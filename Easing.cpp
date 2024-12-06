#include "Structures.h"
#include "Easing.h"

//========================================================
// イージングの関数
//========================================================

float EaseIn(const float& t)
{

	return 1.0f - sqrtf(1.0f - t * t);

}

float EaseOut(const float& t) 
{

	return sqrtf(1.0f - (t - 1.0f) * (t - 1.0f));

}



float EaseInOut(float& t)
{

	t *= 2;

	if (t < 1) {
		return 0.5f * (1 - (float)sqrt(1 - t * t)); // easeIn
	}
	else {
		t -= 2; // easeOutに移る
		return 0.5f * ((float)sqrt(1 - t * t) + 1); // easeOut
	}

}

float EaseOutBack(const float& t)
{
	// バックの強さ。
	const float s1 = 6.00158f; 
	const float s2 = s1 + 1;

	// EaseOutBackの計算式
	return 1 + s2 * powf(t - 1, 3) + s1 * powf(t - 1, 2);
}

float EaseInOutBack(const float& t)
{
	const float s1 = 6.00158f;
	const float s2 = s1 + 1;

	if (t < 0.5f) {
		// EaseInBack部分
		return 0.5f * (t * t * ((s2 + 1) * t - s2));
	}
	else {
		// EaseOutBack部分
		return 0.5f * (t * t * ((s2 + 1) * t - s2) + 2);
	}
}

float EaseInBounce(const float& t)
{
	return 1.0f - EaseOutBounce(1.0f - t);
}

float EaseOutBounce(const float& t)
{
	if (t < (1 / 2.75f))
	{
		return 7.5625f * t * t;
	}
	else if (t < (2 / 2.75f))
	{
		float t_ = t - (1.5f / 2.75f);
		return 7.5625f * t_ * t_ + 0.75f;
	}
	else if (t < (2.5 / 2.75f))
	{
		float t_ = t - (2.25f / 2.75f);
		return 7.5625f * t_ * t_ + 0.9375f;
	}
	else
	{
		float t_ = t - (2.625f / 2.75f);
		return 7.5625f * t_ * t_ + 0.984375f;
	}
}

float EaseInOutBounce(const float& t)
{
	if (t < 0.5f)
	{
		// 前半 EaseInBounce
		return 0.5f * EaseInBounce(t * 2.0f);
	}
	else
	{
		// 後半 EaseOutBounce
		return 0.5f * EaseOutBounce(t * 2.0f - 1.0f) + 0.5f;
	}
}

//========================================================
// イージング用のタイマーの関数
//========================================================

