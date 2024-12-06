#include "Structures.h"


void CalcVertexRectangle(RectangleObject* ro) {
    if (ro == nullptr) return; // nullptr チェック

    ro->wVertex.LT.x = ro->pos.x - ro->width / 2;
    ro->wVertex.LT.y = ro->pos.y + ro->height / 2;
    ro->wVertex.RT.x = ro->pos.x + ro->width / 2;
    ro->wVertex.RT.y = ro->pos.y + ro->height / 2;
    ro->wVertex.LB.x = ro->pos.x - ro->width / 2;
    ro->wVertex.LB.y = ro->pos.y - ro->height / 2;
    ro->wVertex.RB.x = ro->pos.x + ro->width / 2;
    ro->wVertex.RB.y = ro->pos.y - ro->height / 2;
}

void ConvertWorldToScreenRectangle(RectangleObject* ro) {
    if (ro == nullptr) return; // nullptr チェック

    ro->sVertex = ro->wVertex;
    ro->sVertex.LT.y -= kWindowHeight;
    ro->sVertex.LT.y *= -1.0f;
    ro->sVertex.RT.y -= kWindowHeight;
    ro->sVertex.RT.y *= -1.0f;
    ro->sVertex.LB.y -= kWindowHeight;
    ro->sVertex.LB.y *= -1.0f;
    ro->sVertex.RB.y -= kWindowHeight;
    ro->sVertex.RB.y *= -1.0f;
}



