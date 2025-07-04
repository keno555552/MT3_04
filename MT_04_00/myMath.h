#pragma once
#include <assert.h>
#include <math.h>
#define M_PI 3.14159265358979323846f

///by keno v1.35

#pragma region Vector2
typedef struct Vector2 {

	///定義
	float x, y;

	///演算子再定義
	Vector2 operator+(const Vector2& target);
	Vector2 operator-(const Vector2& target);
	Vector2 operator*(const Vector2& target);
	Vector2 operator/(const Vector2& target);
	Vector2 operator*(const float& target);
	friend Vector2 operator*(float scalar, const Vector2& vec);
	Vector2 operator/(const float& target);

	///int
	Vector2 operator*(const int& target);
	friend Vector2 operator*(int scalar, const Vector2& vec);

}Vector2;

#pragma endregion

#pragma region Vector3
typedef struct Vector3 {

	///定義
	float x, y, z;

	///演算子再定義
	Vector3 operator+(const Vector3& target);
	Vector3 operator-(const Vector3& target);
	Vector3 operator*(const Vector3& target);
	Vector3 operator/(const Vector3& target);
	Vector3 operator*(const float& target);
	friend Vector3 operator*(float scalar, const Vector3& vec);
	Vector3 operator/(const float& target);

	///int
	Vector3 operator*(const int& target);
	friend Vector3 operator*(int scalar, const Vector3& vec);

	///ヘルム
	Vector3 helmholtz();
	///正規化
	Vector3 normalize();
}Vector3;

// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2);

// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

// スカラー倍
Vector3 Multiply(const float& scalar, const Vector3& v);

// 内積
float Dot(const Vector3& v1, const Vector3& v2);

// 長さ（ノルム）
float Length(const Vector3& v);

// 正規化
Vector3 Normalize(const Vector3& v);

// 表示
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

#pragma endregion

#pragma region Matrix3x3

typedef struct Matrix3x3 {

	///定義
	float m[3][3];

	///演算子再定義
	Matrix3x3 operator+(const Matrix3x3& target);
	Matrix3x3 operator-(const Matrix3x3& target);
	Matrix3x3 operator*(const Matrix3x3& target);

}Matrix3x3;

////////////////////////////////////////////////////////////////////////////陣列変換

/// <summary>
/// Vector2からMatrix3x3への変換
/// </summary>
/// <param name="translate">Vector2</param>
/// <returns>結果Matrix3x3</returns>
Matrix3x3 MakeTranslateMatrix3x3(const Vector2 translate);

/// <summary>
/// Matrix3x3からVector2への変換
/// </summary>
/// <param name="translate">Matrix3x3</param>
/// <returns>結果Vector2</returns>
Vector2 MakeTranslateVector2(const Matrix3x3 translate);

////////////////////////////////////////////////////////////////////////////陣列計算

/// <summary>
/// Matrix3x3掛けるVector2
/// </summary>
/// <param name="changeMatrix">変換したいMatrix3x3</param>
/// <param name="vector">Vector2</param>
/// <returns>結果Matrix3x3</returns>
Vector2 Vector2xMatrix3x3(const Vector2 vector, const Matrix3x3 matrix);

/// <summary>
/// 回転行列行列
/// </summary>
/// <param name="theta">回転角度(radian)</param>
/// <returns></returns>
Matrix3x3 MakeRotateMatrix(const float theta);

/// <summary>
/// Matrix3x3の逆行列を探す
/// </summary>
/// <param name="matrix">元のMatrix3x3</param>
/// <returns>結果Matrix3x3</returns>
Matrix3x3 Inverse(Matrix3x3 matrix);

/// <summary>
/// Matrix3x3の転置行列を探す
/// </summary>
/// <param name="matrix">元のMatrix3x3</param>
/// <returns>結果Matrix3x3</returns>
Matrix3x3 Transpose(Matrix3x3 matrix);

////////////////////////////////////////////////////////////////////////////陣列表示

///// <summary>
///// Matrix3x3を描写する
///// </summary>
///// <param name="x">左上のposX</param>
///// <param name="y">左上のposY</param>
///// <param name="matrix">描写したいMatrix3x3</param>
//void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix);

////////////////////////////////////////////////////////////////////////////陣列結合

/// <summary>
/// 使わない、例の結合用関数
/// </summary>
/// <param name="scale"></param>
/// <param name="rotate"></param>
/// <param name="translate"></param>
/// <returns></returns>
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);

/// <summary>
/// 二つのMatrix3x3を掛け算する
/// </summary>
/// <param name="matrix1">Matrix3x3 その1</param>
/// <param name="matrix2">Matrix3x3 その2</param>
/// <returns>結果Matrix3x3</returns>
Matrix3x3 MatrixMix(Matrix3x3 matrix1, Matrix3x3 matrix2);

/// <summary>
/// 三つのMatrix3x3を掛け算する
/// </summary>
/// <param name="matrix1">Matrix3x3 その1</param>
/// <param name="matrix2">Matrix3x3 その2</param>
/// <param name="matrix2">Matrix3x3 その3</param>
/// <returns>結果Matrix3x3</returns>
Matrix3x3 MatrixMix(Matrix3x3 matrix1, Matrix3x3 matrix2, Matrix3x3 matrix3);

