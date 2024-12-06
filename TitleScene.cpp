#include "Structures.h"
#include "TitleScene.h"
#include "Easing.h"
#include "SelectScene.h"
#include "Rectangle.h"
#include "Player.h"
#include "Particle.h"

//========================================================
// タイトルシーンの更新処理
//========================================================

Scene UpdateTitleScene()
{

	Scene nextScene = Title;

	return nextScene;

}

//========================================================
// タイトルシーンの描画処理
//========================================================

// タイトルシーンのデバック(デバックモードのみ)
void ScreenPrintfTitleScene()
{
	Novice::ScreenPrintf(0, 0, "TitleScene");
}

//タイトルシーンの描画
void DrawTitleScene()
{
	
#if defined(_DEBUG)
	ScreenPrintfTitleScene();
#endif
}

//========================================================
// タイトルシーンの初期化
//========================================================

void InitTitleScene()
{
	
}

//タイトルシーンの演出に関する初期化
void InitTitleSceneEffect()
{

}