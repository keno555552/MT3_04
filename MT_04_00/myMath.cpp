#include "myMath.h"
#include "Novice.h"

#pragma region Vector2
Vector2 Vector2::operator+(const Vector2& target) {
	return { x + target.x, y + target.y };
}

Vector2 Vector2::operator-(const Vector2& target) {
	return { x - target.x, y - target.y };
}

Vector2 Vector2::operator*(const Vector2& target) {
	return { x * target.x, y * target.y };
}

Vector2 Vector2::operator/(const Vector2& target) {
	return { x / target.x, y / target.y };
}

Vector2 Vector2::operator*(const float& target) {
	return { x * target, y * target };
}

Vector2 operator*(float scalar, const Vector2& vec) {
	return { vec.x * scalar, vec.y * scalar };
}

Vector2 Vector2::operator/(const float& target) {
	return { x / target, y / target };
}



Vector2 Vector2::operator*(const int& target) {
	return { x * (float)target, y * (float)target };
}

Vector2 operator*(int scalar, const Vector2& vec) {
	return { vec.x * (float)scalar, vec.y * (float)scalar };
}
#pragma endregion

#pragma region Vector3
Vector3 Vector3::operator+(const Vector3& target) {
	return { x + target.x, y + target.y , z + target.z };
}

Vector3 Vector3::operator-(const Vector3& target) {
	return { x - target.x, y - target.y , z - target.z };
}

Vector3 Vector3::operator*(const Vector3& target) {
	return { x * target.x, y * target.y };
}

Vector3 Vector3::operator/(const Vector3& target) {
	return { x / target.x, y / target.y, z / target.z };
}

Vector3 Vector3::operator*(const float& target) {
	return { x * target, y * target, z * target };
}

Vector3 operator*(float scalar, const Vector3& vec) {
	return { vec.x * scalar, vec.y * scalar, vec.z * scalar };
}

Vector3 Vector3::operator/(const float& target) {
	return { x / target, y / target, z / target };
}



Vector3 Vector3::operator*(const int& target) {
	return { x * (float)target, y * (float)target, z * (float)target };
}


Vector3 operator*(int scalar, const Vector3& vec) {
	return { vec.x * (float)scalar, vec.y * (float)scalar , vec.z * (float)scalar };
}

Vector3 Vector3::helmholtz() {
	return { sqrtf(x * x),sqrtf(y * y),sqrtf(z * z) };
}

Vector3 Vector3::normalize() {
	Vector3 length = helmholtz();
	if (length.x != 0 && length.y != 0 && length.z != 0) {
		return { x / length.x, y / length.y, z / length.z };
	}
	return Vector3();
}

Vector3 Add(const Vector3& V1, const Vector3& V2) {
	return { V1.x + V2.x, V1.y + V2.y , V1.z + V2.z };
}

Vector3 Subtract(const Vector3& V1, const Vector3& V2) {
	return { V1.x - V2.x, V1.y - V2.y , V1.z - V2.z };
}

Vector3 Multiply(const float& scalar, const Vector3& v) {
	return { scalar * v.x, scalar * v.y, scalar * v.z };
}

float Dot(const Vector3& V1, const Vector3& V2) {
	return V1.x * V2.x + V1.y * V2.y + V1.z * V2.z;
}

float Length(const Vector3& v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Normalize(const Vector3& v) {
	float length = Length(v);
	if (length != 0) {
		return { v.x / length, v.y / length, v.z / length };
	}
	return Vector3();
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	static const int kColumnWidth = 60;
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

#pragma endregion

#pragma region Matrix3x3
Matrix3x3 Matrix3x3::operator+(const Matrix3x3& target) {
	Matrix3x3 resuit = {};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			resuit.m[i][j] = m[i][j] + target.m[i][j];
		}
	}

	return resuit;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& target) {
	Matrix3x3 resuit = {};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			resuit.m[i][j] = m[i][j] - target.m[i][j];
		}
	}

	return resuit;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& target) {
	Matrix3x3 result = {};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				result.m[i][j] += m[i][k] * target.m[k][j];
			}
		}
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////陣列変換

Matrix3x3 MakeTranslateMatrix3x3(const Vector2 translate) {
	return { 1,0,0,
			 0,1,0,
			  translate.x,translate.y,1 };
}

Vector2 MakeTranslateVector2(const Matrix3x3 translate) {
	return { translate.m[2][0],translate.m[2][1] };
}

////////////////////////////////////////////////////////////////////////////陣列計算

Vector2 Vector2xMatrix3x3(const Vector2 vector, const Matrix3x3 matrix) {
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

Matrix3x3 MakeRotateMatrix(const float theta) {
	return{ cosf(theta) ,sinf(theta),0,
			-sinf(theta),cosf(theta),0,
			0,0,1 };
}

Matrix3x3 Inverse(Matrix3x3 matrix) {
	float determinant = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1])
		-
		(matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] +
			matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] +
			matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

	return Matrix3x3{ (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) / determinant,
					 -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) / determinant,
					  (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) / determinant,

					 -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) / determinant,
					  (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) / determinant,
					 -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) / determinant,

					  (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) / determinant,
					 -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) / determinant,
					  (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) / determinant };
}


Matrix3x3 Transpose(Matrix3x3 matrix) {

	return Matrix3x3{ matrix.m[0][0],matrix.m[1][0],matrix.m[2][0],
					  matrix.m[0][1],matrix.m[1][1],matrix.m[2][1],
					  matrix.m[0][2],matrix.m[1][2],matrix.m[2][2] };
}

