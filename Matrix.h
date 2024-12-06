#pragma once

#include "Structures.h"

//掛け算行列の関数
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

//逆行列の関数
Matrix3x3 InverseMatrix(Matrix3x3 matrix);

//回転行列の関数
Matrix3x3 MakeRotateMatrix(float theta);

//スケーリング行列の関数
Matrix3x3 MakeScaleMatrix(Vector2 scale);

//平行移動行列の関数
Matrix3x3 MakeTranslateMatrix(Vector2 translate);
Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

//アフィン行列の関数
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);

//正射影行列の関数
Matrix3x3 MakeOrthographicMatrix(float left, float top,
	float right, float bottom);

//ビューポート行列の関数
Matrix3x3 MakeViewportMatrix(float left, float top,
	float right, float bottom);
