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


void Player::SearchTip(Map* map, Camera* camera)
{
    //中心のチップナンバーを計算
    ro_.wPosCurrentChipNo.y = int(ro_.wPos.y / map->GetChip(0, 0).GetHeight());
    ro_.wPosCurrentChipNo.x = int(ro_.wPos.x / map->GetChip(0, 0).GetWidth());

    //ワールドの四隅の頂点を特定
    CalcWorldVertexRectangle(&ro_);

    //四隅の頂点の現在のチップナンバーを計算
    ro_.currentChipNo.LT = { static_cast<int>(ro_.wVertex.LT.x / (map->GetChip(0, 0).GetWidth())),
                             static_cast<int>((ro_.wVertex.LT.y) / (map->GetChip(0, 0).GetHeight())) };
    ro_.currentChipNo.RT = { static_cast<int>(ro_.wVertex.RT.x / (map->GetChip(0, 0).GetWidth())),
                             static_cast<int>((ro_.wVertex.RT.y) / (map->GetChip(0, 0).GetHeight())) };
    ro_.currentChipNo.LB = { static_cast<int>(ro_.wVertex.LB.x / (map->GetChip(0, 0).GetWidth())),
                             static_cast<int>((ro_.wVertex.LB.y) / (map->GetChip(0, 0).GetHeight())) };
    ro_.currentChipNo.RB = { static_cast<int>(ro_.wVertex.RB.x / (map->GetChip(0, 0).GetWidth())),
                             static_cast<int>((ro_.wVertex.RB.y) / (map->GetChip(0, 0).GetHeight())) };

    camera->pos = { ro_.wPos.x,ro_.wPos.y };
}


void Player::Move(GameManager* gm, Camera* camera, Map* map)
{
    if (gm->keys[DIK_W])
    {
        for (int i = 0; i < 50; i++)
        {
            Player::SearchTip(map, camera);
            if (map->GetChip(int(ro_.currentChipNo.LT.x), int(ro_.currentChipNo.LT.y)).GetChipType() == ChipType::none &&
                map->GetChip(int(ro_.currentChipNo.RT.x), int(ro_.currentChipNo.RT.y)).GetChipType() == ChipType::none)
            {
                ro_.wPos.y += 0.1f;
            }
            else
            {
                ro_.wPos.y -= 0.1f;
                break;
            }
        }
    }
    else if (gm->keys[DIK_S])
    {
        for (int i = 0; i < 50; i++)
        {
            Player::SearchTip(map, camera);
            if (map->GetChip(int(ro_.currentChipNo.LB.x), int(ro_.currentChipNo.LB.y)).GetChipType() == ChipType::none &&
                map->GetChip(int(ro_.currentChipNo.RB.x), int(ro_.currentChipNo.RB.y)).GetChipType() == ChipType::none)
            {
                ro_.wPos.y -= 0.1f;
            }
            else
            {
                ro_.wPos.y += 0.1f;
                break;
            }
        }
    }
    else if (gm->keys[DIK_D])
    {
        for (int i = 0; i < 50; i++)
        {
            Player::SearchTip(map, camera);
            if (map->GetChip(int(ro_.currentChipNo.RT.x), int(ro_.currentChipNo.RT.y)).GetChipType() == ChipType::none &&
                map->GetChip(int(ro_.currentChipNo.RB.x), int(ro_.currentChipNo.RB.y)).GetChipType() == ChipType::none)
            {
                ro_.wPos.x += 0.1f;
            }
            else
            {
                ro_.wPos.x -= 0.1f;
                break;
            }
        }
    }
    else if (gm->keys[DIK_A])
    {
        for (int i = 0; i < 50; i++)
        {
            Player::SearchTip(map, camera);
            if (map->GetChip(int(ro_.currentChipNo.LT.x), int(ro_.currentChipNo.LT.y)).GetChipType() == ChipType::none &&
                map->GetChip(int(ro_.currentChipNo.LB.x), int(ro_.currentChipNo.LB.y)).GetChipType() == ChipType::none)
            {
                ro_.wPos.x -= 0.1f;
            }
            else
            {
                ro_.wPos.x += 0.1f;
                break;
            }
        }
    }

    Player::SearchTip(map, camera);


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
    //プレイヤーの描画
    DrawQuadWithData(&ro_, 0, 0, 0, 0, 0, color_);

    //デバックの描画
    ImGui::Begin("Window");
    ImGui::DragFloat2("ro_.wCenterPos", &ro_.wPos.x, 0.01f);
    ImGui::DragFloat2("ro_.pos", &ro_.pos.x, 0.01f);
    ImGui::DragInt2(" ro_.currentChipNo.LT", &ro_.currentChipNo.LT.x);
    ImGui::DragInt2(" ro_.currentChipNo.RT", &ro_.currentChipNo.RT.x);
    ImGui::DragInt2(" ro_.currentChipNo.LB", &ro_.currentChipNo.LB.x);
    ImGui::DragInt2(" ro_.currentChipNo.RB", &ro_.currentChipNo.RB.x);
    ImGui::DragInt2(" ro_.wCenterCurrentChipNo", &ro_.wPosCurrentChipNo.x);
    ImGui::DragFloat2(" ro_.wVertex.LT ", &ro_.wVertex.LT.x);
    ImGui::DragFloat2(" ro_.wVertex.RT ", &ro_.wVertex.RT.x);
    ImGui::DragFloat2(" ro_.wVertex.LB ", &ro_.wVertex.LB.x);
    ImGui::DragFloat2(" ro_.wVertex.RB ", &ro_.wVertex.RB.x);
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
    CalcCameraVertexRectangle(&ro_);
    
}

//プレイヤーの演出に関する初期化
void InitPlayerEffect()
{

}