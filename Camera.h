#pragma once

#include "Structures.h"

//矩形の単体シェイク処理
void RectangleShakeCamera(RectangleObject* ro);

// カメラ更新

//プレイヤーのワールド行列
Matrix3x3 MakePlayerWorldMatrix(const RectangleObject* ro, const Camera& camera);

//カメラのワールド行列
Matrix3x3 MakeCameraWorldMatrix(const Camera& camera);

//ビュー行列
Matrix3x3 MakeViewMatrix(const Camera& camera);

//正射影行列
Matrix3x3 MakeOrthographicMatrix();

//ビューポート行列
Matrix3x3 MakeViewportMatrix();

//矩形をカメラ座標に変換
void MakeCameraMatrix(RectangleObject* ro, const Camera& camera);

//矩形のカメラのデバッグ用関数
void DebugCameraRectangle(GameManager* gm, RectangleObject* ro);