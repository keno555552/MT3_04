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

	/// Plane
	Plane plane;
	plane.normal = Normalize({ -0.2f,0.9f,-0.3f });
	plane.distance = 0.0f;

	/// Sphere
	Ball ball{};
	ball.position = { 0.8f, 1.2f, 0.3f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = WHITE;
	ball.acceleration = { 0.0f, -9.8f, 0.0f }; // 重力加速度



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

		/// ballの更新処理
		if (ball.velocity.y < 9.8f) {
			ball.velocity += ball.acceleration * deltaTime;
		} else {
			ball.velocity = ball.acceleration;
		}
		{
			int crashCount = 200;
			for (int i = 0; i < crashCount; i++) {
				ball.position += ball.velocity * deltaTime / float(crashCount);
				if (crashDecision(Sphere{ ball.position, ball.radius }, plane)) {
					Reflect(&ball, &plane);
					ball.position += ball.velocity * deltaTime / float(crashCount);
					break;
				}
			}
		}

		///=========================================================================================================================================================================================
		/// 描画処理
		///=========================================================================================================================================================================================

		/// Grid
		DrawGrid(cameraWorldViewProjectionMatrix, cameraViewportMatrix);

		/// DrawSpring
		DrawPlane(plane, cameraWorldViewProjectionMatrix, cameraViewportMatrix, WHITE);
		DrawSphere({ ball.position, ball.radius }, cameraWorldViewProjectionMatrix, cameraViewportMatrix, ball.color);

		/// ImGui
		ImGui::Begin("Control Penol");
		//ImGui::SliderFloat3("ball.center", &ball.center.x, 0.0f, 2.0f);
		//ImGui::SliderFloat3("center", &center.x, 0.0f, 2.0f);
		//ImGui::SliderFloat("Radius", &radius, 0.0f, 2.0f);
		if (ImGui::Button("Start")) {
			ball.position = { 0.8f, 1.2f, 0.3f };
			ball.velocity = { 0.0f, 0.0f, 0.0f };
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
