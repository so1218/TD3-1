#pragma once
#include "Structures.h"


/// <summary>
/// 矩形の描画関数
/// </summary>
/// <param name="ro">RectangleObject構造体</param>
/// <param name="srcW">画像の描画横幅</param>
/// <param name="srcH">画像の描画縦幅</param>
/// <param name="GH">グラフハンドル</param>
/// <param name="spriteNumX">横の何番目の画像か</param>
/// <param name="spriteNumY">縦の何番目の画像か</param>
/// <param name="color">色</param>
void DrawQuadWithData(RectangleObject* ro, float srcW, float srcH, int GH, int spriteNumX, int spriteNumY, unsigned int color);

unsigned int HSVtoColorCode(float h, float s, float v);