////////////////////////////////////////////////////////////////////////////陣列表示

//void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix) {
//	int kColumnWidth = 80;
//	int kRowHeight = 40;
//	for (int row = 0; row < 3; ++row) {
//		for (int column = 0; column < 3; ++column) {
//			Novice::ScreenPrintf(
//				x + column * kColumnWidth,
//				y + row * kRowHeight,
//				"%.02f",
//				matrix.m[row][column]
//			);
//		}
//	}
//}

////////////////////////////////////////////////////////////////////////////陣列結合

Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {
	return { scale.x * cosf(rotate),scale.x * sinf(rotate),0,
			 -scale.y * sinf(rotate),scale.y * cosf(rotate),0,
			  translate.x,translate.y,1 };
}

Matrix3x3 MatrixMix(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result = matrix1 * matrix2;
	return result;
}

Matrix3x3 MatrixMix(Matrix3x3 matrix1, Matrix3x3 matrix2, Matrix3x3 matrix3) {
	Matrix3x3 result = matrix1 * matrix2 * matrix3;
	return result;
}

Matrix3x3 MatrixMix(Matrix3x3 matrix1, Matrix3x3 matrix2, Matrix3x3 matrix3, Matrix3x3 matrix4) {
	Matrix3x3 result = matrix1 * matrix2 * matrix3 * matrix4;
	return result;
}

////////////////////////////////////////////////////////////////////////////world改変陣列

Matrix3x3 MakeWorldMatrix(Matrix3x3 origin) {
	return origin;
}

Matrix3x3 MakeViewMatrix(Matrix3x3 origin, Vector2 pos) {
	Vector2 move = pos;
	Matrix3x3 move2 = MakeTranslateMatrix3x3(move);
	Matrix3x3 result = MatrixMix(origin, move2);
	return Inverse(result);
}

Matrix3x3 MakeOrthographicMatrix(Vector2 leftTop, Vector2 rightBottom) {
	return{ 2.0f / (rightBottom.x - leftTop.x),0.0f,0.0f,
			0.0f,2.0f / (leftTop.y - rightBottom.y),0.0f,
			(leftTop.x + rightBottom.x) / (leftTop.x - rightBottom.x),(leftTop.y + rightBottom.y) / (rightBottom.y - leftTop.y),1.0f };
}

Matrix3x3 MakeViewportMatrix(Vector2 leftTop, Vector2 rightBottom) {
	return{ rightBottom.x / 2.0f,0.0f,0.0f,
			0.0f,-(rightBottom.y / 2.0f),0.0f,
			leftTop.x + (rightBottom.x / 2.0f),leftTop.y + (rightBottom.y / 2.0f),1.0f };
}
#pragma endregion

#pragma region Matrix4x4
Matrix4x4 Matrix4x4::Identity() {
	Matrix4x4 resuit = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			resuit.m[i][j] = 0;
			m[i][j] = 0;
			if (i == j) {
				resuit.m[i][j] = 1;
				m[i][j] = 1;
			}
		}
	}
	return resuit;
}

