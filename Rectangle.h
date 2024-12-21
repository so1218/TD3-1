#pragma once

#include "Structures.h"


void CalcVertexRectangle(RectangleObject* ro);

//ワールドの四隅の頂点を特定
void CalcWorldVertexRectangle(RectangleObject* ro);

void CalcCameraVertexRectangle(RectangleObject* ro);

void ConvertWorldToScreenRectangle(RectangleObject* ro);

void ConvertScreenToWorldRectangle(RectangleObject* ro);

