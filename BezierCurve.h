#pragma once

#include "Structures.h"

// ベジェ曲線計算関数
Vector2 QuadraticBezier(Vector2 p0, Vector2 p1, Vector2 p2, Easing* easing);

Vector2 CubicBezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, Easing* easing);

Vector2 QuinticBezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Vector2 p5, Easing* easing);