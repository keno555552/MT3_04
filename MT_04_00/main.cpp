#include <Novice.h>
#include "myMath.h"
#include "physicsEngine.h"
#include "ImGui.h"

const char kWindowTitle[] = "GC01_05_カン_ケンリャン";

int kWindowWidth = 1280, kWindowHeight = 720;

///=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
/// 重要定義、構造体作り
///=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

enum stage { Title = 0, Stage, scoreBoard };
int stageHandle = Title;

// キー入力結果を受け取る箱
char keys[256] = { 0 };
char preKeys[256] = { 0 };

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);


	///=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
	/// 初期化
	///=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=


	// インスタンス生成と初期化
	Spring spring{};
	spring.anchor = { 0.0f, 0.0f, 0.0f };
	spring.naturalLength = 1.0f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	Ball ball{};
	ball.position = { 1.2f, 0.0f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	spring.end.acceleration = ball.acceleration;
	spring.end.color = ball.color;
	spring.end.mass = ball.mass;
	spring.end.position = ball.position;
	spring.end.velocity = ball.velocity;

	///カメラ初期化
	Vector3 cameraTranslate{ 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate{ 0.26f, 0.0f, 0.0f };

	Matrix4x4 cameraMatix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
	Matrix4x4 cameraViewMatrix = Inverse(cameraMatix);
	Matrix4x4 cameraProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	Matrix4x4 cameraWorldViewProjectionMatrix = cameraProjectionMatrix * cameraViewMatrix;
	Matrix4x4 cameraViewportMatrix = MakeViewportMatrix(0.0f, 0.0f, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
		/// ボタン処理
		///=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

		if (keys[DIK_A]) { cameraTranslate.x -= 0.1f; }
		if (keys[DIK_D]) { cameraTranslate.x += 0.1f; }
		if (keys[DIK_W]) { cameraTranslate.z += 0.1f; }
		if (keys[DIK_S]) { cameraTranslate.z -= 0.1f; }
		if (keys[DIK_Z]) { cameraRotate.y += 0.1f; }
		if (keys[DIK_C]) { cameraRotate.y -= 0.1f; }
		if (keys[DIK_R]) {
			cameraTranslate = { 0.0f, 1.9f, -6.49f };
			cameraRotate = { 0.26f, 0.0f,   0.0f };
		}

		///=========================================================================================================================================================================================
		/// 更新処理
		///=========================================================================================================================================================================================
		
		///カメラ更新処理
		cameraMatix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		cameraViewMatrix = Inverse(cameraMatix);
		cameraProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		cameraWorldViewProjectionMatrix = cameraViewMatrix * cameraProjectionMatrix;
		cameraViewportMatrix = MakeViewportMatrix(0.0f, 0.0f, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		springUpdate(&spring);
		ball.acceleration	= spring.end.acceleration ;
		ball.mass			= spring.end.mass		  ;
		ball.position		= spring.end.position	  ;
		ball.velocity		= spring.end.velocity	  ;


		///=========================================================================================================================================================================================
		/// 描画処理
		///=========================================================================================================================================================================================

		/// Grid
		DrawGrid(cameraWorldViewProjectionMatrix, cameraViewportMatrix);

		/// DrawSpring
		DrawSphere({ ball.position, ball.radius }, cameraWorldViewProjectionMatrix, cameraViewportMatrix, ball.color);
		Draw3DLine({spring.anchor,spring.end.position - spring.anchor }, cameraWorldViewProjectionMatrix, cameraViewportMatrix, WHITE);

		/// ImGui
		ImGui::Begin("Control Penol");
		if (ImGui::Button("Start")) {
			spring.end.position = { 1.2f, 0.0f, 0.0f };
			spring.end.mass = 2.0f;
			spring.end.color = BLUE;
			spring.end.velocity = { 0.0f,0.0f,0.0f };
		}

		ImGui::End();

		/// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		/// StageEND
		/// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