Matrix4x4 Matrix4x4::Inverse() {
	float determinant = m[0][0] * m[1][1] * m[2][2] * m[3][3]
		+ m[0][0] * m[1][2] * m[2][3] * m[3][1]
		+ m[0][0] * m[1][3] * m[2][1] * m[3][2]

		- m[0][0] * m[1][3] * m[2][2] * m[3][1]
		- m[0][0] * m[1][2] * m[2][1] * m[3][3]
		- m[0][0] * m[1][1] * m[2][3] * m[3][2]

		- m[0][1] * m[1][0] * m[2][2] * m[3][3]
		- m[0][2] * m[1][0] * m[2][3] * m[3][1]
		- m[0][3] * m[1][0] * m[2][1] * m[3][2]

		+ m[0][3] * m[1][0] * m[2][2] * m[3][1]
		+ m[0][2] * m[1][0] * m[2][1] * m[3][3]
		+ m[0][1] * m[1][0] * m[2][3] * m[3][2]

		+ m[0][1] * m[1][2] * m[2][0] * m[3][3]
		+ m[0][2] * m[1][3] * m[2][0] * m[3][1]
		+ m[0][3] * m[1][1] * m[2][0] * m[3][2]

		- m[0][3] * m[1][2] * m[2][0] * m[3][1]
		- m[0][2] * m[1][1] * m[2][0] * m[3][3]
		- m[0][1] * m[1][3] * m[2][0] * m[3][2]

		- m[0][1] * m[1][2] * m[2][3] * m[3][0]
		- m[0][2] * m[1][3] * m[2][1] * m[3][0]
		- m[0][3] * m[1][1] * m[2][2] * m[3][0]

		+ m[0][3] * m[1][2] * m[2][1] * m[3][0]
		+ m[0][2] * m[1][1] * m[2][3] * m[3][0]
		+ m[0][1] * m[1][3] * m[2][2] * m[3][0];

	return Matrix4x4{ (m[1][1] * m[2][2] * m[3][3]
					 + m[1][2] * m[2][3] * m[3][1]
					 + m[1][3] * m[2][1] * m[3][2]
					 - m[1][3] * m[2][2] * m[3][1]
					 - m[1][2] * m[2][1] * m[3][3]
					 - m[1][1] * m[2][3] * m[3][2]) / determinant,/// 11

					(-m[0][1] * m[2][2] * m[3][3]
					 - m[0][2] * m[2][3] * m[3][1]
					 - m[0][3] * m[2][1] * m[3][2]
					 + m[0][3] * m[2][2] * m[3][1]
					 + m[0][2] * m[2][1] * m[3][3]
					 + m[0][1] * m[2][3] * m[3][2]) / determinant,/// 12

					(+m[0][1] * m[1][2] * m[3][3]
					 + m[0][2] * m[1][3] * m[3][1]
					 + m[0][3] * m[1][1] * m[3][2]
					 - m[0][3] * m[1][2] * m[3][1]
					 - m[0][2] * m[1][1] * m[3][3]
					 - m[0][1] * m[1][3] * m[3][2]) / determinant,/// 13

					(-m[0][1] * m[1][2] * m[2][3]
					 - m[0][2] * m[1][3] * m[2][1]
					 - m[0][3] * m[1][1] * m[2][2]
					 + m[0][3] * m[1][2] * m[2][1]
					 + m[0][2] * m[1][1] * m[2][3]
					 + m[0][1] * m[1][3] * m[2][2]) / determinant,/// 14

					(-m[1][0] * m[2][2] * m[3][3]
					 - m[1][2] * m[2][3] * m[3][0]
					 - m[1][3] * m[2][0] * m[3][2]
					 + m[1][3] * m[2][2] * m[3][0]
					 + m[1][2] * m[2][0] * m[3][3]
					 + m[1][0] * m[2][3] * m[3][2]) / determinant,/// 21

					(+m[0][0] * m[2][2] * m[3][3]
					 + m[0][2] * m[2][3] * m[3][0]
					 + m[0][3] * m[2][0] * m[3][2]
					 - m[0][3] * m[2][2] * m[3][0]
					 - m[0][2] * m[2][0] * m[3][3]
					 - m[0][0] * m[2][3] * m[3][2]) / determinant,/// 22

					(-m[0][0] * m[1][2] * m[3][3]
					 - m[0][2] * m[1][3] * m[3][0]
					 - m[0][3] * m[1][0] * m[3][2]
					 + m[0][3] * m[1][2] * m[3][0]
					 + m[0][2] * m[1][0] * m[3][3]
					 + m[0][0] * m[1][3] * m[3][2]) / determinant,/// 23

					(+m[0][0] * m[1][2] * m[2][3]
					 + m[0][2] * m[1][3] * m[2][0]
					 + m[0][3] * m[1][0] * m[2][2]
					 - m[0][3] * m[1][2] * m[2][0]
					 - m[0][2] * m[1][0] * m[2][3]
					 - m[0][0] * m[1][3] * m[2][2]) / determinant,/// 24

					(+m[1][0] * m[2][1] * m[3][3]
					 + m[1][1] * m[2][3] * m[3][0]
					 + m[1][3] * m[2][0] * m[3][1]
					 - m[1][3] * m[2][1] * m[3][0]
					 - m[1][1] * m[2][0] * m[3][3]
					 - m[1][0] * m[2][3] * m[3][1]) / determinant,/// 31

					(-m[0][0] * m[2][1] * m[3][3]
					 - m[0][1] * m[2][3] * m[3][0]
					 - m[0][3] * m[2][0] * m[3][1]
					 + m[0][3] * m[2][1] * m[3][0]
					 + m[0][1] * m[2][0] * m[3][3]
					 + m[0][0] * m[2][3] * m[3][1]) / determinant,/// 32

					(+m[0][0] * m[1][1] * m[3][3]
					 + m[0][1] * m[1][3] * m[3][0]
					 + m[0][3] * m[1][0] * m[3][1]
					 - m[0][3] * m[1][1] * m[3][0]
					 - m[0][1] * m[1][0] * m[3][3]
					 - m[0][0] * m[1][3] * m[3][1]) / determinant,/// 33

					(-m[0][0] * m[1][1] * m[2][3]
					 - m[0][1] * m[1][3] * m[2][0]
					 - m[0][3] * m[1][0] * m[2][1]
					 + m[0][3] * m[1][1] * m[2][0]
					 + m[0][1] * m[1][0] * m[2][3]
					 + m[0][0] * m[1][3] * m[2][1]) / determinant,/// 34

					(-m[1][0] * m[2][1] * m[3][2]
					 - m[1][1] * m[2][2] * m[3][0]
					 - m[1][2] * m[2][0] * m[3][1]
					 + m[1][2] * m[2][1] * m[3][0]
					 + m[1][1] * m[2][0] * m[3][2]
					 + m[1][0] * m[2][2] * m[3][1]) / determinant,/// 41

					(+m[0][0] * m[2][1] * m[3][2]
					 + m[0][1] * m[2][2] * m[3][0]
					 + m[0][2] * m[2][0] * m[3][1]
					 - m[0][2] * m[2][1] * m[3][0]
					 - m[0][1] * m[2][0] * m[3][2]
					 - m[0][0] * m[2][2] * m[3][1]) / determinant,/// 42

					(-m[0][0] * m[1][1] * m[3][2]
					 - m[0][1] * m[1][2] * m[3][0]
					 - m[0][2] * m[1][0] * m[3][1]
					 + m[0][2] * m[1][1] * m[3][0]
					 + m[0][1] * m[1][0] * m[3][2]
					 + m[0][0] * m[1][2] * m[3][1]) / determinant,/// 43

					(+m[0][0] * m[1][1] * m[2][2]
					 + m[0][1] * m[1][2] * m[2][0]
					 + m[0][2] * m[1][0] * m[2][1]
					 - m[0][2] * m[1][1] * m[2][0]
					 - m[0][1] * m[1][0] * m[2][2]
					 - m[0][0] * m[1][2] * m[2][1]) / determinant /// 44
	};
}

