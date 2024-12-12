#pragma once

#include "Structures.h"
#include "Camera.h"
#include "Map.h"

// プレイヤーの移動処理
class Player 
{

public:
    //コンストラクタで初期化
    Player(float posX, float posY, float speedX, float speedY);

    //デストラクタ
    ~Player();
  
    //メンバ変数
    //ゲッターとセッター
    Vector2 GetHeight() const { return velocity_; }
    void SetHeight(Vector2 newVelocity) { velocity_ = newVelocity; }

    int GetWidth() const { return radius_; }
    void SetWidth(int newRadius) { radius_ = newRadius; }

    Vector2 GetChipType() const { return pos_; }
    void SetChipType(Vector2 newPos) { pos_ = newPos; }

    unsigned int GetColor() const { return color_; }
    void SetColor(unsigned int newColor) { color_ = newColor; }

    RectangleObject& GetRectangleObject() { return ro_; }
    void SetRectangleObject(const RectangleObject& newRectangle) { ro_ = newRectangle; }

    //メンバ関数
    // プレイヤーの状態を管理するメンバ関数
    void Move(GameManager* gm, Camera* camera, Map* map);
 
    // プレイヤーの描画処理
    void Draw();

    void Init();

private:
    //メンバ変数
    Vector2 velocity_;
    int radius_;
    Vector2 pos_;
    RectangleObject ro_;
    unsigned int color_;
};

// プレイヤーのデバッグ表示
void ScreenPrintfPlayScene();

//プレイヤーの演出に関する初期化
void InitPlayerEffect();