/// <summary>
/// 四つのMatrix3x3を掛け算する
/// </summary>
/// <param name="matrix1">Matrix3x3 その1</param>
/// <param name="matrix2">Matrix3x3 その2</param>
/// <param name="matrix2">Matrix3x3 その3</param>
/// <param name="matrix2">Matrix3x3 その4</param>
/// <returns>結果Matrix3x3</returns>
Matrix3x3 MatrixMix(Matrix3x3 matrix1, Matrix3x3 matrix2, Matrix3x3 matrix3, Matrix3x3 matrix4);


////////////////////////////////////////////////////////////////////////////カメラ改変陣列

/// <summary>
/// ローカル座標からのワルド座標へ改変
/// </summary>
/// <returns></returns>
Matrix3x3 MakeWorldMatrix(Matrix3x3 origin);

/// <summary>
/// ビュー変換数列生成
/// </summary>
/// <returns></returns>
Matrix3x3 MakeViewMatrix(Matrix3x3 origin, Vector2 pos);

/// <summary>
/// 正射影変換数列生成
/// </summary>
/// <returns></returns>
Matrix3x3 MakeOrthographicMatrix(Vector2 leftTop, Vector2 rightBottom);

/// <summary>
/// ビューポート変換数列生成
/// </summary>
/// <returns></returns>
Matrix3x3 MakeViewportMatrix(Vector2 leftTop, Vector2 rightBottom);

#pragma endregion

#pragma region Matrix4x4
typedef struct Matrix4x4 {

	///定義
	float m[4][4];

	///単位行列
	Matrix4x4 Identity();
	///逆行列
	Matrix4x4 Inverse();
	///転置行列
	Matrix4x4 Transpose();

	///演算子再定義
	Matrix4x4 operator+(const Matrix4x4& target);
	Matrix4x4 operator-(const Matrix4x4& target);
	Matrix4x4 operator*(const Matrix4x4& target);
	Matrix4x4 operator*(const float& target);
	friend Matrix4x4 operator*(float scalar, const Matrix4x4& vec);


}Matrix4x4;

#pragma region 陣列転換

/// <summary>
/// 普通のVector3からMatrix4x4への変換
/// </summary>
/// <param name="translate">Vector3</param>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeTranslateMatrix3x3(const Vector3 translate);

/// <summary>
/// 移動のVector3からMatrix4x4への変換
/// </summary>
/// <param name="translate">Vector3</param>
/// <returns>結果Matrix4x4</returns>
Vector3 MakeTranslateVector3(const Matrix4x4 translate);

#pragma endregion

#pragma region 陣列表示
/// <summary>
/// Matrix4x4を描写する
/// </summary>
/// <param name="x">左上のposX</param>
/// <param name="y">左上のposY</param>
/// <param name="matrix">描写したいMatrix3x3</param>
void MatrixScreenPrintf(int x, int y, Matrix4x4& matrix, const char* name = nullptr);
#pragma endregion

#pragma region 陣列計算

/// ///////////////////////for this task

// 1. 行列的加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
// 2. 行列的減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
// 3. 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
// 4. 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);
// 5. 転置行列
Matrix4x4 Transpose(const Matrix4x4 m);
// 6. 単位行列の作成
Matrix4x4 MakeIdentity4x4();

/// <summary>
/// 拡縮のVector3からMatrix4x4への変換
/// </summary>
/// <param name="scole">Vector3</param>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeScaleMatrix(const Vector3 scole);

Matrix4x4 MakeRotateXMatrix(const float theta);

Matrix4x4 MakeRotateYMatrix(const float theta);

Matrix4x4 MakeRotateZMatrix(const float theta);

/// <summary>
/// 回転のVector3からMatrix4x4への変換
/// </summary>
/// <param name="rotate">Vector3</param>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeRotateMatrix(const Matrix4x4 thetaX, const Matrix4x4 thetaY, const Matrix4x4 thetaZ);

/// <summary>
/// 移動のVector3からMatrix4x4への変換
/// </summary>
/// <param name="translate">Vector3</param>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeTranslateMatrix(const Vector3 translate);

#pragma endregion

#pragma region カメラ改変陣列

/// <summary>
/// Matrix4x4のアフィン変換(Vector3から)
/// </summary>
/// <param name="scole">Vector3</param>
/// <param name="rotate">Vector3</param>
/// <param name="translate">Vector3</param>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeAffineMatrix(Vector3 scale, Vector3 rotate, Vector3 translate);

/// <summary>
/// 最大4つのMatrix4x4を掛け算する
/// </summary>
/// <param name="matrix1">Matrix4x4 その1</param>
/// <param name="matrix2">Matrix4x4 その2</param>
/// <param name="matrix3">Matrix4x4 その3(有無可)</param>
/// <param name="matrix4">Matrix4x4 その4(有無可)</param>
/// <returns>結果Matrix3x3</returns>
Matrix4x4 MatrixMix(Matrix4x4* matrix1,
	Matrix4x4* matrix2,
	Matrix4x4* matrix3 = nullptr,
	Matrix4x4* matrix4 = nullptr);