Matrix4x4 Matrix4x4::Transpose() {
	Matrix4x4 result = {};
	Matrix4x4 a = *this;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = a.m[j][i];
			m[i][j] = a.m[j][i];

		}
	}
	return result;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& target) {
	Matrix4x4 resuit = {};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resuit.m[x][y] = m[x][y] + target.m[x][y];
		}
	}


	return resuit;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& target) {
	Matrix4x4 resuit = {};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resuit.m[x][y] = m[x][y] - target.m[x][y];
		}
	}
	return resuit;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& target) {
	Matrix4x4 resuit = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				resuit.m[i][j] += m[i][k] * target.m[k][j];
			}
		}
	}
	return resuit;
}

Matrix4x4 Matrix4x4::operator*(const float& target) {
	Matrix4x4 resuit = {};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resuit.m[x][y] = m[x][y] * target;
		}
	}
	return resuit;
}


Matrix4x4 operator*(float scalar, const Matrix4x4& vec) {
	Matrix4x4 resuit = {};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resuit.m[x][y] = vec.m[x][y] * scalar;
		}
	}
	return resuit;
}

#pragma region 陣列転換
Matrix4x4 MakeTranslateMatrix3x3(const Vector3 translate) {
	return Matrix4x4{ 1.0f,		  0.0f,		   0.0f, 0.0f,
							 0.0f,		  1.0f,		   0.0f, 0.0f,
							 0.0f,		  0.0f,		   1.0f, 0.0f,
					  translate.x, translate.y,	translate.z, 1.0f };
}

Vector3 MakeTranslateVector3(const Matrix4x4 translate) {
	return Vector3(translate.m[3][0], translate.m[3][1], translate.m[3][2]);
}
#pragma endregion

//////////////////////////////////////////////////////////////////////////陣列表示

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resuit = {};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resuit.m[x][y] = m1.m[x][y] + m2.m[x][y];
		}
	}
	return resuit;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resuit = {};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resuit.m[x][y] = m1.m[x][y] - m2.m[x][y];
		}
	}
	return resuit;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resuit = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				resuit.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return resuit;
}

