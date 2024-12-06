#include "Structures.h"
#include "Calculate.h"

//========================================================
// 当たり判定の関数
//========================================================

//矩形と矩形の当たり判定の関数
bool CheckRectangleRectangleCollision(RectangleObject* rect1, RectangleObject* rect2)
{

    if (rect1->wVertex.RT.x < rect2->wVertex.LT.x)
        return false;
   
    if (rect1->wVertex.LT.x > rect2->wVertex.RT.x)
        return false;
    
    if (rect1->wVertex.LT.y < rect2->wVertex.RB.y)
        return false;
    
    if (rect1->wVertex.RB.y > rect2->wVertex.LT.y)
        return false;

    // 矩形が重なっている
    return true;

}

void ApplyKnockback(Knockback* knockback, RectangleObject* rect1, RectangleObject* rect2, Vector2* beDonePos, Vector2* doPos)
{
	if (CheckRectangleRectangleCollision(rect1, rect2))
	{

		knockback->dir = { beDonePos->x - doPos->x, beDonePos->y - doPos->y };

		knockback->normalizedDir = CalculateNormalize(knockback->dir);

		knockback->velocity.x = knockback->normalizedDir.x * knockback->strength;
		knockback->velocity.y = knockback->normalizedDir.y * knockback->strength;

		knockback->isKnockback = true;


	}

	if (knockback->isKnockback)
	{
		knockback->velocity.x *= 0.95f;
		knockback->velocity.y *= 0.95f;
		beDonePos->x += knockback->velocity.x;
		beDonePos->y += knockback->velocity.y;
	}
	if (fabs(knockback->velocity.x) < 0.1f || fabs(knockback->velocity.y) < 0.1f)
	{
		knockback->isKnockback = false;
		knockback->velocity.x = 0.0f;
		knockback->velocity.y = 0.0f;
	}
}

