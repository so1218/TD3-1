#pragma once

#include "Structures.h"
#include "Camera.h"
#include "Map.h"
#include "Character.h"

//プレイヤーの移動処理
class Player : public Character
{
public:
    //コンストラクタで初期化
    Player(float posX, float posY, float speedX, float speedY)
        : Character(posX, posY, speedX, speedY)
    {
        ro_.wPos.x = posX;
        ro_.wPos.y = posY;
        width_ = 40;
        height_ = 40;
        color_ = RED;
    }

    //デストラクタ
    ~Player() {}

    //ゲッターとセッター
   
    RectangleObject& GetRectangleObject() { return ro_; }
    void SetRectangleObject(const RectangleObject& newRectangle) { ro_ = newRectangle; }

    //プレイヤーの状態を管理するメンバ関数
    void Move(GameManager* gm, Camera* camera, Map* map);

    //プレイヤーの描画処理
    void Draw();

    void Init();

private:
    //プレイヤー特有のメンバ変数

    //プレイヤーの矩形オブジェクト
    RectangleObject ro_; 
};

//プレイヤーのデバッグ表示
void ScreenPrintfPlayScene();

//プレイヤーの演出に関する初期化
void InitPlayerEffect();



