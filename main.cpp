#include "Structures.h"
#include "BezierCurve.h"
#include "Easing.h"
#include "map.h"
#include "Player.h"
#include "Particle.h"
#include "Rectangle.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "GrovalAudio.h"
#include "GrovalTextureHandles.h"

const char kWindowTitle[] = "TD3_test";

int GHs[128];

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// GHs 配列を初期化
	for (int i{ 0 }; i < _countof(GHs); ++i)
	{
		GHs[i] = -1;
	}

	// テクスチャ読み込み
	TextureManager::LoadTextures();

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

#if defined(_DEBUG)
	Scene currentScene = Play;
#else
	Scene currentScene = Title;
#endif

	int currentTime = static_cast<int>(time(nullptr));
	srand(currentTime);

	TitleScene* p_ts;
	p_ts = new TitleScene;

	SelectScene* p_ss;
	p_ss = new SelectScene;

	PlayScene* p_ps;
	p_ps = new PlayScene;

	Player* p_player = new Player(300.0f, 150.0f, 4.0f, 4.0f);

	Camera* p_camera = new Camera;
	
	GameManager* p_gm;
	p_gm = new GameManager;

	Map* p_map;
	p_map = new Map;

	InitTitleScene();
	InitSelectScene();
	p_map->SetMap();
	InitPlayScene(p_player);
	AudioInitialize();

#if defined(_DEBUG)
	p_map->SetStageNo(0);
#else
	p_map->SetStageNo(0);
#endif

	//プレイシーンの中に必要な変数を格納
	p_ps->gm = p_gm;

	//タイトルシーンの中に必要な変数を格納
	p_ts->gm = p_gm;

	//セレクトシーンの中に必要な変数を格納
	p_ss->gm = p_gm;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(p_gm->preKeys, p_gm->keys, 256);
		Novice::GetHitKeyStateAll(p_gm->keys);

		///
		/// ↓更新処理ここから
		///

		switch (currentScene)
		{
		case Title:

			currentScene = UpdateTitleScene();

			break;

		case Select:

			currentScene = UpdateSelectScene();

			break;

		case Play:

			currentScene = UpdatePlayScene(p_player, p_map, p_gm, p_camera);

			break;

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (currentScene)
		{
		case Title:

			DrawTitleScene();

			break;

		case Select:

			DrawSelectScene();

			break;

		case Play:

			DrawPlayScene(p_player, p_map);

			break;

		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete p_player;
	delete p_gm;
	delete p_map;
	delete p_ps;
	delete p_ts;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