Matrix4x4 Inverse(const Matrix4x4& m) {
	float determinant = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]

		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]

		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]

		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]

		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]

		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]

		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]

		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	return Matrix4x4{ (m.m[1][1] * m.m[2][2] * m.m[3][3]
					 + m.m[1][2] * m.m[2][3] * m.m[3][1]
					 + m.m[1][3] * m.m[2][1] * m.m[3][2]
					 - m.m[1][3] * m.m[2][2] * m.m[3][1]
					 - m.m[1][2] * m.m[2][1] * m.m[3][3]
					 - m.m[1][1] * m.m[2][3] * m.m[3][2]) / determinant,/// 11

					(-m.m[0][1] * m.m[2][2] * m.m[3][3]
					 - m.m[0][2] * m.m[2][3] * m.m[3][1]
					 - m.m[0][3] * m.m[2][1] * m.m[3][2]
					 + m.m[0][3] * m.m[2][2] * m.m[3][1]
					 + m.m[0][2] * m.m[2][1] * m.m[3][3]
					 + m.m[0][1] * m.m[2][3] * m.m[3][2]) / determinant,/// 12

					(+m.m[0][1] * m.m[1][2] * m.m[3][3]
					 + m.m[0][2] * m.m[1][3] * m.m[3][1]
					 + m.m[0][3] * m.m[1][1] * m.m[3][2]
					 - m.m[0][3] * m.m[1][2] * m.m[3][1]
					 - m.m[0][2] * m.m[1][1] * m.m[3][3]
					 - m.m[0][1] * m.m[1][3] * m.m[3][2]) / determinant,/// 13

					(-m.m[0][1] * m.m[1][2] * m.m[2][3]
					 - m.m[0][2] * m.m[1][3] * m.m[2][1]
					 - m.m[0][3] * m.m[1][1] * m.m[2][2]
					 + m.m[0][3] * m.m[1][2] * m.m[2][1]
					 + m.m[0][2] * m.m[1][1] * m.m[2][3]
					 + m.m[0][1] * m.m[1][3] * m.m[2][2]) / determinant,/// 14

					(-m.m[1][0] * m.m[2][2] * m.m[3][3]
					 - m.m[1][2] * m.m[2][3] * m.m[3][0]
					 - m.m[1][3] * m.m[2][0] * m.m[3][2]
					 + m.m[1][3] * m.m[2][2] * m.m[3][0]
					 + m.m[1][2] * m.m[2][0] * m.m[3][3]
					 + m.m[1][0] * m.m[2][3] * m.m[3][2]) / determinant,/// 21

					(+m.m[0][0] * m.m[2][2] * m.m[3][3]
					 + m.m[0][2] * m.m[2][3] * m.m[3][0]
					 + m.m[0][3] * m.m[2][0] * m.m[3][2]
					 - m.m[0][3] * m.m[2][2] * m.m[3][0]
					 - m.m[0][2] * m.m[2][0] * m.m[3][3]
					 - m.m[0][0] * m.m[2][3] * m.m[3][2]) / determinant,/// 22

					(-m.m[0][0] * m.m[1][2] * m.m[3][3]
					 - m.m[0][2] * m.m[1][3] * m.m[3][0]
					 - m.m[0][3] * m.m[1][0] * m.m[3][2]
					 + m.m[0][3] * m.m[1][2] * m.m[3][0]
					 + m.m[0][2] * m.m[1][0] * m.m[3][3]
					 + m.m[0][0] * m.m[1][3] * m.m[3][2]) / determinant,/// 23

					(+m.m[0][0] * m.m[1][2] * m.m[2][3]
					 + m.m[0][2] * m.m[1][3] * m.m[2][0]
					 + m.m[0][3] * m.m[1][0] * m.m[2][2]
					 - m.m[0][3] * m.m[1][2] * m.m[2][0]
					 - m.m[0][2] * m.m[1][0] * m.m[2][3]
					 - m.m[0][0] * m.m[1][3] * m.m[2][2]) / determinant,/// 24

					(+m.m[1][0] * m.m[2][1] * m.m[3][3]
					 + m.m[1][1] * m.m[2][3] * m.m[3][0]
					 + m.m[1][3] * m.m[2][0] * m.m[3][1]
					 - m.m[1][3] * m.m[2][1] * m.m[3][0]
					 - m.m[1][1] * m.m[2][0] * m.m[3][3]
					 - m.m[1][0] * m.m[2][3] * m.m[3][1]) / determinant,/// 31

					(-m.m[0][0] * m.m[2][1] * m.m[3][3]
					 - m.m[0][1] * m.m[2][3] * m.m[3][0]
					 - m.m[0][3] * m.m[2][0] * m.m[3][1]
					 + m.m[0][3] * m.m[2][1] * m.m[3][0]
					 + m.m[0][1] * m.m[2][0] * m.m[3][3]
					 + m.m[0][0] * m.m[2][3] * m.m[3][1]) / determinant,/// 32

					(+m.m[0][0] * m.m[1][1] * m.m[3][3]
					 + m.m[0][1] * m.m[1][3] * m.m[3][0]
					 + m.m[0][3] * m.m[1][0] * m.m[3][1]
					 - m.m[0][3] * m.m[1][1] * m.m[3][0]
					 - m.m[0][1] * m.m[1][0] * m.m[3][3]
					 - m.m[0][0] * m.m[1][3] * m.m[3][1]) / determinant,/// 33

					(-m.m[0][0] * m.m[1][1] * m.m[2][3]
					 - m.m[0][1] * m.m[1][3] * m.m[2][0]
					 - m.m[0][3] * m.m[1][0] * m.m[2][1]
					 + m.m[0][3] * m.m[1][1] * m.m[2][0]
					 + m.m[0][1] * m.m[1][0] * m.m[2][3]
					 + m.m[0][0] * m.m[1][3] * m.m[2][1]) / determinant,/// 34

					(-m.m[1][0] * m.m[2][1] * m.m[3][2]
					 - m.m[1][1] * m.m[2][2] * m.m[3][0]
					 - m.m[1][2] * m.m[2][0] * m.m[3][1]
					 + m.m[1][2] * m.m[2][1] * m.m[3][0]
					 + m.m[1][1] * m.m[2][0] * m.m[3][2]
					 + m.m[1][0] * m.m[2][2] * m.m[3][1]) / determinant,/// 41

					(+m.m[0][0] * m.m[2][1] * m.m[3][2]
					 + m.m[0][1] * m.m[2][2] * m.m[3][0]
					 + m.m[0][2] * m.m[2][0] * m.m[3][1]
					 - m.m[0][2] * m.m[2][1] * m.m[3][0]
					 - m.m[0][1] * m.m[2][0] * m.m[3][2]
					 - m.m[0][0] * m.m[2][2] * m.m[3][1]) / determinant,/// 42

					(-m.m[0][0] * m.m[1][1] * m.m[3][2]
					 - m.m[0][1] * m.m[1][2] * m.m[3][0]
					 - m.m[0][2] * m.m[1][0] * m.m[3][1]
					 + m.m[0][2] * m.m[1][1] * m.m[3][0]
					 + m.m[0][1] * m.m[1][0] * m.m[3][2]
					 + m.m[0][0] * m.m[1][2] * m.m[3][1]) / determinant,/// 43

					(+m.m[0][0] * m.m[1][1] * m.m[2][2]
					 + m.m[0][1] * m.m[1][2] * m.m[2][0]
					 + m.m[0][2] * m.m[1][0] * m.m[2][1]
					 - m.m[0][2] * m.m[1][1] * m.m[2][0]
					 - m.m[0][1] * m.m[1][0] * m.m[2][2]
					 - m.m[0][0] * m.m[1][2] * m.m[2][1]) / determinant /// 44
	};

}

Matrix4x4 Transpose(Matrix4x4 m) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[j][i];
		}
	}
	return result;
}


Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 resuit = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			resuit.m[i][j] = 0;
			if (i == j) {
				resuit.m[i][j] = 1;
			}
		}
	}
	return resuit;
}

