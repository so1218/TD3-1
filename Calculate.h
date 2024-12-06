#pragma once

#include "Structures.h"

// 階乗関数
int Factorial(int n);

// 指数関数
float Power(float t, int n);

// 二項係数関数
int Binomial(int n, int k);

// バーンスタイン基底関数
float Bernstein(int n, int i, float t);

//2点の距離の関数
float CalculateDistance(const Vector2& a, const Vector2& b);

//ベクトルの正規化の関数
Vector2 CalculateNormalize(Vector2& vec);

