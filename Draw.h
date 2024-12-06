#pragma once
#include "Structures.h"

void DrawQuadWithData(RectangleObject* ro, float srcW, float srcH, int GH, int spriteNum, unsigned int color);

unsigned int HSVtoColorCode(float h, float s, float v);