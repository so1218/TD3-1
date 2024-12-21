#include "Structures.h"
#include "Map.h"
#include "Player.h"
#include "Easing.h"
#include "SelectScene.h"
#include "Particle.h"
#include "Rectangle.h"
#include "Matrix.h"
#include "GrovalTextureHandles.h"
#include "PlayScene.h"
#include "Function.h"
#include "Camera.h"


//========================================================
// プレイシーンの更新処理
//========================================================

Scene UpdatePlayScene(Player* player, Map* map, GameManager* gm, Camera* camera)
{
	Scene nextScene = Play;

	player->Move(gm, camera, map);

	for (int i = 0; i < map->GetFloorHeight(); ++i)
	{
		for (int j = 0; j < map->GetFloorWidth(); ++j)
		{
			camera->MakeCameraMatrix(&map->GetChip(j,i).GetRectangleObject());
		}
	}

	//プレイヤーのシェイク処理(試し)
	if (gm->keys[DIK_F] && !gm->preKeys[DIK_F])
	{
		player->GetRectangleObject().isShake = true;
	}

	if (player->GetRectangleObject().isShake)
	{
		camera->ShakeObject(&player->GetRectangleObject());
	}

	//カメラのシェイク処理(試し)
	if (gm->keys[DIK_I] && !gm->preKeys[DIK_I])
	{
		camera->isShake = true;
	}

	if (camera->isShake)
	{
		camera->ShakeCamera();
	}

	

	camera->DebugCameraMovement(gm, &player->GetRectangleObject());
				
	return nextScene;

}

//========================================================
// プレイシーンの描画処理
//========================================================

// プレイシーンのデバック(デバックモードのみ)
void ScreenPrintfPlayScene()
{
	Novice::ScreenPrintf(0, 0, "PlayScene");
}

// プレイシーンの描画
void DrawPlayScene(Player *player, Map* map, Camera* camera)
{
	map->DrawMap(camera);

	player->Draw();

#if defined(_DEBUG)
	ScreenPrintfPlayScene();
#endif
}

//========================================================
// プレイシーンの初期化
//========================================================

void InitPlayScene(Player* player)
{
	player->Init();
}

// プレイシーンの演出に関する初期化
void InitPlaySceneEffect()
{

}