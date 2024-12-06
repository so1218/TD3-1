#include "Structures.h"

// 階乗関数
int Factorial(int n)
{

	if (n < 2)
	{

		return 1;

	}

	return n * Factorial(n - 1);

}

// 指数関数
float Power(float t, int n)
{

	if (n < 1) 
	{

		return 1.0f;

	}

	return t * Power(t, n - 1);

}

// 二項係数関数
int Binomial(int n, int k)
{

	return Factorial(n) / (Factorial(k) * Factorial(n - k));

}

// バーンスタイン基底関数
float Bernstein(int n, int i, float t)
{

	return static_cast<float>(Binomial(n, i)) * Power(t, i) * Power(1 - t, n - i);

}

//2点の距離の関数
float CalculateDistance(const Vector2& a, const Vector2& b) 
{

	return sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));

}

//ベクトルの正規化の関数
Vector2 CalculateNormalize(Vector2& vec)
{
	float length = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (length == 0)
	{
		return Vector2(0, 0);
	}

	// 正規化されたベクトルを返す
	return Vector2(vec.x / length, vec.y / length);
}

//回転の関数
Vector2 Rotate(Vector2 v, float angle)
{
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	return Vector2
	(
		cosAngle * v.x - sinAngle * v.y,
		sinAngle * v.x + cosAngle * v.y
	);
}