void MatrixScreenPrintf(int x, int y, Matrix4x4& matrix, const char* name) {
	int kColumnWidth = 60;
	int kRowHeight = 20;
	if (name == nullptr) {
		for (int row = 0; row < 4; ++row) {
			for (int column = 0; column < 4; ++column) {
				Novice::ScreenPrintf(
					x + column * kColumnWidth,
					y + row * kRowHeight,
					"%6.02f",
					matrix.m[row][column]
				);
			}
		}
	} else {
		Novice::ScreenPrintf(x, y, "%s", name);
		for (int row = 0; row < 4; ++row) {
			for (int column = 0; column < 4; ++column) {
				Novice::ScreenPrintf(
					x + column * kColumnWidth,
					y + row * kRowHeight + kRowHeight,
					"%6.02f",
					matrix.m[row][column]
				);
			}
		}
	}
}

Matrix4x4 MakeScaleMatrix(const Vector3 scole) {
	return Matrix4x4{ scole.x,    0.0f,    0.0f, 0.0f,
						 0.0f, scole.y,    0.0f, 0.0f,
						 0.0f,    0.0f, scole.z, 0.0f,
						 0.0f,    0.0f,	   0.0f, 1.0f };
}

Matrix4x4 MakeRotateXMatrix(const float theta) {
	Matrix4x4 rX = { 1.0f,		   0.0f,         0.0f, 0.0f,
							0.0f,   cosf(theta),  sinf(theta), 0.0f,
							0.0f,  -sinf(theta),  cosf(theta), 0.0f,
							0.0f,	       0.0f,		 0.0f, 1.0f };
	return rX;
}

Matrix4x4 MakeRotateYMatrix(const float theta) {
	Matrix4x4 rY = { cosf(theta),		   0.0f, -sinf(theta), 0.0f,
							0.0f,		   1.0f,         0.0f, 0.0f,
					 sinf(theta),		   0.0f,  cosf(theta), 0.0f,
							0.0f,		   0.0f,		 0.0f, 1.0f };
	return rY;
}

Matrix4x4 MakeRotateZMatrix(const float theta) {
	Matrix4x4 rZ = { cosf(theta),   sinf(theta),		 0.0f, 0.0f,
					-sinf(theta),   cosf(theta),		 0.0f, 0.0f,
							0.0f,   	   0.0f,		 1.0f, 0.0f,
							0.0f,   	   0.0f,		 0.0f, 1.0f };
	return rZ;
}

Matrix4x4 MakeRotateMatrix(const Matrix4x4 thetaX, const Matrix4x4 thetaY, const Matrix4x4 thetaZ) {
	return Multiply(thetaX, Multiply(thetaY, thetaZ));
}

Matrix4x4 MakeTranslateMatrix(const Vector3 translate) {
	return Matrix4x4{ 1.0f,		  0.0f,		   0.0f, 0.0f,
							 0.0f,		  1.0f,		   0.0f, 0.0f,
							 0.0f,		  0.0f,		   1.0f, 0.0f,
					  translate.x, translate.y,	translate.z, 1.0f };
}

Matrix4x4 MakeAffineMatrix(Vector3 scale, Vector3 rotate, Vector3 translate) {
	Matrix4x4 r1 = MakeScaleMatrix(scale);

	Matrix4x4 r2 = MakeRotateMatrix(MakeRotateXMatrix(rotate.x),
		MakeRotateYMatrix(rotate.y),
		MakeRotateZMatrix(rotate.z));

	Matrix4x4 r3 = MakeTranslateMatrix(translate);

	//return Matrix4x4{ r3 * (r2 * r1) };
	//return Matrix4x4{ r1 * r2 * r3 };
	return Matrix4x4{ r1 * (r2 * r3) };
}


Matrix4x4 MatrixMix(Matrix4x4* matrix1, Matrix4x4* matrix2, Matrix4x4* matrix3, Matrix4x4* matrix4) {
	if (matrix4 == nullptr) { return Matrix4x4{ *matrix1 * *matrix2 * *matrix3 }; } else if (matrix3 == nullptr) { return Matrix4x4{ *matrix1 * *matrix2 }; } else { return Matrix4x4{ *matrix1 * *matrix2 * *matrix3 * *matrix4 }; }
}

/////////////////////////////////////////////////////////////////

Matrix4x4 MakeWorldMatrix(Matrix4x4 origin) {
	return origin;
}

Matrix4x4 MakeViewMatrix(Vector3 scole, Vector3 rotate, Vector3 translate) {
	return MakeAffineMatrix(scole, rotate, translate);
}

Matrix4x4 MakeProjectionMatrix(float leftO, float rightO, float topO, float bottomO, float nearO, float farO) {
	return{ 2.0f / (rightO - leftO),0.0f,0.0f,0.0f,
			0.0f,2.0f / (topO - bottomO),0.0f,0.0f,
			0.0f,0.0f,1.0f / (farO - nearO),0.0f,
			(leftO + rightO) / (leftO - rightO),(topO + bottomO) / (bottomO - topO),nearO / (nearO - farO),1.0f };
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	return { (1.0f / aspectRatio) * (1.0f / tanf(fovY / 2.0f)),					  0.0f,				 						   0.0f,0.0f,
														 0.0f,1.0f / (tanf(fovY / 2.0f)),				 					   0.0f,0.0f,
														 0.0f,					  0.0f,				 farClip / (farClip - nearClip),1.0f,
														 0.0f,					  0.0f,-(nearClip * farClip) / (farClip - nearClip),0.0f };
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minD, float maxD) {
	return { width / 2.0f,     			   0.0f,       0.0f,0.0f,
								 0.0f,     -(height / 2.0f),       0.0f,0.0f,
								 0.0f,     		       0.0f,maxD - minD,0.0f,
				left + (width / 2.0f),top + (height / 2.0f),       minD,1.0f };
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	return{ 2.0f / (right - left),0.0f,0.0f,0.0f,
			0.0f,2.0f / (top - bottom),0.0f,0.0f,
			0.0f,0.0f,1.0f / (farClip - nearClip),0.0f,
			(left + right) / (left - right),(top + bottom) / (bottom - top),nearClip / (nearClip - farClip),1.0f };
}

