#include "Structures.h"
#include "Calculate.h"
#include "Easing.h"

//2次曲線のベジエ曲線
Vector2 QuadraticBezier(Vector2 p0, Vector2 p1, Vector2 p2, Easing* easing)
{
    float t = easing->easeTimer;

    // (1 - t)^2 * p0 + 2 * (1 - t) * t * p1 + t^2 * p2
    float u = 1 - t;  // (1 - t)
    float tt = t * t; // t^2
    float ut = u * t; // (1 - t) * t

    float x = u * u * p0.x + 2 * ut * p1.x + tt * p2.x;
    float y = u * u * p0.y + 2 * ut * p1.y + tt * p2.y;

    return Vector2(x, y);
}

//3次曲線のベジエ曲線
Vector2 CubicBezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, Easing* easing)
{
    float t = easing->easeTimer;

    // (1 - t)^3 * p0 + 3 * (1 - t)^2 * t * p1 + 3 * (1 - t) * t^2 * p2 + t^3 * p3
    float u = 1 - t;  // (1 - t)
    float tt = t * t; // t^2
    float ttt = tt * t; // t^3
    float ut = u * t;  // (1 - t) * t
    float uuu = u * u * u; // (1 - t)^3
    float uut = u * ut; // (1 - t)^2 * t
    float utt = u * tt; // (1 - t) * t^2

    float x = uuu * p0.x + 3 * uut * p1.x + 3 * utt * p2.x + ttt * p3.x;
    float y = uuu * p0.y + 3 * uut * p1.y + 3 * utt * p2.y + ttt * p3.y;

    return Vector2(x, y);
}

Vector2 QuinticBezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Vector2 p5, Easing* easing) 
{
    float t = easing->easeTimer;

    float u = 1.0f - t;
    float tt = t * t;
    float ttt = tt * t;
    float u2 = u * u;
    float u3 = u2 * u;
    float u4 = u3 * u;
    float u5 = u4 * u;

    float coef1 = u5;
    float coef2 = 5.0f * u4 * t;
    float coef3 = 10.0f * u3 * tt;
    float coef4 = 10.0f * u2 * ttt;
    float coef5 = 5.0f * u * ttt;
    float coef6 = t * ttt * t;

    Vector2 result;
    result.x = coef1 * p0.x + coef2 * p1.x + coef3 * p2.x + coef4 * p3.x + coef5 * p4.x + coef6 * p5.x;
    result.y = coef1 * p0.y + coef2 * p1.y + coef3 * p2.y + coef4 * p3.y + coef5 * p4.y + coef6 * p5.y;

    return result;
}
