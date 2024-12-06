#include "Structures.h"
#include "Map.h"
#include "Rectangle.h"
#include "Player.h"
#include "Particle.h"
#include "Easing.h"
#include "PlayScene.h"

//========================================================
// セレクトシーンの更新処理
//========================================================

Scene UpdateSelectScene()
{
	Scene nextScene = Select;
	
	return nextScene;
}

//========================================================
// セレクトシーンの描画処理
//========================================================

// セレクトシーンのデバック(デバックモードのみ)
void ScreenPrintfSelectScene()
{
	Novice::ScreenPrintf(0, 0, "SelectScene");
}

// セレクトシーンの描画
void DrawSelectScene()
{
	

#if defined(_DEBUG)
	ScreenPrintfSelectScene();
#endif
}

//========================================================
// セレクトシーンの初期化
//========================================================

void InitSelectScene()
{
	
}

//セレクトシーンの演出に関する初期化
void InitSelectSceneEffect()
{

}