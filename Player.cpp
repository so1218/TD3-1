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
#include "Map.h"
#include <imgui.h>

//========================================================
// プレイヤーの挙動
//========================================================

Player::Player(float posX, float posY, float speedX, float speedY)
{
    ro_.wCenterPos.x = posX;
    ro_.wCenterPos.y = posY;
    velocity_.x = speedX;
    velocity_.y = speedY;
    radius_ = 10;
    color_ = RED;
}

Player::~Player()
{
  
};


void Player::Move(GameManager* gm, Camera* camera, Map* map)
{
    ro_.preWCenterPos = ro_.wCenterPos;

    // キーボードでの移動
   
    if (gm->keys[DIK_W]) 
    {
        ro_.wCenterPos.y += 5.0f;
        while (map->GetChip(int(ro_.currentChipNo.LT.x), int(ro_.currentChipNo.LT.y)).GetChipType() == ChipType::block
            ||
            map->GetChip(int(ro_.currentChipNo.RT.x), int(ro_.currentChipNo.RT.y)).GetChipType() == ChipType::block)
        {
            ro_.wCenterPos.y -= 0.1f;

            ro_.wCenterCurrentChipNo[0] = int((ro_.wCenterPos.y) / map->GetChip(0, 0).GetHeight());
            ro_.wCenterCurrentChipNo[1] = int(ro_.wCenterPos.x / map->GetChip(0, 0).GetWidth());
            CalcVertexCenterRectangle(&ro_);
            ro_.currentChipNo.LT = { static_cast<int>(ro_.wVertex.LT.x / map->GetChip(0, 0).GetWidth()),
                                    static_cast<int>((ro_.wVertex.LT.y) / map->GetChip(0, 0).GetHeight()) };
            ro_.currentChipNo.RT = { static_cast<int>(ro_.wVertex.RT.x / map->GetChip(0, 0).GetWidth()),
                                    static_cast<int>((ro_.wVertex.RT.y) / map->GetChip(0, 0).GetHeight()) };
        }
    }
    else if(gm->keys[DIK_S]) 
    {
        ro_.wCenterPos.y -= 5.0f;
        while (map->GetChip(int(ro_.currentChipNo.LB.x), int(ro_.currentChipNo.LB.y)).GetChipType() == ChipType::block
            ||
            map->GetChip(int(ro_.currentChipNo.RB.x), int(ro_.currentChipNo.RB.y)).GetChipType() == ChipType::block)
        {
            ro_.wCenterPos.y += 0.1f;
            ro_.wCenterCurrentChipNo[0] = int((ro_.wCenterPos.y) / map->GetChip(0, 0).GetHeight());
            ro_.wCenterCurrentChipNo[1] = int(ro_.wCenterPos.x / map->GetChip(0, 0).GetWidth());
            CalcVertexCenterRectangle(&ro_);
            ro_.currentChipNo.LB = { static_cast<int>(ro_.wVertex.LB.x / map->GetChip(0, 0).GetWidth()),
                                    static_cast<int>((ro_.wVertex.LB.y) / map->GetChip(0, 0).GetHeight()) };
            ro_.currentChipNo.RB = { static_cast<int>(ro_.wVertex.RB.x / map->GetChip(0, 0).GetWidth()),
                                    static_cast<int>((ro_.wVertex.RB.y) / map->GetChip(0, 0).GetHeight()) };
        }
    }
    else if (gm->keys[DIK_D])
    {
        ro_.wCenterPos.x += 5.0f;
        while (map->GetChip(int(ro_.currentChipNo.RT.x), int(ro_.currentChipNo.RT.y)).GetChipType() == ChipType::block
            ||
            map->GetChip(int(ro_.currentChipNo.RB.x), int(ro_.currentChipNo.RB.y)).GetChipType() == ChipType::block)
        {
            ro_.wCenterPos.x -= 0.1f;

            ro_.wCenterCurrentChipNo[0] = int((ro_.wCenterPos.y) / map->GetChip(0, 0).GetHeight());
            ro_.wCenterCurrentChipNo[1] = int(ro_.wCenterPos.x / map->GetChip(0, 0).GetWidth());
            CalcVertexCenterRectangle(&ro_);
            ro_.currentChipNo.LT = { static_cast<int>(ro_.wVertex.LT.x / map->GetChip(0, 0).GetWidth()),
                                    static_cast<int>((ro_.wVertex.LT.y) / map->GetChip(0, 0).GetHeight()) };
            ro_.currentChipNo.LB = { static_cast<int>(ro_.wVertex.LB.x / map->GetChip(0, 0).GetWidth()),
                                    static_cast<int>((ro_.wVertex.LB.y) / map->GetChip(0, 0).GetHeight()) };
        }
    }
    else if (gm->keys[DIK_A])
    {
        ro_.wCenterPos.x -= 5.0f;
        while (map->GetChip(int(ro_.currentChipNo.LT.x), int(ro_.currentChipNo.LT.y)).GetChipType() == ChipType::block
            ||
            map->GetChip(int(ro_.currentChipNo.LB.x), int(ro_.currentChipNo.LB.y)).GetChipType() == ChipType::block)
        {
            ro_.wCenterPos.x += 0.1f;

            ro_.wCenterCurrentChipNo[0] = int((ro_.wCenterPos.y) / map->GetChip(0, 0).GetHeight());
            ro_.wCenterCurrentChipNo[1] = int(ro_.wCenterPos.x / map->GetChip(0, 0).GetWidth());
            CalcVertexCenterRectangle(&ro_);
            ro_.currentChipNo.LT = { static_cast<int>(ro_.wVertex.LT.x / map->GetChip(0, 0).GetWidth()),
                                    static_cast<int>((ro_.wVertex.LT.y) / map->GetChip(0, 0).GetHeight()) };
            ro_.currentChipNo.LB = { static_cast<int>(ro_.wVertex.LB.x / map->GetChip(0, 0).GetWidth()),
                                    static_cast<int>((ro_.wVertex.LB.y) / map->GetChip(0, 0).GetHeight()) };
        }
    }

    ro_.wCenterCurrentChipNo[0] = int((ro_.wCenterPos.y) / map->GetChip(0, 0).GetHeight());
    ro_.wCenterCurrentChipNo[1] = int(ro_.wCenterPos.x / map->GetChip(0, 0).GetWidth());

    CalcVertexCenterRectangle(&ro_);

    ro_.currentChipNo.LT = { static_cast<int>(ro_.wVertex.LT.x / map->GetChip(0, 0).GetWidth()),
                            static_cast<int>((ro_.wVertex.LT.y) / map->GetChip(0, 0).GetHeight()) };
    ro_.currentChipNo.RT = { static_cast<int>(ro_.wVertex.RT.x / map->GetChip(0, 0).GetWidth()),
                            static_cast<int>((ro_.wVertex.RT.y) / map->GetChip(0, 0).GetHeight()) };
    ro_.currentChipNo.LB = { static_cast<int>(ro_.wVertex.LB.x / map->GetChip(0, 0).GetWidth()),
                            static_cast<int>((ro_.wVertex.LB.y) / map->GetChip(0, 0).GetHeight()) };
    ro_.currentChipNo.RB = { static_cast<int>(ro_.wVertex.RB.x / map->GetChip(0, 0).GetWidth()),
                            static_cast<int>((ro_.wVertex.RB.y) / map->GetChip(0, 0).GetHeight()) };


    camera->MakeCameraMatrix(&ro_);
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
    
    DrawQuadWithData(&ro_, 0, 0, 0, 0, 0, color_);

    ImGui::Begin("Window");
    ImGui::DragFloat2("ro_.centerPos", &ro_.wCenterPos.x, 0.01f);
    ImGui::DragInt2(" ro_.currentChipNo.LT", &ro_.currentChipNo.LT.x);
    ImGui::DragInt2(" ro_.currentChipNo.RT", &ro_.currentChipNo.RT.x);
    ImGui::DragInt2(" ro_.currentChipNo.LB", &ro_.currentChipNo.LB.x);
    ImGui::DragInt2(" ro_.currentChipNo.RB", &ro_.currentChipNo.RB.x);
    ImGui::End();

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