/// <summary>
/// ローカル座標からのワルド座標へ改変
/// </summary>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeWorldMatrix(Matrix4x4 origin);

/// <summary>
/// ビュー変換数列生成
/// </summary>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeViewMatrix(Vector3 scole, Vector3 rotate, Vector3 translate);

/// <summary>
/// 正射影変換数列生成
/// </summary>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeProjectionMatrix(float  leftO, float  rightO,
	float   topO, float bottomO,
	float  nearO, float    farO);

/// <summary>
/// 透視投影変換数列生成
/// </summary>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio,
	float nearClip, float farClip);

/// <summary>
/// ビューポート変換数列生成
/// </summary>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeViewportMatrix(float   left, float     top,
	float  width, float  height,
	float    minD, float    maxD);

/// <summary>
/// ビューポート変換数列生成
/// </summary>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeOrthographicMatrix(float   left, float   top,
	float  right, float  bottom,
	float  nearClip, float  farClip);

/// <summary>
///　3Dカメラの総まとめ変換
/// </summary>
/// <param name="obj">もの自身のワルド座標</param>
/// <param name="tranformMatrix">変換Matrix</param>
/// <returns></returns>
Vector3 viewFinilTransform(Vector3 obj, Matrix4x4 tranformMatrix);


#pragma endregion

#pragma endregion

#pragma region Transform
struct Transform {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};
#pragma endregion

#pragma region Geometry

/// 直線
struct Line {
	Vector3 origin; //<<< 始点
	Vector3 diff;   //<<< 終点への差分ベクトル
};

/// 半直線
struct Ray {
	Vector3 origin; //<<< 始点
	Vector3 diff;   //<<< 終点への差分ベクトル
};

/// 線分
struct Segment {
	Vector3 origin; //<<< 始点
	Vector3 diff;   //<<< 終点への差分ベクトル
};
void Draw3DLine(const Line& line, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color);

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

/// <summary>
/// 線形補間
/// </summary>
/// <param name="a">A point Vector2構造体</param>
/// <param name="b">C point Vector2構造体</param>
/// <param name="c">補間用変数t</param>
/// <param name="t">総分割数</param>
/// <returns></returns>
float Lerp(float a, float b, int c, int t);


/// 曲線

/// <summary>
/// 2次元2次ベジェ曲線の点計算
/// </summary>
/// <param name="p0">制御点0</param>
/// <param name="p1">制御点1</param>
/// <param name="p2">制御点2</param>
/// <param name="p3">制御点2</param>
/// <param name="time">補間用変数t</param>
/// <param name="clock">総分割数</param>
/// <returns>曲線上にtの対応点</returns>
Vector2 Bezier(const Vector2 p0, const Vector2 p1, const Vector2 p2, int time, int clock);

/// <summary>
/// 3次元2次ベジェ曲線の点計算
/// </summary>
/// <param name="p0">制御点0</param>
/// <param name="p1">制御点1</param>
/// <param name="p2">制御点2</param>
/// <param name="p3">制御点2</param>
/// <param name="time">補間用変数t</param>
/// <param name="clock">総分割数</param>
/// <returns>曲線上にtの対応点</returns>
Vector3 Bezier(const Vector3 p0, const Vector3 p1, const Vector3 p2, int time, int clock);

void DrawBezier(const Vector3 p0, const Vector3 p1, const Vector3 p2, int function, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color);

/// 球体
typedef struct Sphere {
	Vector3 center;
	float radius;
}Sphere;

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color);

/// 平面
typedef struct Plane {
	Vector3 normal; //<<< 法線ベクトル
	float distance; //<<< 平面の方程式のdistance
}Plane;

/// 三角
typedef struct Triangle {
	Vector3 vertex[3]; //<<< 頂点
}Triangle;

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color);

/// <summary>
/// Vector3の垂直点を返す
/// </summary>
/// <param name="vector">元のVector3</param>
/// <returns></returns>
Vector3 Perpendicular(const Vector3& vector);
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color);


#pragma endregion

#pragma region Hit judgment


/// <summary>
/// 正射影ベクトル
/// </summary>
/// <param name="v1">目標の線</param>
/// <param name="v2">点</param>
/// <returns></returns>
Vector3 Project(const Vector3& v1, const Vector3& v2);

/// 最接近点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

#pragma endregion

#pragma region Other

/// <summary>
/// 二進数比較器
/// </summary>
/// <param name="binary">比較基準</param>
/// <param name="target">目標</param>
/// <returns>=ならtrue</returns>
bool BinaryComparator(int binary, int target);

/// <summary>
/// cross積を求める
/// </summary>
/// <param name="v1">線A</param>
/// <param name="v2">線B</param>
/// <returns></returns>
Vector3 Cross(const Vector3& v1, const Vector3& v2);


#pragma endregion