#include "Structures.h"
#include <assert.h>
#include "Rectangle.h"

//掛け算行列の関数
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2)
{
	return
	{
		matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0],
		matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1],
		matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2],
		matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0],
		matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1],
		matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2],
		matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0],
		matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1],
		matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2],
	};
}

//逆行列の関数
Matrix3x3 InverseMatrix(Matrix3x3 matrix)
{
	Matrix3x3 InverseMatrix;
	float determinant = matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1])
		- matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0])
		+ matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);

	InverseMatrix.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) / determinant;
	InverseMatrix.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) / determinant;
	InverseMatrix.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) / determinant;
	InverseMatrix.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) / determinant;
	InverseMatrix.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) / determinant;
	InverseMatrix.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) / determinant;
	InverseMatrix.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) / determinant;
	InverseMatrix.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) / determinant;
	InverseMatrix.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) / determinant;

	return InverseMatrix;

}

//回転行列の関数
Matrix3x3 MakeRotateMatrix(float theta)
{
	Matrix3x3 rotateMatrix;

	rotateMatrix.m[0][0] = cosf(theta);
	rotateMatrix.m[0][1] = sinf(theta);
	rotateMatrix.m[0][2] = 0;
	rotateMatrix.m[1][0] = -sinf(theta);
	rotateMatrix.m[1][1] = cosf(theta);
	rotateMatrix.m[1][2] = 0;
	rotateMatrix.m[2][0] = 0;
	rotateMatrix.m[2][1] = 0;
	rotateMatrix.m[2][2] = 1;

	return rotateMatrix;
}

//スケーリング行列の関数
Matrix3x3 MakeScaleMatrix(Vector2 scale)
{
	Matrix3x3 scaleMatrix;

	scaleMatrix.m[0][0] = scale.x;
	scaleMatrix.m[0][1] = 0;
	scaleMatrix.m[0][2] = 0;
	scaleMatrix.m[1][0] = 0;
	scaleMatrix.m[1][1] = scale.y;
	scaleMatrix.m[1][2] = 0;
	scaleMatrix.m[2][0] = 0;
	scaleMatrix.m[2][1] = 0;
	scaleMatrix.m[2][2] = 1;

	return scaleMatrix;
}


//平行移動行列の関数
Matrix3x3 MakeTranslateMatrix(Vector2 translate)
{
	Matrix3x3 translateMatrix;

	translateMatrix.m[0][0] = 1;
	translateMatrix.m[0][1] = 0;
	translateMatrix.m[0][2] = 0;
	translateMatrix.m[1][0] = 0;
	translateMatrix.m[1][1] = 1;
	translateMatrix.m[1][2] = 0;
	translateMatrix.m[2][0] = translate.x;
	translateMatrix.m[2][1] = translate.y;
	translateMatrix.m[2][2] = 1;

	return translateMatrix;
}

//ベクトルと3x3行列を使って、アフィン変換を行い、新しいベクトルを計算
Vector2 Transform(Vector2 vector, Matrix3x3 matrix)
{
	Vector2 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];


	result.x /= w;
	result.y /= w;
	return result;
}

//アフィン行列の関数
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate)
{
	//拡縮の行列
	Matrix3x3 scaleMatrix = MakeScaleMatrix(scale);

	//回転の行列
	Matrix3x3 rotateMatrix = MakeRotateMatrix(rotate);

	//平行移動の行列
	Matrix3x3 translateMatrix = MakeTranslateMatrix(translate);

	Matrix3x3 scaleRotateMatrix = Multiply(scaleMatrix, rotateMatrix);
	Matrix3x3 affineMatrix = Multiply(scaleRotateMatrix, translateMatrix);

	return affineMatrix;
}

//正射影行列の関数
Matrix3x3 MakeOrthographicMatrix(float left, float top,
	float right, float bottom)
{
	Matrix3x3 result;

	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0.0f;

	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);
	result.m[2][2] = 1.0f;

	return result;
}

//ビューポート行列の関数
Matrix3x3 MakeViewportMatrix(float left, float top,
	float right, float bottom)
{
	Matrix3x3 result;

	result.m[0][0] = (right - left) / 2.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -(bottom - top) / 2.0f;
	result.m[1][2] = 0.0f;

	result.m[2][0] = left + (right - left) / 2.0f;
	result.m[2][1] = top + (bottom - top) / 2.0f;
	result.m[2][2] = 1.0f;

	return result;
}