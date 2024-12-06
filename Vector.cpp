#include "Structures.h"

void AddVector(const Vector2* v1, const Vector2* v2, Vector2* v3) {
    if (v1 == nullptr || v2 == nullptr || v3 == nullptr) return; // nullptr チェック

    v3->x = v1->x + v2->x;
    v3->y = v1->y + v2->y;
}

void SwapVector(Vector2* vector) {
    if (vector == nullptr) return; // nullptr チェック

    vector[1].x = static_cast<float>(static_cast<int>(vector[1].x) ^ 25);
    vector[1].y = static_cast<float>(static_cast<int>(vector[1].y) ^ 25);
}
