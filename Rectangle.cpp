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

void CalcVertexCenterRectangle(RectangleObject* ro) {
    if (ro == nullptr) return; // nullptr チェック

    ro->wVertex.LT.x = ro->wCenterPos.x - ro->width / 2;
    ro->wVertex.LT.y = ro->wCenterPos.y + ro->height / 2;
    ro->wVertex.RT.x = ro->wCenterPos.x + ro->width / 2;
    ro->wVertex.RT.y = ro->wCenterPos.y + ro->height / 2;
    ro->wVertex.LB.x = ro->wCenterPos.x - ro->width / 2;
    ro->wVertex.LB.y = ro->wCenterPos.y - ro->height / 2;
    ro->wVertex.RB.x = ro->wCenterPos.x + ro->width / 2;
    ro->wVertex.RB.y = ro->wCenterPos.y - ro->height / 2;
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

void ConvertScreenToWorldRectangle(RectangleObject* ro) {
    if (ro == nullptr) return; // nullptr チェック

    ro->wVertex = ro->sVertex;
    ro->wVertex.LT.y -= kWindowHeight;
    ro->wVertex.LT.y *= -1.0f;
    ro->wVertex.RT.y -= kWindowHeight;
    ro->wVertex.RT.y *= -1.0f;
    ro->wVertex.LB.y -= kWindowHeight;
    ro->wVertex.LB.y *= -1.0f;
    ro->wVertex.RB.y -= kWindowHeight;
    ro->wVertex.RB.y *= -1.0f;
}



