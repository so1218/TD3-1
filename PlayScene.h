#pragma once

#include "Novice.h"
#include "Structures.h"

// プレイシーンの更新処理
Scene UpdatePlayScene(Player* player, Map* map, GameManager* gm);

void DrawPlayScene(Player* player, Map* map);
// プレイシーンの初期化処理
void InitPlayScene(Player* player);

// プレイシーンの演出に関する初期化
void InitPlaySceneEffect();
