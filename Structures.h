#pragma once

#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <vector>
#include <deque>
#include <math.h>

const int kWindowWidth = 1300;
const int kWindowHeight = 700;

//シーン
enum Scene
{
	Title = 0,
	Select = 1,
	Play = 2,
};

struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;
};

struct IntVector2
{
	int x = 0;
	int y = 0;
};

struct Vector3
{
	float x = 0;
	float y = 0;
	float z = 0;
};

//3x3行列の構造体
struct Matrix3x3
{
	float m[3][3];
};

// 物理的要素
struct PhysicalElements
{
	Vector2 velocity = {};
	Vector2 acceleration = {};
};

//イージングの構造体
struct Easing
{
	float interval = 0.01f;
	float cycle = 0.0f;
	float timer = 0.0f;
	float easeTimer = 0.0f;
	bool isEase = false;
	bool isReverse = false;

	int frameCount = 0;
	int runCount = 0;

	unsigned int fadeColor = 0x00000000;

	//スタートの変数
	unsigned int startColor = 0x000000ff;
	int intStartPos = 0;
	float floatStartPos = 0.0f;
	Vector2 vec2StartPos = { 0.0f,0.0f };

	//エンドの変数
	unsigned int endColor = 0x000000ff;
	int intEndPos = 0;
	float floatEndPos = 0.0f;
	Vector2 vec2EndPos = { 0.0f,0.0f };
};

// (T = Top, B = Bottom, L = Left, R = Right)
struct Vertex
{
	Vector2 LT = { -25,25 };
	Vector2 LB = { -25,-25 };
	Vector2 RT = { 25,25 };
	Vector2 RB = { 25,-25 };
};


// (T = Top, B = Bottom, L = Left, R = Right)
struct VertexOnMap
{
	IntVector2 LT;
	IntVector2 LB;
	IntVector2 RT;
	IntVector2 RB;
};

////カメラ関係の構造体
//struct Camera
//{
//	
//	//カメラの振れ幅
//	//シェイクの信号
//	bool isShake = false;
//
//	//シェイク関係
//	int shakeDuration = 20;
//	int shakeCounter = 0;
//	int magnitude = 15;
//	IntVector2 shakingPos = {};
//	
//	//ワールド座標
//	Vector2 pos = { 325,175 };
//	Vector2 scale = { 1.0f,1.0f };
//	float theta = { 0.0f };
//
//};

// 四角形の構造体
struct RectangleObject
{
	Vector2 pos;

	// 移動前の座標
	Vector2 prePos;

	// 移動後の座標
	Vector2 nextPos;

	Vector2 radius = { 0.0f, 0.0f };

	unsigned int color = 0x000000ff;

	//ワールド座標の中心の座標
	Vector2 wCenterPos = { 0,0 };
	Vector2 preWCenterPos = { 0,0 };
	int wCenterCurrentChipNo[2] = {};

	// ワールド用の４つ角 
	Vertex wVertex;
	// スクリーン用の４つ角 
	Vertex sVertex;

	// 座標が移動する直前の4つ角の保管。当たり判定で使う。
	Vertex preVertex;

	VertexOnMap currentChipNo;
	VertexOnMap preChipNo;

	bool isCollisionBlock_[2][2];

	Vector2 scale = { 1.0f,1.0f };
	float theta = { 0.0f };
	float width = 40;
	float height = 40;

	bool canMoveLeft;
	bool canMoveRight;
	bool canMoveUp;
	bool canMoveDown;

	bool isPressLeft;
	bool isPressRight;
	bool isPressUp;
	bool isPressDown;
	
	Vector2 line = { 0.0f,0.0f };
	Vector2 scroll = { 0,0 };
};

struct Circle
{
	Vector2 center;
	Vector2 radius = { 0.0f, 0.0f };
};

struct BlendModeFunc
{
	int mode = 1;
	int choiceType = 1;

	enum BlendModeType
	{
		None = 0,
		Normal = 1,
		Add = 2,
		Subtract = 3,
		Multiply = 4,
		Screen = 5,
		Exclusion = 6
	};
};

//ゲームオブジェクトに関する構造体
struct GameObject :RectangleObject, PhysicalElements
{
	Vector2 eDir = { 1.0f, 0.0f };      //位置の単位ベクトル
	bool isExist = true;

	//描写に関する変数
	unsigned int color = WHITE;
	unsigned int startColor = 0x000000ff;
	unsigned int endColor = 0x00000000;

	Vector2 startPos;
	Vector2 endPos;

	float srcW = 0;
	float srcH = 0;
	int GH = 0; //GraphicHandle。0で「White1x1」
	int spriteNum = 0;


	float theta = 0.0f;                 //角度
	float angle;
	float angleStep;
	float amplitude = 10.0f;
	float speed = 0.0f;
	Vector2 directionVec = {};
	Vector2 normalizedDirection = {};
	IntVector2 currentChipNo;          //現在いるチップのナンバー格納用。{y,x}。
	IntVector2 nextChipNo;				//次回いるチップのナンバー格納用。{y,x}。
	IntVector2 startChipNo;
	bool sidesCollision[3][3] = {};	    //周囲の８マスのマップチップとぶつかっているかどうか。
	bool isNextScene = false;

	int frameCount = 0;

	Vector2 initialPos;

	BlendModeFunc blendMode;
};

