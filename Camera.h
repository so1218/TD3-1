#pragma once

#include "Structures.h"

class Camera
{
public:

    //コンストラクタ
    Camera();

    //メンバ変数

    // カメラの振れ幅、シェイクの信号
    bool isShake = false;

    // シェイク関係
    int shakeDuration = 20;
    int shakeCounter = 0;
    int magnitude = 15;
    IntVector2 shakingPos = {};
    Matrix3x3 cameraMatrix;

    // ワールド座標
    Vector2 pos = { 650,350 };
    Vector2 scale = { 1.0f,1.0f };
    float theta = { 0.0f };

    //メンバ関数

    //カメラのシェイク処理
    void ShakeObject(RectangleObject* ro);

    //カメラのシェイク処理
    void ShakeCamera();

    //カメラ行列の作成
    void MakeCameraMatrix(RectangleObject* ro);

    //矩形のカメラのデバッグ用関数
    void DebugCameraMovement(GameManager* gm, RectangleObject* ro);


    // 行列計算関数群
    Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);
    Matrix3x3 InverseMatrix(Matrix3x3 matrix);
    Matrix3x3 MakeRotateMatrix(float theta);
    Matrix3x3 MakeScaleMatrix(Vector2 scale);
    Matrix3x3 MakeTranslateMatrix(Vector2 translate);
    Vector2 Transform(Vector2 vector, Matrix3x3 matrix);
    Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);
    Matrix3x3 MakeRectangleWorldMatrix(const RectangleObject* ro);
    Matrix3x3 MakeCameraWorldMatrix();
    Matrix3x3 MakeViewMatrix();
    Matrix3x3 MakeOrthographicMatrix(float left, float top,
        float right, float bottom);
    Matrix3x3 MakeViewportMatrix(float left, float top,
        float right, float bottom);

};