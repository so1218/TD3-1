#pragma once

#include "Structures.h"

//矩形と矩形の当たり判定の関数
bool CheckRectangleRectangleCollision(RectangleObject* rect1, RectangleObject* rect2);

void ApplyKnockback(Knockback* knockback, RectangleObject* rect1, RectangleObject* rect2, Vector2* beDonePos, Vector2* doPos);

