#pragma once

#include "Structures.h"

// プレイヤーの移動処理
class Player 
{

public:

    Player(float posX, float posY, float speedX, float speedY);

    ~Player();
  
    //メンバ変数
    Vector2 velocity_;
    int radius_;
    Vector2 pos_;
    RectangleObject ro_;
    unsigned int color_;

    // プレイヤーの状態を管理するメンバ関数
    void Move(GameManager* gm);
 
    // プレイヤーの描画処理
    void Draw();

    void Init();
};





// プレイヤーのデバッグ表示
void ScreenPrintfPlayScene();

//プレイヤーの演出に関する初期化
void InitPlayerEffect();