// EaseInOutのイージングタイマー
void CountEaseInOutTimer(Easing& easing) 
{

	if (easing.timer > 1.0f) 
	{

		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else 
	{

		easing.timer += easing.interval;
		easing.easeTimer = EaseInOut(easing.timer);

	}

}



void CountEaseInOutTimer(const unsigned int end, unsigned int& current, Easing& easing) 
{

	if (easing.timer > 1.0f) 
	{

		current = end;
		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else 
	{

		easing.timer += easing.interval;
		easing.easeTimer = EaseInOut(easing.timer);

	}
}

void CountEaseInOutTimer(const int end, int& current, Easing& easing)
{

	if (easing.timer > 1.0f) {

		current = end;
		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else {

		easing.timer += easing.interval;
		easing.easeTimer = EaseInOut(easing.timer);

	}

}

void CountEaseInOutTimer(const float end, float& current, Easing& easing)
{

	if (easing.timer > 1.0f) {

		current = end;
		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else {

		easing.timer += easing.interval;
		easing.easeTimer = EaseInOut(easing.timer);

	}

}

void CountEaseInOutTimer(const Vector2 end, Vector2& current, Easing& easing)
{

	if (easing.timer > 1.0f) {

		current = end;
		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else {

		easing.timer += easing.interval;
		easing.easeTimer = EaseInOut(easing.timer);

	}
}

//EaseOutのイージングタイマー
void CountEaseOutTimer(Easing& easing)
{

	if (easing.timer > 1.0f) {

		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else {

		easing.timer += easing.interval;
		easing.easeTimer = EaseOut(easing.timer);

	}

}

void CountSwapEaseOutTimer(Easing& easing)
{
	if (easing.timer > 1.0f) {
		easing.easeTimer = 0.0f;
		

		if (easing.isReverse)
		{
			easing.isEase = false;
		}
		
		easing.isReverse = !easing.isReverse; // 補間方向を反転

		
		easing.timer = 0.0f;
	}
	else {
		easing.timer += easing.interval;
		easing.easeTimer = EaseOut(easing.timer);
	}
}

//EaseInのイージングタイマー
void CountEaseInTimer(Easing& easing)
{

	if (easing.timer > 1.0f)
	{

		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else {

		easing.timer += easing.interval;
		easing.easeTimer = EaseIn(easing.timer);

	}

}

//EaseOutBackのイージングタイマー
void CountEaseOutBackTimer(Easing& easing)
{

	if (easing.timer > 1.0f) {

		easing.easeTimer = 0.0f;
		easing.timer = 0.0f;
		easing.isEase = false;

	}
	else {

		easing.timer += easing.interval;
		easing.easeTimer = EaseOutBack(easing.timer);

	}

}

//線形補間関数(LinearInterpolation)

// 色遷移のイージング関数
void ColorLinearInterpolation(const unsigned int start, const unsigned int end, unsigned int& current, const Easing& easing)
{

	//赤
	unsigned int startR = (start >> 24) & 0xff;

	//緑
	unsigned int startG = (start >> 16) & 0xff;

	//青
	unsigned int startB = (start >> 8) & 0xff;

	//透明度
	unsigned int startA = start & 0xff;

	unsigned int endR = (end >> 24) & 0xff;
	unsigned int endG = (end >> 16) & 0xff;
	unsigned int endB = (end >> 8) & 0xff;
	unsigned int endA = end & 0xff;

	// 各成分を補間
	unsigned int newR = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(startR) + easing.easeTimer * static_cast<float>(endR));
	unsigned int newG = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(startG) + easing.easeTimer * static_cast<float>(endG));
	unsigned int newB = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(startB) + easing.easeTimer * static_cast<float>(endB));
	unsigned int newA = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(startA) + easing.easeTimer * static_cast<float>(endA));

	current = (newR << 24) | (newG << 16) | (newB << 8) | newA;

}

// 色遷移のイージング関数(startの色に戻る)
void ColorReverseLinearInterpolation(unsigned int start, unsigned int end, unsigned int& current, Easing& easing)
{
	// 赤
	unsigned int startR = (start >> 24) & 0xff;
	unsigned int startG = (start >> 16) & 0xff;
	unsigned int startB = (start >> 8) & 0xff;
	unsigned int startA = start & 0xff;

	unsigned int endR = (end >> 24) & 0xff;
	unsigned int endG = (end >> 16) & 0xff;
	unsigned int endB = (end >> 8) & 0xff;
	unsigned int endA = end & 0xff;

	// 補間方向が切り替わるまで
	unsigned int newR, newG, newB, newA;

	if (!easing.isReverse)
	{
		// 現在の補間方向に基づいて色を補間
		newR = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(startR) + easing.easeTimer * static_cast<float>(endR));
		newG = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(startG) + easing.easeTimer * static_cast<float>(endG));
		newB = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(startB) + easing.easeTimer * static_cast<float>(endB));
		newA = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(startA) + easing.easeTimer * static_cast<float>(endA));
	}
	else
	{
		// 補間の反転
		newR = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(endR) + easing.easeTimer * static_cast<float>(startR));
		newG = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(endG) + easing.easeTimer * static_cast<float>(startG));
		newB = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(endB) + easing.easeTimer * static_cast<float>(startB));
		newA = static_cast<unsigned int>((1.0f - easing.easeTimer) * static_cast<float>(endA) + easing.easeTimer * static_cast<float>(startA));
	}

	// 結果をcurrentに設定
	current = (newR << 24) | (newG << 16) | (newB << 8) | newA;
}

void LinearInterpolation(const int start, const int end, int& current, const Easing& easing) 
{

	current = static_cast<int>((1.0f - easing.easeTimer) * static_cast<float>(start) + easing.easeTimer * static_cast<float>(end));

}

void LinearInterpolation(const float start, const float end, float& current, const Easing& easing)
{

	current = (1.0f - easing.easeTimer) * start + easing.easeTimer * end;

}

void LinearInterpolation(const Vector2& start, const Vector2& end, Vector2& current, const Easing& easing)
{

	LinearInterpolation(start.x, end.x, current.x, easing);
	LinearInterpolation(start.y, end.y, current.y, easing);

}

void InitializeEasing(Easing& easing)
{

	easing.interval = 0.01f;
	easing.cycle = 0.0f;
	easing.timer = 0.0f;
	easing.easeTimer = 0.0f;
	easing.isEase = false;

}


