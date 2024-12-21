#include "Structures.h"


void CalcVertexRectangle(RectangleObject* ro) 
{
    if (ro == nullptr) return; // nullptr チェック

    ro->sDrawVertex.LT.x = ro->pos.x - ro->width / 2;
    ro->sDrawVertex.LT.y = ro->pos.y + ro->height / 2;
    ro->sDrawVertex.RT.x = ro->pos.x + ro->width / 2;
    ro->sDrawVertex.RT.y = ro->pos.y + ro->height / 2;
    ro->sDrawVertex.LB.x = ro->pos.x - ro->width / 2;
    ro->sDrawVertex.LB.y = ro->pos.y - ro->height / 2;
    ro->sDrawVertex.RB.x = ro->pos.x + ro->width / 2;
    ro->sDrawVertex.RB.y = ro->pos.y - ro->height / 2;
}

//ワールドの四隅の頂点を特定
void CalcWorldVertexRectangle(RectangleObject* ro)
{
    if (ro == nullptr) return; // nullptr チェック

    ro->wVertex.LT.x = ro->wPos.x - ro->width / 2;
    ro->wVertex.LT.y = ro->wPos.y + ro->height / 2;
    ro->wVertex.RT.x = ro->wPos.x + ro->width / 2;
    ro->wVertex.RT.y = ro->wPos.y + ro->height / 2;
    ro->wVertex.LB.x = ro->wPos.x - ro->width / 2;
    ro->wVertex.LB.y = ro->wPos.y - ro->height / 2;
    ro->wVertex.RB.x = ro->wPos.x + ro->width / 2;
    ro->wVertex.RB.y = ro->wPos.y - ro->height / 2;
}

void CalcCameraVertexRectangle(RectangleObject* ro)
{
    if (ro == nullptr) return; // nullptr チェック

    ro->sDrawVertex.LT.x = -ro->width / 2;
    ro->sDrawVertex.LT.y = ro->height / 2;
    ro->sDrawVertex.RT.x = ro->width / 2;
    ro->sDrawVertex.RT.y = ro->height / 2;
    ro->sDrawVertex.LB.x = -ro->width / 2;
    ro->sDrawVertex.LB.y = -ro->height / 2;
    ro->sDrawVertex.RB.x = ro->width / 2;
    ro->sDrawVertex.RB.y = -ro->height / 2;
}

void ConvertWorldToScreenRectangle(RectangleObject* ro)
{
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

void ConvertScreenToWorldRectangle(RectangleObject* ro)
{
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



