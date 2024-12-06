#include "Structures.h"
#include "Rectangle.h"
#include "Particle.h"
#include "Hit.h"
#include "GrovalTextureHandles.h"
#include "Draw.h"
#include "Player.h"
#include "Easing.h"
#include "Camera.h"
#include "Function.h"

//========================================================
// プレイヤーの挙動
//========================================================

Player::Player(float posX, float posY, float speedX, float speedY)
{
    ro_.centerPos.x = posX;
    ro_.centerPos.y = posY;
    velocity_.x = speedX;
    velocity_.y = speedY;
    radius_ = 10;
    color_ = RED;
}

Player::~Player()
{
  
};


void Player::Move(GameManager* gm)
{
   
    // キーボードでの移動
   
    if (gm->keys[DIK_D]) { ro_.centerPos.x += 5.0f; }
    if (gm->keys[DIK_A]) { ro_.centerPos.x -= 5.0f; }
    if (gm->keys[DIK_W]) { ro_.centerPos.y += 5.0f; }
    if (gm->keys[DIK_S]) { ro_.centerPos.y -= 5.0f; }
  
    DebugCameraRectangle(gm, &ro_);

    MakeCameraMatrix(&ro_, ro_.camera);
}


//========================================================
// プレイヤーの描画処理
//========================================================

// プレイヤーのデバック(デバックモードのみ)
void ScreenPrintfPlayer()
{

}

//	プレイヤーの描画
void Player::Draw()
{
    

    DrawQuadWithData(&ro_, 0, 0, 0, 0, color_);

    

#if defined(_DEBUG)
	ScreenPrintfPlayer();
#endif
}

//========================================================
// プレイヤーの初期化
//========================================================

void Player::Init()
{
    ro_.width = 25;
    ro_.height = 25;
    CalcVertexRectangle(&ro_);
}

//プレイヤーの演出に関する初期化
void InitPlayerEffect()
{

}