#pragma once

#include "Structures.h"


//中心から周囲にEmitterRangeの範囲で発生するパーティクル(aroundParticle->amountを初期化すること)
void UpdateCenterToAroundParticle(Particle* particles,int amount, Vector2* startPos);
void DrawCenterToAroundParticle(Particle* particles, int amount);
void InitCenterToAroundParticle(Particle* particles, int amount);

//class Particle {
//public:
//    Vector2 pos;
//    Vector2 velocity;
//    Vector2 speed;
//    unsigned int color, startColor, endColor;
//    Easing easingInOut;
//    BlendModeFunc blendMode;
//    int width, height;
//    int srcW, srcH;
//    int frameCount;
//    int appearInterval;
//    bool isExist;
//    bool hasExisted;
//
//    Particle() {
//        // デフォルトの初期化
//        isExist = false;
//        hasExisted = false;
//        frameCount = 0;
//        appearInterval = 4;
//        easingInOut.isEase = true;
//        easingInOut.interval = 0.01f;
//        blendMode.choiceType = BlendModeFunc::Add;
//        width = height = 20;
//        srcW = srcH = 80;
//        color = 0xffffffff;
//        startColor = 0xffffffff;
//        endColor = 0xffffff00;
//    }
//
//    virtual void Init(int amount) = 0;
//    virtual void update() = 0; 
//    virtual void draw() = 0;   
//};

//上に向かって周囲にEmitterRangeの範囲で発生するパーティクル(aroundParticle->amountを初期化すること)
void UpdateGoUpAroundParticle(Particle* particles, int amount, Vector2* startPos);
void DrawGoUpAroundParticle(Particle* particles, int amount);
void InitGoUpAroundParticle(Particle* particles, int amount);

//進行方向と逆に出る動いているときの煙のようなパーティクル
void UpdateLikeSmokeParticle(Particle* particles, int amount, Vector2* startPos);
void DrawLikeSmokeParticle(Particle* particles, int amount);
void InitLikeSmokeParticle(Particle* particles, int amount);

// 一気に上に行って重力を受けるパーティクル
void UpdateGoUpGravityParticle(Particle* particles, int amount, Vector2* startPos);
void DrawGoUpGravityParticle(Particle* particles, int amount);
void InitGoUpGravityParticle(Particle* particles, int amount);

// 一気に中心から外側に行くパーティクル
void UpdateImpactDustCloudParticle(Particle* particles,int amount, Vector2* startPos);
void DrawImpactDustCloudParticle(Particle* particles,int amount);
void InitImpactDustCloudParticle(Particle* particles,int amount);

// 一気に中心から外側に行くパーティクル(花火のような)
void UpdateFireworkParticle(Particle* particles, int amount, Vector2* startPos);
void DrawFireworkParticle(Particle* particles, int amount);
void InitFireworkParticle(Particle* particles, int amount);

// 斜め十字のパーティクル
void UpdateNanameJuujiParticle(Particle* particles, int amount, Vector2* startPos);
void DrawNanameJuujiParticle(Particle* particles, int amount);
void InitNanameJuujiParticle(Particle* particles, int amount);

// 一気に中心から外側に行くパーティクル(爆発のような)
void UpdateExplosionParticle(Particle* particles, int amount, Vector2* startPos);
void DrawExplosionParticle(Particle* particles, int amount);
void InitExplosionParticle(Particle* particles, int amount);

// 一気に中心から外側に行くパーティクル(小爆発のような)
void UpdateMinorExplosionParticle(Particle* particles, int amount, Vector2* startPos);
void DrawMinorExplosionParticle(Particle* particles, int amount);
void InitMinorExplosionParticle(Particle* particles, int amount);

//周囲から中心に向かうEmitterRangeの範囲で発生するパーティクル
void UpdateToCenterParticle(Particle* particles, int amount, Vector2* startPos);
void DrawToCenterParticle(Particle* particles, int amount);
void InitToCenterParticle(Particle* particles, int amount);

//隕石のようなパーティクル3
void UpdateMeteoriteParticle(Particle* particles, int amount, Vector2* startPos);
void DrawMeteoriteParticle(Particle* particles, int amount);
void InitMeteoriteParticle(Particle* particles, int amount);

//竜巻のようなパーティクル
void UpdateTornadeParticle(Particle* particles, int amount, Vector2* startPos, Vector2* endPos);
void DrawTornadeParticle(Particle* particles, int amount);
void InitTornadeParticle(Particle* particles, int amount);

// プレイヤー出現のパーティクル
void UpdateAppearAroundParticle(Particle* particles, int amount, Vector2* startPos);
void DrawAppearAroundParticle(Particle* particles, int amount);
void InitAppearAroundParticle(Particle* particles, int amount);

//プレイシーンの背景のパーティクル
void UpdatePlaySceneParticle(Particle* particles, int amount);
void DrawPlaySceneParticle(Particle* particles, int amount);
void InitPlaySceneParticle(Particle* particles, int amount);

//セレクトシーンの背景のパーティクル
void UpdateSelectSceneParticle(Particle* particles, int amount);
void DrawSelectSceneParticle(Particle* particles, int amount);
void InitSelectSceneParticle(Particle* particles, int amount);

//タイトルシーンの背景のパーティクル
void UpdateTitleSceneParticle(Particle* particles, int amount);
void DrawTitleSceneParticle(Particle* particles, int amount);
void InitTitleSceneParticle(Particle* particles, int amount);

//タイトルシーンの背景の風のパーティクル
void UpdateTitleWindParticle(Particle* particles, int amount);
void DrawTitleWindParticle(Particle* particles, int amount);
void InitTitleWindParticle(Particle* particles, int amount);