Vector3 viewFinilTransform(Vector3 obj, Matrix4x4 tranformMatrix) {
	Matrix4x4 objMatrix = MakeTranslateMatrix(obj) * tranformMatrix;
	if (objMatrix.m[3][3] != 0) {
		objMatrix.m[3][0] /= objMatrix.m[3][3];
		objMatrix.m[3][1] /= objMatrix.m[3][3];
		objMatrix.m[3][2] /= objMatrix.m[3][3];
		objMatrix.m[3][3] = 1.0f;
	} else {
		//assert(0);
	}
	return MakeTranslateVector3(objMatrix);
}

//////////////////////////////////////////////////////////////////////////陣列結合

#pragma endregion

#pragma region Geometry

void Draw3DLine(const Line& line, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color) {
	// 線分は両端をそれぞれスクリーン座標系まで変換し、Novice::DrawLineを利用して描画する
	Vector3 start = viewFinilTransform(viewFinilTransform(line.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = viewFinilTransform(viewFinilTransform(Add(line.origin, line.diff), viewProjectionMatrix), viewportMatrix);
	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
}

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;  // Gridの半分の幅
	const int kSubdivision = 10;   // 分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);  // 1つ分の長さ
	// 奥から手前への線を順々に引いていく
	for (int xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		// 上の情報を使ってワールド座標系上の始点と終点を求める
		Vector3 start = { -kGridHalfWidth + (kGridEvery * xIndex), 0.0f,  -kGridHalfWidth };
		Vector3 end = { -kGridHalfWidth + (kGridEvery * xIndex), 0.0f,  kGridHalfWidth };
		// スクリーン座標系まで変換をかける
		Vector3 startV2 = viewFinilTransform(start, viewProjectionMatrix);
		Vector3 endV2 = viewFinilTransform(end, viewProjectionMatrix);
		Vector3 startV3 = viewFinilTransform(startV2, viewportMatrix);
		Vector3 endV3 = viewFinilTransform(endV2, viewportMatrix);

		// 変換した座標を使って表示。色は薄い灰色(0xAAAAAAFF)、原点は黒ぐらいが良いが、何でも良い
		int color1 = 0xAAAAAAFF;
		int color2 = 0x000000FF;
		if (xIndex == 5) {
			Novice::DrawLine((int)startV3.x, (int)startV3.y,
				(int)endV3.x, (int)endV3.y,
				color2);
		} else {
			Novice::DrawLine((int)startV3.x, (int)startV3.y,
				(int)endV3.x, (int)endV3.y,
				color1);
		}
	}
	// 左から右も同じように順々に引いていく
	for (int zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		// 奥から手前が左右に変わるだけ

		// 上の情報を使ってワールド座標系上の始点と終点を求める
		Vector3 start = { -kGridHalfWidth , 0.0f, -kGridHalfWidth + kGridEvery * zIndex };
		Vector3 end = { kGridHalfWidth , 0.0f, -kGridHalfWidth + kGridEvery * zIndex };

		// スクリーン座標系まで変換をかける
		Vector3 startV2 = viewFinilTransform(start, viewProjectionMatrix);
		Vector3 endV2 = viewFinilTransform(end, viewProjectionMatrix);
		Vector3 startV3 = viewFinilTransform(startV2, viewportMatrix);
		Vector3 endV3 = viewFinilTransform(endV2, viewportMatrix);

		// 変換した座標を使って表示。色は薄い灰色(0xAAAAAAFF)、原点は黒ぐらいが良いが、何でも良い
		int color1 = 0xAAAAAAFF;
		int color2 = 0x000000FF;
		if (zIndex == 5) {
			Novice::DrawLine((int)startV3.x, (int)startV3.y,
				(int)endV3.x, (int)endV3.y,
				color2);
		} else {
			Novice::DrawLine((int)startV3.x, (int)startV3.y,
				(int)endV3.x, (int)endV3.y,
				color1);
		}
	}
}

float Lerp(float a, float b, int c, int t) {
	float time = float(c) / t;
	return (time)*a + (1.0f - time) * b;
}

Vector2 Bezier(const Vector2 p0, const Vector2 p1, const Vector2 p2, int time, int clock) {
	Vector2 Np0 = {
		Lerp(p0.x,p1.x,time,clock),
		Lerp(p0.y,p1.y,time,clock)
	};
	Vector2 Np1 = {
		Lerp(p1.x,p2.x,time,clock),
		Lerp(p1.y,p2.y,time,clock)
	};
	return {
		Lerp(Np0.x,Np1.x,time,clock),
		Lerp(Np0.y,Np1.y,time,clock)
	};
}


Vector3 Bezier(const Vector3 p0, const Vector3 p1, const Vector3 p2, int time, int clock) {
	Vector3 Np0 = {
		Lerp(p0.x,p1.x,time,clock),
		Lerp(p0.y,p1.y,time,clock),
		Lerp(p0.z,p1.z,time,clock)
	};
	Vector3 Np1 = {
		Lerp(p1.x,p2.x,time,clock),
		Lerp(p1.y,p2.y,time,clock),
		Lerp(p1.z,p2.z,time,clock)
	};
	return {
		Lerp(Np0.x,Np1.x,time,clock),
		Lerp(Np0.y,Np1.y,time,clock),
		Lerp(Np0.z,Np1.z,time,clock)
	};
}

void DrawBezier(const Vector3 p0, const Vector3 p1, const Vector3 p2, int function, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color) {
	Vector3 pointL = p0;
	Vector3 pointN = p0;
	for (int i = 1; i < function + 1; i++) {
		pointL = pointN;
		pointN = Bezier(p2, p1, p0, i, function );
		Draw3DLine({ pointL,{pointN - pointL} }, viewProjectionMatrix, viewportMatrix, color);
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color) {
	const int kSubdivision = 24; // 分割数
	const float kLonEvery = M_PI / kSubdivision; // 経度分割1つ分の角度
	const float kLatEvery = 2.0f * M_PI / kSubdivision; // 緯度分割1つ分の角度
	// 緯度方向に分割 -π/2 ～ π/2
	for (int latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -M_PI / 2.0f + kLatEvery * latIndex; // 現在の緯度
		// 経度方向に分割 0 ～ 2π
		for (int lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; // 現在の経度
			// ワールド座標系でのa, b, cを計算
			///Vector3 a, b, c;
			Vector3 a = { sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
						  sphere.center.y + sphere.radius * sinf(lat),
						  sphere.center.z + sphere.radius * cosf(lat) * sinf(lon) };

			Vector3 b = { sphere.center.x + sphere.radius * cosf(lat) * cosf(lon + kLonEvery),
						  sphere.center.y + sphere.radius * sinf(lat),
						  sphere.center.z + sphere.radius * cosf(lat) * sinf(lon + kLonEvery) };

			Vector3 c = { sphere.center.x + sphere.radius * cosf(lat + kLatEvery) * cosf(lon),
						  sphere.center.y + sphere.radius * sinf(lat + kLatEvery),
						  sphere.center.z + sphere.radius * cosf(lat + kLatEvery) * sinf(lon) };

			// a, b, cをスクリーン座標系に変換

			Vector3 aV2 = viewFinilTransform(a, viewProjectionMatrix);
			Vector3 bV2 = viewFinilTransform(b, viewProjectionMatrix);
			Vector3 cV2 = viewFinilTransform(c, viewProjectionMatrix);
			Vector3 aV3 = viewFinilTransform(aV2, viewportMatrix);
			Vector3 bV3 = viewFinilTransform(bV2, viewportMatrix);
			Vector3 cV3 = viewFinilTransform(cV2, viewportMatrix);

			// abとbcの線分を描画
			Novice::DrawLine((int)aV3.x, (int)aV3.y,
				(int)bV3.x, (int)bV3.y, color);
			Novice::DrawLine((int)aV3.x, (int)aV3.y,
				(int)cV3.x, (int)cV3.y, color);
		}
	}
}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color) {
	for (int i = 0; i < 3; i++) {
		Vector3 end;
		Vector3 start = viewFinilTransform(viewFinilTransform(triangle.vertex[i], viewProjectionMatrix), viewportMatrix);
		if (i != 2) {
			end = viewFinilTransform(viewFinilTransform(triangle.vertex[i + 1], viewProjectionMatrix), viewportMatrix);
		} else {
			end = viewFinilTransform(viewFinilTransform(triangle.vertex[0], viewProjectionMatrix), viewportMatrix);
		}
		Novice::DrawLine((int)start.x, (int)start.y,
			(int)end.x, (int)end.y, color);
	}
}

Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y, vector.x, 0.0f }; // 1
	}
	return Vector3(0.0f, -vector.z, vector.y);
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color) {
	Vector3 center = Multiply(plane.distance, plane.normal); // 1
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal)); // 2
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z }; // 3
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]); // 4
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z }; // 5
	// 6
	Vector3 points[4];
	for (int index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = viewFinilTransform(viewFinilTransform(point, viewProjectionMatrix), viewportMatrix);
	}
	// pointsをそれぞれ結んでDrawLineで矩形を描画する。DrawTriangleを使って塗りつぶしても良いが、DepthがないのでMT3では分かりづらい
	Novice::DrawLine((int)points[0].x, (int)points[0].y,
		(int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[2].x, (int)points[2].y,
		(int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y,
		(int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y,
		(int)points[0].x, (int)points[0].y, color);
}



Vector3 Project(const Vector3& v1, const Vector3& v2) {
	Vector3 b = Normalize(v2);
	return Dot(v1, b) * b;
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 resuit = {};
	float divisions = 100.0f;
	Segment targetLine = segment;

	for (float t = 0; t < divisions; t++) {
		Vector3 now = targetLine.origin + (targetLine.diff / divisions) * t;
		if (Length(Project(point, resuit)) < Length(Project(point, now))) {
			resuit = now;
		}
	}
	return resuit;
}

#pragma endregion


#pragma region Other
bool BinaryComparator(int binary, int target) {
	if (binary == (target & binary)) {
		return true;
	}
	return false;
}
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	return { (v1.y * v2.z) - (v1.z * v2.y),
			 (v1.z * v2.x) - (v1.x * v2.z),
			 (v1.x * v2.y) - (v1.y * v2.x) };
}
#pragma endregion