// マップチップに関する構造体
//struct MapChip :GameObject
//{
//	//チップの種類
//	int chipType = 0;                  
//
//	Vector2 pos;
//
//	float height = 50.0f;
//	float width = 50.0f;
//
//	unsigned int color = WHITE;
//
//	RectangleObject ro;
//};

struct GameManager
{
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int numJoysticks = Novice::GetNumberOfJoysticks();

	//画面外境界線。mainの画面サイズの書き換えも手打ち。マップチップのサイズ等で変動あり
	static constexpr float screenTop = 700;
	static constexpr float screenLeft = 0;
	static constexpr float screenRight = 1300;
	static constexpr float screenBottom = 0;
};

struct StageImage :RectangleObject
{
	Vector2 screen;
	float scale;
	bool isSelect;
};

//ビットマップフォントの構造体
struct BitMapFont
{
	//そのステージの制限時間
	int timeLimit = 60 * 30;

	//制限時間のビットマップフォント
	int timeLimitArray[2];
	int timeLimitSurplus;

	//カラー
	unsigned int color = 0xFFFFFFFF;

	//そのステージがクリアしたかどうか
	bool haveStageCompleted = false;        //そのステージがクリア済みかどうかの変数

	StageImage scoreBitMap[5];
	StageImage maxScoreBitMap[5];
	StageImage timeLimitBitMap[2];
	StageImage score_Font;
	StageImage time_Font;

};

//カラーに関する構造体
struct Color
{
	unsigned int r;  // 赤
	unsigned int g;  // 緑
	unsigned int b;  // 青
	unsigned int a;  // アルファ（透明度）

	Color(unsigned int r = 255, unsigned int g = 255, unsigned int b = 255, unsigned int a = 255)
		: r(r), g(g), b(b), a(a) {}
};

//マップに関する構造体
//struct Map
//{
//	static const int kFloorWidth = 26;		//マップチップの横個数
//	static const int kFloorHeight = 14;	    //縦個数
//	static const int stageSum = 1;          //ステージの総数
//	int stageNo = 0;                        //ステージのナンバリング。セレクトシーンで変更。
//
//	Easing easing;
//	Vector2 pos;
//
//	float easingTimer = 0.0f;
//
//	enum ChipType
//	{
//		none = 0,
//		block = 1,
//	}chipType = none;
//
//	int backType = 0;
//
//	
//	MapChip chip[kFloorHeight][kFloorWidth];
//
//	Map()
//	{
//		//チップの座標と４つ角を設定
//		for (int i = 0; i < kFloorHeight; ++i)
//		{
//			for (int j = 0; j < kFloorWidth; ++j)
//			{
//				chip[i][j].ro.wCenterPos.x = float(chip[i][j].width / 2.0f + (j * chip[i][j].width));
//				chip[i][j].ro.wCenterPos.y = float(GameManager::screenTop - chip[i][j].height / 2.0f - (i * chip[i][j].height));
//			}
//		}
//	}
//
//	// 補完用の変数
//	float targetPosX[kFloorHeight][kFloorWidth]; // ターゲットのX位置
//	float targetPosY[kFloorHeight][kFloorWidth]; // ターゲットのY位置
//	float moveSpeed = 0.0f; // 補完速度
//
//};

//ノックバックの構造体
struct Knockback :PhysicalElements
{
	Vector2 dir;
	Vector2 normalizedDir;
	float strength = 10;
	Easing ease;
	bool isKnockback = false;
	bool isKnockbacked = false;
	int frameCount = 0;
};

//残像の構造体
struct AfterImage
{
	std::deque<Vector2> posHistory;
	static const int maxHistory = 10;
	int frameCounter = 0;
	Vector2 pastPos = {};

	unsigned int colorRGB = 0x000000;
	float colorAlpha = 0.0f;
	float scale = 1.0f;

	Easing easingInOut;
	Easing easingOut;
	Easing easingIn;

	bool isFading = false;
	float fadeTimer = 0;

	GameObject* go;
};


struct Particle :GameObject
{
	bool isEmit = false;

	unsigned int colorRGB = 0x000000;
	unsigned int colorAlpha = 0xff;

	float lifetime;
	int elapsedTime = 0;
	int direction;
	float radius = 10.0f;
	IntVector2 emitterRange = { 80,80 };
	IntVector2 activeDistance = { 60,60 };
	Vector2 speed = {};
	float gravity = 0.7f;
	int appearInterval = 20;
	int randNum = 0;
	Vector2 speedRange = { 2.0f,2.0f };
	Vector2 speedAdd = { 1.0f,1.0f };

	BlendModeFunc blendMode;
	Knockback knockback;

	Easing easingInOut;
	Easing easingOut;
	Easing easingIn;

	//ベジエ曲線のデータ
	Vector2 p0;
	Vector2 p1;
	Vector2 p2;
	Vector2 p3;
	Vector2 p4;
	Vector2 p5;
	Vector2 center;

	bool hasExisted = false;

	int amount;

	AfterImage afterImage;
	
};

//プレイヤーの構造体
//struct Player :GameObject
//{
//	
//};

//プレイシーンの構造体
struct PlayScene :GameObject
{
	GameManager* gm;
};

//タイトルシーンの構造体
struct TitleScene: GameObject
{
	GameManager* gm;
};

//セレクトシーンの構造体
struct SelectScene: GameObject
{
	GameManager* gm;
};