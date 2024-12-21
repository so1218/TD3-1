#include "BezierCurve.h"
#include "Calculate.h"
#include "Draw.h"
#include "Easing.h"
#include "GameObject.h"
#include "GrovalTextureHandles.h"
#include "Rectangle.h"
#include "Structures.h"
#include "Vector.h"
#include "Function.h"
#include <stdlib.h>
#include "Particle.h"

//Particle::Particle() {
//    // デフォルト値で初期化
//    isExist = false;
//    hasExisted = false;
//    frameCount = 0;
//    appearInterval = 4;
//    width = 20;
//    height = 20;
//    color = 0xffffffff;
//    startColor = 0xffffffff;
//    endColor = 0xffffff00;
//    speed = { 1.0f, 1.0f };
//    gravity = 0.23f;
//    emitterRange = { 20, 20 };
//}
//
//void Particle::Update() {
//    // パーティクルの状態を更新（位置、速度、色など）
//    if (frameCount <= 0) {
//        frameCount = appearInterval;
//    }
//
//    if (frameCount == appearInterval && !isExist) {
//        // パーティクルの生成ロジック（位置、速度、角度など）
//        angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
//        velocity.x = speed.x * cosf(angle);
//        velocity.y = speed.y * sinf(angle);
//        isExist = true;
//    }
//
//    // パーティクルの移動
//    if (isExist) {
//        pos.x += velocity.x;
//        pos.y += velocity.y;
//
//        // イージングや色補間の更新処理
//        if (!easingInOut.isEase) {
//            isExist = false;
//        }
//
//        // その他の更新処理（例: 残像、イージングの処理）
//        ColorLinearInterpolation(startColor, endColor, color, easingInOut);
//        CountEaseInOutTimer(easingInOut);
//    }
//
//    frameCount--;
//}
//
//void Particle::Draw() {
//    // パーティクルの描画ロジック
//    if (isExist) {
//        UpdateBlendMode(&blendMode);
//        DrawQuadWithData(&ro, 0, 0, 0, 0, 0, color);
//        ResetBlendMode();
//    }
//}
//
//void ParticleEmitter::Update(Vector2* startPos) {
//    // 各パーティクルを更新
//    for (int i = 0; i < amount; ++i) {
//        particles[i].Update();
//    }
//}
//
//void ParticleEmitter::Draw() {
//    // 各パーティクルを描画
//    for (int i = 0; i < amount; ++i) {
//        particles[i].Draw();
//    }
//}
//
//void ParticleEmitter::Init() {
//    // 初期化処理
//    for (int i = 0; i < amount; ++i) {
//        particles[i] = Particle();
//        // 個別に初期設定を行う（位置、色など）
//        particles[i].appearInterval = 4;
//        particles[i].emitterRange = { 20, 20 };
//        particles[i].speed = { 1.0f, 1.0f };
//        particles[i].color = 0xffa500ff;
//    }
//}
//
//void ParticleEmitter::UpdateCenterToAroundParticle(Vector2* startPos) {
//    for (int i = 0; i < amount; ++i) {
//        Particle& particle = particles[i];
//        if (!particle.isExist) {
//            // 位置や速度の設定
//            particle.pos.x = startPos->x;
//            particle.pos.y = startPos->y;
//            // 他の処理
//        }
//        particle.Update();
//    }
//}

// 中心から周囲に向かうEmitterRangeの範囲で発生するパーティクル(aroundParticle->amountを初期化すること)
void UpdateCenterToAroundParticle(Particle* particles, int amount, Vector2* startPos)
{
    if (particles->frameCount <= 0) {
        particles->frameCount = particles->appearInterval;
    }

    particles->isEmit = false;

    // フレームごとに新しいパーティクルを生成
    if (particles->frameCount == particles->appearInterval) {

        for (int i = 0; i < amount; ++i) {
            Particle& particle = particles[i];

            if (!particle.hasExisted) {
                if (!particle.isExist) {

                    particle.angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
                    particle.pos.x = static_cast<float>(startPos->x);
                    particle.pos.y = static_cast<float>(startPos->y);

                    particle.speed = { 1.0f, 1.0f };
                    particle.velocity.x = particle.speed.x * cosf(particle.angle);
                    particle.velocity.y = particle.speed.y * sinf(particle.angle);

                    particle.isExist = true;
                    particle.easingInOut.isEase = true;

                    particle.blendMode.mode = particle.blendMode.choiceType;

                    particle.hasExisted = true;

                    break;
                }
            }
        }
    }

    particles->frameCount -= 1;

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            particles->isEmit = true;

            particle.pos.x += particle.velocity.x;
            particle.pos.y += particle.velocity.y;

            if (!particle.easingInOut.isEase) {
                particle.isExist = false;
            }

            ColorLinearInterpolation(particle.startColor, particle.endColor, particle.color, particle.easingInOut);
            CountEaseInOutTimer(particle.easingInOut);
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawCenterToAroundParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitCenterToAroundParticle(Particle* particles, int amount)
{

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 4;
        particle.emitterRange = { 20, 20 };
        particle.easingInOut.interval = 0.01f;
        particle.width = 20;
        particle.height = 20;
        particle.color = 0xffa500ff;
        particle.startColor = 0xffa500ff;
        particle.endColor = 0xffa50000;
        particle.blendMode.choiceType = particles[i].blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.frameCount = 0;
    }
}

// 上に向かって周囲にEmitterRangeの範囲で発生するパーティクル
void UpdateGoUpAroundParticle(Particle* particles, int amount, Vector2* startPos)
{

    if (particles->frameCount <= 0) {
        particles->frameCount = particles->appearInterval;
    }

    // フレームごとに新しいパーティクルを生成
    if (particles->frameCount == particles->appearInterval) {
        for (int i = 0; i < amount; ++i) {
            Particle& particle = particles[i]; // particles[i]を参照として取得

            if (!particle.isExist) {

                particle.pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle.emitterRange.x - particle.emitterRange.x / 2);
                particle.pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle.emitterRange.y - particle.emitterRange.y / 2);
                particle.initialPos.y = particle.pos.y;
                particle.speed = { 1.0f, 0.5f };
                particle.velocity.y = particle.speed.y;
                particle.isExist = true;
                particle.easingOut.isEase = true;
                particle.easingInOut.isEase = true;
                particle.blendMode.mode = particle.blendMode.choiceType;

                break;
            }
        }
    }

    particles->frameCount -= 1;

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {

            if (!particle.easingInOut.isEase) {
                particle.isExist = false;
            }

            LinearInterpolation(particle.initialPos.y,
                particle.initialPos.y + particle.activeDistance.y,
                particle.pos.y,
                particle.easingOut);
            CountEaseOutTimer(particle.easingOut);

            ColorLinearInterpolation(particle.startColor, particle.endColor, particle.color, particle.easingInOut);
            CountEaseInOutTimer(particle.easingInOut);
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawGoUpAroundParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitGoUpAroundParticle(Particle* particles, int amount)
{

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 4;
        particle.emitterRange = { 30, 20 };
        particle.easingInOut.interval = 0.01f;
        particle.width = 20;
        particle.height = 20;
        particle.color = 0xffff00ff;
        particle.startColor = 0xffff00ff;
        particle.endColor = 0xffff0000;
        particle.blendMode.choiceType = particles[i].blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.isExist = false;
        particle.hasExisted = false;
        /* particle.amount = 32;*/
        particle.frameCount = 0;
        particle.speed = { 1.0f, 0.1f };
    }
}

// 進行方向と逆に出る動いているときの煙のようなパーティクル
void UpdateLikeSmokeParticle(Particle* particles, int amount, Vector2* startPos)
{

    if (particles->frameCount <= 0) {
        particles->frameCount = particles->appearInterval;
    }

    if (particles->frameCount == particles->appearInterval) {
        for (int i = 0; i < amount; ++i) {
            Particle& particle = particles[i]; // particles[i]を参照として取得

            if (!particle.hasExisted) {
                if (!particle.isExist) {
                    // ランダムで角度を設定
                    particle.angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
                    particle.pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle.emitterRange.x - particle.emitterRange.x / 2);
                    particle.pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle.emitterRange.y - particle.emitterRange.y / 2);

                    // 初期速度を設定
                    particle.velocity.x = particle.speed.x * cosf(particle.angle);
                    particle.velocity.y = particle.speed.y * sinf(particle.angle);

                    // パーティクルの存在を設定
                    particle.isExist = true;
                    particle.easingInOut.isEase = true;
                    particle.blendMode.mode = particle.blendMode.choiceType;
                    break;
                }
            }
        }
    }

    particles->frameCount -= 1;

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];
        // パーティクルの移動
        if (particle.isExist) {
            particle.pos.x += particle.velocity.x;
            particle.pos.y += particle.velocity.y;

            // イージングが終了したら存在しなくなる
            if (!particle.easingInOut.isEase) {
                particle.isExist = false;
            }

            // カラーの補間
            ColorLinearInterpolation(particle.startColor, particle.endColor, particle.color, particle.easingInOut);
            CountEaseInOutTimer(particle.easingInOut);
        }

        // パーティクルの描画用計算
        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawLikeSmokeParticle(Particle* particles, int amount)
{

    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];
        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitLikeSmokeParticle(Particle* particles, int amount)
{

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 4;
        particle.emitterRange = { 20, 20 };
        particle.easingInOut.interval = 0.01f;
        particle.width = 50;
        particle.height = 50;
        particle.color = 0xffffffff;
        particle.startColor = 0xffffffff;
        particle.endColor = 0xffffff00;
        particle.blendMode.choiceType = particles[i].blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.speed = { 0.2f, 0.2f };
        particle.frameCount = 0;
    }
}

// 一気に上に行って重力を受けるパーティクル
void UpdateGoUpGravityParticle(Particle* particles, int amount, Vector2* startPos)
{

    // フレームごとに新しいパーティクルを生成
    particles->isEmit = false;

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i]; // particles[i]を参照として取得

        if (!particle.hasExisted) {
            if (!particle.isExist) {
                particle.angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
                particle.pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle.emitterRange.x - particle.emitterRange.x / 2);
                particle.pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle.emitterRange.y - particle.emitterRange.y / 2);

                if (particle.pos.x >= startPos->x) {
                    particle.speed = { static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f, static_cast<float>(rand()) / RAND_MAX * 4.0f + 8.0f };
                }
                else {
                    particle.speed = { -static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f, static_cast<float>(rand()) / RAND_MAX * 4.0f + 8.0f };
                }
                particle.velocity.x = particle.speed.x;
                particle.velocity.y = particle.speed.y;

                particle.isExist = true;
                particle.hasExisted = true;
                particle.easingInOut.isEase = true;

                particle.blendMode.mode = particle.blendMode.choiceType;

                particle.afterImage.easingInOut.isEase = true;
            }
        }
    }

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i]; // particles[i]を参照として取得

        if (particle.isExist) {
            particles->isEmit = true;

            particle.pos.x += particle.velocity.x;
            particle.pos.y += particle.velocity.y;
            particle.velocity.y -= particle.gravity;

            // 残像の処理
            particle.afterImage.frameCounter++;

            if (particle.afterImage.frameCounter >= 1) {

                particle.afterImage.posHistory.push_front(particle.pos);

                if (particle.afterImage.posHistory.size() > particle.afterImage.maxHistory) {
                    particle.afterImage.posHistory.pop_back();
                }

                // フレームカウンタをリセット
                particle.afterImage.frameCounter = 0;
            }

            if (!particle.easingInOut.isEase) {
                particle.isExist = false;

                particle.afterImage.isFading = true;
                particle.pos = { -500.0f,-500.0f };
            }

            ColorLinearInterpolation(particle.startColor, particle.endColor, particle.color, particle.easingInOut);
            CountEaseInOutTimer(particle.easingInOut);
        }

        if (!particle.isExist && particle.afterImage.isFading) {
            // 残像の透明度を時間経過で減少させる
            if (particle.afterImage.fadeTimer < 1.0f) {
                particle.afterImage.fadeTimer += 0.03f;
                particles->isEmit = true;

            }
            else {
                // 完全に透明になったら残像を削除
                particle.afterImage.isFading = false;
                particle.afterImage.posHistory.clear();
            }
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawGoUpGravityParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i]; // particles[i]を参照として取得

        UpdateBlendMode(&particle.blendMode);

        // 残像を描画
        for (int j = 0; j < particle.afterImage.posHistory.size(); ++j) {

            particle.afterImage.pastPos = particle.afterImage.posHistory[j];

            particle.afterImage.colorAlpha = 1.0f - (j / static_cast<float>(particle.afterImage.maxHistory));
            particle.afterImage.scale = 1.0f - (j / static_cast<float>(particle.afterImage.maxHistory));

            if (!particle.isExist) {
                particle.afterImage.colorAlpha *= 1.0f - particle.afterImage.fadeTimer;
                particle.afterImage.scale *= 1.0f - particle.afterImage.fadeTimer;
            }
            Novice::DrawQuad(
                static_cast<int>(particle.afterImage.pastPos.x - particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y - particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.afterImage.pastPos.x + particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y - particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.afterImage.pastPos.x - particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y + particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.afterImage.pastPos.x + particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y + particle.height * particle.afterImage.scale / 2),
                0, 0, 80, 80, GHs[TextureName::Particle1], (particle.afterImage.colorRGB << 8) | static_cast<unsigned int>(particle.afterImage.colorAlpha * 255));
        }

        if (particle.isExist) {

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);
        }

        ResetBlendMode();
    };
}

void InitGoUpGravityParticle(Particle* particles, int amount)
{

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 5;
        particle.emitterRange = { 40, 40 };
        particle.easingInOut.interval = 0.01f;
        particle.width = 50;
        particle.height = 50;
        particle.color = 0x8a2be2ff;
        particle.startColor = 0x8a2be2ff;
        particle.endColor = 0x8a2be200;
        particle.blendMode.choiceType = particles[i].blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.afterImage.colorRGB = 0x8a2be2;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.gravity = 0.23f;
        particle.afterImage.posHistory.clear();
        particle.afterImage.fadeTimer = 0.0f;
        particle.frameCount = 0;
        particle.scale = { 1.0f,1.0f };
    }
}

// 一気に中心から外側に行くパーティクル
void UpdateImpactDustCloudParticle(Particle* particles, int amount, Vector2* startPos)
{
    // フレームごとに新しいパーティクルを生成

    particles->isEmit = false;

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (!particle.hasExisted) {
            if (!particle.isExist) {
                particle.angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
                particle.pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle.emitterRange.x - particle.emitterRange.x / 2);
                particle.pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle.emitterRange.y - particle.emitterRange.y / 2);

                if (particle.pos.x >= startPos->x) {
                    particle.speed.x = static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f;
                }
                else {
                    particle.speed.x = -static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f;
                }

                if (particle.pos.y >= startPos->y) {
                    particle.speed.y = static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f;
                }
                else {
                    particle.speed.y = -static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f;
                }

                particle.velocity.x = particle.speed.x;
                particle.velocity.y = particle.speed.y;

                particle.gravity = 0.2f;

                particle.isExist = true;
                particle.hasExisted = true;
                particle.easingInOut.isEase = true;
                particle.blendMode.mode = particle.blendMode.choiceType;
            }
        }
    }

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            particles->isEmit = true;

            particle.pos.x += particle.velocity.x;
            particle.pos.y += particle.velocity.y;
            particle.velocity.y -= particle.gravity;

            if (!particle.easingInOut.isEase) {
                particle.isExist = false;
                particle.isEmit = false;
            }

            ColorLinearInterpolation(particle.startColor, particle.endColor, particle.color, particle.easingInOut);
            CountEaseInOutTimer(particle.easingInOut);
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawImpactDustCloudParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitImpactDustCloudParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 4;
        particle.emitterRange = { 60, 40 };
        particle.easingInOut.interval = 0.03f;
        particle.width = 50;
        particle.height = 50;
        particle.color = 0x00ff00ff;
        particle.startColor = 0x00ff00ff;
        particle.endColor = 0x00ff0000;
        particle.blendMode.choiceType = particles[i].blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.afterImage.colorRGB = 0x8a2be2;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.gravity = 0.3f;
        particle.easingInOut.interval = 0.03f;
        particle.frameCount = 0;
    }
}

// 一気に中心から外側に行くパーティクル(花火のような)
void UpdateFireworkParticle(Particle* particles, int amount, Vector2* startPos)
{
    particles->elapsedTime++;

    // フレームごとに新しいパーティクルを生成

    particles->isEmit = false;

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (!particle.hasExisted) {
            if (!particle.isExist) {
                particle.angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
                particle.pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle.emitterRange.x - particle.emitterRange.x / 2);
                particle.pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle.emitterRange.y - particle.emitterRange.y / 2);

                if (particle.pos.x >= startPos->x) {
                    particle.speed.x = static_cast<float>(rand()) / RAND_MAX * 5.0f + 1.0f;
                }
                else {
                    particle.speed.x = -static_cast<float>(rand()) / RAND_MAX * 5.0f + 1.0f;
                }

                if (particle.pos.y >= startPos->y) {
                    particle.speed.y = static_cast<float>(rand()) / RAND_MAX * 5.0f + 1.0f;
                }
                else {
                    particle.speed.y = -static_cast<float>(rand()) / RAND_MAX * 5.0f + 1.0f;
                }

                particle.velocity.x = particle.speed.x;
                particle.velocity.y = particle.speed.y;

                particle.isExist = true;
                particle.hasExisted = true;
                particle.easingInOut.isEase = true;
                particle.blendMode.mode = particle.blendMode.choiceType;
            }
        }
    }

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            particles->isEmit = true;

            if (particles->elapsedTime <= 300) {
                particle.pos.x += particle.velocity.x;
                particle.pos.y += particle.velocity.y;

                if (!particle.easingInOut.isEase) {
                    particle.isExist = false;
                }

                ColorLinearInterpolation(particle.startColor, particle.endColor, particle.color, particle.easingInOut);
                CountEaseInOutTimer(particle.easingInOut);

            }

            else {
                particle.pos.y += 1.0f;

                particle.scale.x *= 0.98f;
                particle.scale.y *= 0.98f;

                if (particle.scale.x < 0.1f || particle.scale.y < 0.1f) {
                    particle.isExist = false;
                    particle.isEmit = false;
                }
            }
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawFireworkParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitFireworkParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 1;
        particle.emitterRange = { 10, 10 };
        particle.easingInOut.interval = 0.001f;
        particle.width = 150;
        particle.height = 150;
        particle.color = 0x8b4513ff;
        particle.startColor = 0x8b4513ff;
        particle.endColor = 0x8b451300;
        particle.blendMode.choiceType = particle.blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.afterImage.colorRGB = 0xf5bed3;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.elapsedTime = 0;
        particle.scale = { 1.0f, 1.0f };
        particle.frameCount = 0;
    }
}

// 斜め十字のパーティクル
void UpdateNanameJuujiParticle(Particle* particles, int amount, Vector2* startPos)
{
    particles->elapsedTime++;

    // フレームごとに新しいパーティクルを生成

    if (particles->frameCount <= 0) {
        particles->frameCount = particles->appearInterval;
    }

    if (particles->frameCount == particles->appearInterval) {
        for (int i = 0; i < amount; ++i) {
            Particle& particle = particles[i];

            if (particles->elapsedTime <= 120) {

                if (!particle.isExist) {
                    particle.angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
                    particle.pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle.emitterRange.x - particle.emitterRange.x / 2);
                    particle.pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle.emitterRange.y - particle.emitterRange.y / 2);

                    if (particle.pos.x >= startPos->x) {
                        particle.speed.x = static_cast<float>(rand()) / RAND_MAX * 2.0f + 5.0f;
                    }
                    else {
                        particle.speed.x = -(static_cast<float>(rand()) / RAND_MAX * 2.0f + 5.0f);
                    }

                    if (particle.pos.y >= startPos->y) {
                        particle.speed.y = static_cast<float>(rand()) / RAND_MAX * 2.0f + 5.0f;
                    }
                    else {
                        particle.speed.y = -(static_cast<float>(rand()) / RAND_MAX * 2.0f + 5.0f);
                    }

                    particle.velocity.x = particle.speed.x;
                    particle.velocity.y = particle.speed.y;

                    particle.isExist = true;

                    particle.easingInOut.isEase = true;
                    particle.blendMode.mode = particle.blendMode.choiceType;

                    break;
                }
            }
        }
    }

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            if (particles->elapsedTime <= 120) {
                particle.pos.x += particle.velocity.x;
                particle.pos.y += particle.velocity.y;

                if (particle.pos.x <= 0.0f || particle.pos.x >= kWindowWidth || particle.pos.y <= 0.0f || particle.pos.y >= kWindowHeight) {
                    particle.isExist = false;
                }
            }

            else {
                particle.scale.x *= 0.90f;
                particle.scale.y *= 0.90f;

                if (particle.scale.x < 0.1f || particle.scale.y < 0.1f) {
                    particle.isExist = false;
                    particle.isEmit = false;
                    particle.pos = { -199.0f,-199.0f };
                }
            }
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawNanameJuujiParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitNanameJuujiParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 15;
        particle.emitterRange = { 10, 10 };
        particle.easingInOut.interval = 0.002f;
        particle.width = 150;
        particle.height = 150;
        particle.color = 0x00ff00ff;
        particle.startColor = 0x00ff00ff;
        particle.endColor = 0x00ff0000;
        particle.blendMode.choiceType = particle.blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.afterImage.colorRGB = 0x00ff00;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.elapsedTime = 0;
        particle.scale = { 1.0f, 1.0f };
        particle.frameCount = 0;
    }
}

// 爆発のパーティクル
void UpdateExplosionParticle(Particle* particles, int amount, Vector2* startPos)
{
    particles->elapsedTime++;

    if (particles->frameCount <= 0) {
        particles->frameCount = particles->appearInterval;
    }

    particles->isEmit = false;

    // フレームごとに新しいパーティクルを生成
    if (particles->frameCount == particles->appearInterval) {
        for (int i = 0; i < amount; ++i) {
            Particle& particle = particles[i];

            if (particles->elapsedTime <= 300) {

                if (!particle.isExist) {
                    particle.angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
                    particle.pos.x = static_cast<float>(startPos->x);
                    particle.pos.y = static_cast<float>(startPos->y);

                    particle.scale.x = static_cast<float>(rand()) / RAND_MAX * 1.0f + 0.5f;
                    particle.scale.y = particle.scale.x;

                    particle.velocity.x = particle.speed.x * cosf(particle.angle);
                    particle.velocity.y = particle.speed.y * sinf(particle.angle);

                    particle.colorAlpha = 0x11 + static_cast<unsigned int>(rand()) % (0xff - 0x11);

                    particle.color = (particle.colorRGB & 0xffffff00) | particle.colorAlpha;

                    particle.isExist = true;

                    particle.easingInOut.isEase = true;
                    particle.blendMode.mode = particle.blendMode.choiceType;

                    break;
                }
            }
        }
    }

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {

            particles->isEmit = true;

            if (particles->elapsedTime <= 300) {

                particle.pos.x += particle.velocity.x;
                particle.pos.y += particle.velocity.y;

                if (particle.pos.x <= 0.0f || particle.pos.x >= kWindowWidth || particle.pos.y <= 0.0f || particle.pos.y >= kWindowHeight) {
                    particle.isExist = false;
                    particle.isEmit = false;
                }
            }

            else {
                particle.pos.y += 1.0f;

                particle.scale.x *= 0.98f;
                particle.scale.y *= 0.98f;

                if (particle.scale.x < 0.1f || particle.scale.y < 0.1f) {
                    particle.isExist = false;
                    particle.isEmit = false;
                }
            }
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawExplosionParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitExplosionParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 1;
        particle.emitterRange = { 10, 10 };
        particle.easingInOut.interval = 0.0003f;
        particle.width = 60;
        particle.height = 60;
        particle.color = 0x00ffffff;
        particle.colorRGB = 0x00ffff;
        particle.colorAlpha = 0xff;
        particle.startColor = 0x00ffffff;
        particle.endColor = 0x00ffff00;
        particle.blendMode.choiceType = particle.blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.afterImage.colorRGB = 0x00ffff;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.speed = { 10, 10 };
        particle.elapsedTime = 0;
    }
}

// 小爆発のパーティクル
void UpdateMinorExplosionParticle(Particle* particles, int amount, Vector2* startPos)
{
    particles->elapsedTime++;

    if (particles->frameCount <= 0) {
        particles->frameCount = particles->appearInterval;
    }

    particles->isEmit = false;

    // フレームごとに新しいパーティクルを生成
    if (particles->frameCount == particles->appearInterval) {
        for (int i = 0; i < amount; ++i) {
            Particle& particle = particles[i];

            if (!particle.hasExisted) {
                if (!particle.isExist) {
                    particle.angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
                    particle.pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle.emitterRange.x - particle.emitterRange.x / 2);
                    particle.pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle.emitterRange.y - particle.emitterRange.y / 2);

                    particle.speed.x = static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f;
                    particle.speed.y = static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f;

                    particle.velocity.x = particle.speed.x * cosf(particle.angle);
                    particle.velocity.y = particle.speed.y * sinf(particle.angle);

                    particle.isExist = true;

                    particle.easingOut.isEase = true;
                    particle.hasExisted = true;
                    particle.blendMode.mode = particle.blendMode.choiceType;

                    break;
                }
            }
        }
    }

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            particles->isEmit = true;

            Vector2 startScale = { 0.0f, 0.0f };
            Vector2 endScale = { 1.0f, 1.0f };

            if (particle.easingOut.isEase) {
                LinearInterpolation(startScale,
                    endScale,
                    particle.scale,
                    particle.easingOut);
                CountEaseOutTimer(particle.easingOut);

                particle.pos.x += particle.velocity.x;
                particle.pos.y += particle.velocity.y;

                if (particle.pos.x <= 0.0f || particle.pos.x >= kWindowWidth || particle.pos.y <= 0.0f || particle.pos.y >= kWindowHeight) {
                    particle.isExist = false;
                }
            }

            else {
                particle.pos.y += 1.0f;

                particle.scale.x *= 0.98f;
                particle.scale.y *= 0.98f;

                if (particle.scale.x < 0.1f || particle.scale.y < 0.1f) {
                    particle.isExist = false;
                    particle.isEmit = false;
                }
            }
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawMinorExplosionParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitMinorExplosionParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 1;
        particle.emitterRange = { 10, 10 };
        particle.easingOut.interval = 0.02f;
        particle.width = 100;
        particle.height = 100;
        particle.color = 0xff00ffff;
        particle.colorRGB = 0xff00ff;
        particle.colorAlpha = 0xff;
        particle.startColor = 0xff00ffff;
        particle.endColor = 0xff00ff00;
        particle.blendMode.choiceType = particle.blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.afterImage.colorRGB = 0xff00ff;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.speed = { 2, 2 };
        particle.elapsedTime = 0;
    }
}

// 中心に向かうパーティクル
void UpdateToCenterParticle(Particle* particles, int amount, Vector2* startPos)
{
    if (particles->frameCount <= 0) {
        particles->frameCount = particles->appearInterval;
    }

    // フレームごとに新しいパーティクルを生成
    if (particles->frameCount == particles->appearInterval) {
        for (int i = 0; i < amount; ++i) {
            Particle& particle = particles[i]; // particles[i]を参照として取得

            if (!particle.isExist) {

                particle.angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
                particle.pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle.emitterRange.x - particle.emitterRange.x / 2);
                particle.pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle.emitterRange.y - particle.emitterRange.y / 2);

                particle.isExist = true;
                particle.easingInOut.isEase = true;
                particle.easingIn.isEase = true;
                particle.blendMode.mode = particle.blendMode.choiceType;

                break;
            }
        }
    }

    particles->frameCount -= 1;

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            LinearInterpolation(particle.pos,
                *startPos,
                particle.pos,
                particle.easingIn);
            CountEaseOutTimer(particle.easingIn);

            if (!particle.easingInOut.isEase) {
                particle.isExist = false;
            }

            ColorLinearInterpolation(particle.startColor, particle.endColor, particle.color, particle.easingInOut);
            CountEaseInOutTimer(particle.easingInOut);
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawToCenterParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];
        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitToCenterParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 4;
        particle.emitterRange = { 150, 150 };
        particle.easingInOut.interval = 0.01f;
        particle.easingIn.interval = 0.0000005f;
        particle.width = 20;
        particle.height = 20;
        particle.color = 0x00fa9aff;
        particle.startColor = 0x00fa9aff;
        particle.endColor = 0x00fa9a00;
        particle.blendMode.choiceType = particles[i].blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.isExist = false;
        particle.frameCount = 0;
    }
}

// 隕石のようなパーティクル
void UpdateMeteoriteParticle(Particle* particles, int amount, Vector2* startPos)
{
    if (particles->frameCount <= 0) {
        particles->frameCount = particles->appearInterval;
    }

    particles->isEmit = false;

    // フレームごとに新しいパーティクルを生成
    if (particles->frameCount == particles->appearInterval) {
        for (int i = 0; i < amount; ++i) {
            Particle& particle = particles[i]; // particles[i]を参照として取得

            if (!particle.hasExisted) {

                if (!particle.isExist) {

                    particle.pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle.emitterRange.x - particle.emitterRange.x / 2);
                    particle.pos.y = static_cast<float>(startPos->y);

                    if (particle.pos.x >= startPos->x) {
                        particle.speed.x = static_cast<float>(rand()) / RAND_MAX * 4.0f + 1.0f;
                    }
                    else {
                        particle.speed.x = -(static_cast<float>(rand()) / RAND_MAX * 4.0f + 1.0f);
                    }

                    particle.speed.y = static_cast<float>(rand()) / RAND_MAX * 5.0f - 9.0f;


                    particle.velocity.x = particle.speed.x;
                    particle.velocity.y = particle.speed.y;

                    particle.isExist = true;
                    particle.hasExisted = true;
                    particle.blendMode.mode = particle.blendMode.choiceType;

                    break;
                }
            }
        }
    }

    particles->frameCount -= 1;

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {

            particles->isEmit = true;

            particle.pos.x += particle.velocity.x;
            particle.pos.y += particle.velocity.y;

            if (particle.pos.y <= 0.0f) {
                particle.isExist = false;
                particle.afterImage.isFading = true;
            }

            // 残像の処理
            particle.afterImage.frameCounter++;

            if (particle.afterImage.frameCounter >= 1) {

                particle.afterImage.posHistory.push_front(particle.pos);

                if (particle.afterImage.posHistory.size() > particle.afterImage.maxHistory) {
                    particle.afterImage.posHistory.pop_back();
                }

                // フレームカウンタをリセット
                particle.afterImage.frameCounter = 0;
            }
        }

        if (!particle.isExist && particle.afterImage.isFading) {
            // 残像の透明度を時間経過で減少させる
            if (particle.afterImage.fadeTimer < 1.0f) {
                particle.afterImage.fadeTimer += 0.03f;
                particles->isEmit = true;
            }
            else {
                // 完全に透明になったら残像を削除
                particle.afterImage.isFading = false;
                particle.afterImage.posHistory.clear();
            }
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawMeteoriteParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        UpdateBlendMode(&particle.blendMode);

        // 残像を描画
        for (int j = 0; j < particle.afterImage.posHistory.size(); ++j) {

            particle.afterImage.pastPos = particle.afterImage.posHistory[j];

            particle.afterImage.colorAlpha = 1.0f - (j / static_cast<float>(particle.afterImage.maxHistory));
            particle.afterImage.scale = 1.0f - (j / static_cast<float>(particle.afterImage.maxHistory));

            if (!particle.isExist) {
                particle.afterImage.colorAlpha *= 1.0f - particle.afterImage.fadeTimer;
                particle.afterImage.scale *= 1.0f - particle.afterImage.fadeTimer;
            }

            Novice::DrawQuad(
                static_cast<int>(particle.afterImage.pastPos.x - particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y - particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.afterImage.pastPos.x + particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y - particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.afterImage.pastPos.x - particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y + particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.afterImage.pastPos.x + particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y + particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.srcW * particle.spriteNum), 0,
                static_cast<int>(particle.srcW), static_cast<int>(particle.srcH),
                particle.GH, (particle.afterImage.colorRGB << 8) | static_cast<unsigned int>(particle.afterImage.colorAlpha * 255));
        }

        if (particle.isExist) {
            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);
        }

        ResetBlendMode();
    };
}

void InitMeteoriteParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 7;
        particle.emitterRange = { 300, 20 };
        particle.easingInOut.interval = 0.01f;
        particle.width = 40;
        particle.height = 40;
        particle.color = 0xffa500ff;
        particle.startColor = 0xffa500ff;
        particle.endColor = 0xffa50000;
        particle.blendMode.choiceType = particles[i].blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.afterImage.colorRGB = 0xff8c00;
        particle.afterImage.posHistory.clear();
        particle.frameCount = 0;
    }
}

// 竜巻のようなパーティクル
void UpdateTornadeParticle(Particle* particles, int amount, Vector2* startPos, Vector2* endPos)
{
    if (particles->frameCount <= 0) {
        particles->frameCount = particles->appearInterval;
    }

    particles->isEmit = false;

    // フレームごとに新しいパーティクルを生成
    if (particles->frameCount == particles->appearInterval) {
        for (int i = 0; i < amount; ++i) {
            Particle& particle = particles[i]; // particles[i]を参照として取得

            if (!particle.hasExisted) {
                if (!particle.isExist) {
                    // startからendへの方向ベクトルを計算
                    particle.directionVec = { endPos->x - startPos->x, endPos->y - startPos->y };

                    // 方向ベクトルを正規化して弾の速度にする
                    particle.normalizedDirection = CalculateNormalize(particle.directionVec);

                    // 弾の速度
                    particle.speed = { 2.0f, 2.0f };

                    particle.pos.x = static_cast<float>(startPos->x) + (static_cast<int>(rand()) % particle.emitterRange.x - particle.emitterRange.x / 2);
                    particle.pos.y = static_cast<float>(startPos->y) + (static_cast<int>(rand()) % particle.emitterRange.y - particle.emitterRange.y / 2);

                    particle.velocity.x = particle.speed.x;
                    particle.velocity.y = particle.speed.y;

                    particle.isExist = true;
                    particle.blendMode.mode = particle.blendMode.choiceType;

                    particle.hasExisted = true;

                    break;
                }
            }
        }
    }

    particles->frameCount -= 1;

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            particles->isEmit = true;

            particle.theta += (static_cast<float>(M_PI) / 100.0f) * (0.5f + (rand() % 100) * 0.005f);

            // パーティクルの進行方向に基づいて弾の新しい位置を計算
            particle.pos.x += particle.normalizedDirection.x * particle.speed.x + cosf(particle.theta) * particle.amplitude;
            particle.pos.y += particle.normalizedDirection.y * particle.speed.y;

            if (particle.pos.x <= 0.0f || particle.pos.x >= kWindowWidth || particle.pos.y <= 0.0f || particle.pos.y >= kWindowHeight) {
                particle.isExist = false;
                particle.afterImage.isFading = true;
            }

            // 残像の処理
            particle.afterImage.frameCounter++;

            if (particle.afterImage.frameCounter >= 1) {

                particle.afterImage.posHistory.push_front(particle.pos);

                if (particle.afterImage.posHistory.size() > particle.afterImage.maxHistory) {
                    particle.afterImage.posHistory.pop_back();
                }

                // フレームカウンタをリセット
                particle.afterImage.frameCounter = 0;
            }
        }

        if (!particle.isExist && particle.afterImage.isFading) {

            // 残像の透明度を時間経過で減少させる
            if (particle.afterImage.fadeTimer < 1.0f) {
                particle.afterImage.fadeTimer += 0.03f;
                particles->isEmit = true;
            }
            else {
                // 完全に透明になったら残像を削除
                particle.afterImage.isFading = false;
                particle.afterImage.posHistory.clear();
            }
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawTornadeParticle(Particle* particles, int amount)
{

    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        UpdateBlendMode(&particle.blendMode);

        // 残像を描画
        for (int j = 0; j < particle.afterImage.posHistory.size(); ++j) {

            particle.afterImage.pastPos = particle.afterImage.posHistory[j];

            particle.afterImage.colorAlpha = 1.0f - (j / static_cast<float>(particle.afterImage.maxHistory));
            particle.afterImage.scale = 1.0f - (j / static_cast<float>(particle.afterImage.maxHistory));

            if (!particle.isExist) {
                particle.afterImage.colorAlpha *= 1.0f - particle.afterImage.fadeTimer;
                particle.afterImage.scale *= 1.0f - particle.afterImage.fadeTimer;
            }
            Novice::DrawQuad(
                static_cast<int>(particle.afterImage.pastPos.x - particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y - particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.afterImage.pastPos.x + particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y - particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.afterImage.pastPos.x - particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y + particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.afterImage.pastPos.x + particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y + particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.srcW * particle.spriteNum), 0,
                static_cast<int>(particle.srcW), static_cast<int>(particle.srcH),
                particle.GH, (particle.afterImage.colorRGB << 8) | static_cast<unsigned int>(particle.afterImage.colorAlpha * 255));
        }

        if (particle.isExist) {

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);
        }

        ResetBlendMode();
    };
}

void InitTornadeParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 3;
        particle.emitterRange = { 80, 40 };
        particle.easingInOut.interval = 0.01f;
        particle.width = 40;
        particle.height = 40;
        particle.color = 0x00ffffff;
        particle.startColor = 0x00ffffff;
        particle.endColor = 0x00ffff00;
        particle.blendMode.choiceType = particles[i].blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.afterImage.colorRGB = 0x8a2be2;
        particle.afterImage.posHistory.clear();
        particle.amplitude = 10.0f;
        particle.afterImage.fadeTimer = 0;
    }
}

// プレイヤー出現のパーティクル
void UpdateAppearAroundParticle(Particle* particles, int amount, Vector2* startPos)
{
    particles->angleStep = 360.0f / amount;

    particles->isEmit = false;

    // フレームごとに新しいパーティクルを生成

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (!particle.hasExisted) {
            if (!particle.isExist) {
                particle.angle = particles->angleStep * i;
                particle.theta = particle.angle * (float(M_PI) / 180.0f);
                particle.pos.x = static_cast<float>(startPos->x) + 50.0f * cosf(particle.theta);
                particle.pos.y = static_cast<float>(startPos->y) + 50.0f * sinf(particle.theta);

                particle.isExist = true;

                particle.easingOut.isEase = true;
                particle.hasExisted = true;
                particle.blendMode.mode = particle.blendMode.choiceType;

                break;
            }
        }
    }

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            particles->isEmit = true;

            if (particle.easingOut.isEase) {
                // 回転と移動の処理
                particle.angle += 2.0f;
                particle.theta = particle.angle * (float(M_PI) / 180.0f);

                // 回転後の位置を更新
                particle.pos.x = startPos->x + particle.radius * cosf(particle.theta);
                particle.pos.y = startPos->y + particle.radius * sinf(particle.theta);

                Vector2 direction = { startPos->x - particle.pos.x, startPos->y - particle.pos.y };
                float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

                particle.radius -= 0.8f;

                if (length < 0.5f) {
                    particle.isExist = false;
                    particle.isEmit = false;
                }
            }
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawAppearAroundParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitAppearAroundParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 1;
        particle.emitterRange = { 10, 10 };
        particle.easingOut.interval = 0.02f;
        particle.width = 40;
        particle.height = 40;
        particle.color = 0xff00ffff;
        particle.colorRGB = 0xff00ff;
        particle.colorAlpha = 0xff;
        particle.startColor = 0xff00ffff;
        particle.endColor = 0xff00ff00;
        particle.blendMode.choiceType = particle.blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.afterImage.colorRGB = 0xff00ff;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.speed = { 2, 2 };
        particle.elapsedTime = 0;
        particle.radius = 50;
    }
}

// プレイシーンの背景のパーティクル
void UpdatePlaySceneParticle(Particle* particles, int amount)
{
    if (particles->frameCount <= 0) {
        particles->frameCount = particles->appearInterval;
    }

    particles->isEmit = false;

    // フレームごとに新しいパーティクルを生成
    if (particles->frameCount == particles->appearInterval) {

        for (int i = 0; i < amount; ++i) {
            Particle& particle = particles[i];

            if (!particle.isExist) {

                particle.angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * float(M_PI);
                particle.pos.x = static_cast<float>(static_cast<int>(rand()) % 1280);
                particle.pos.y = static_cast<float>(static_cast<int>(rand()) % 720);

                particle.velocity.x = particle.speed.x * cosf(particle.angle);
                particle.velocity.y = particle.speed.y * sinf(particle.angle);

                particle.isExist = true;

                particle.easingIn.isEase = true;

                particle.colorAlpha = rand() % 200 + 28;
                particle.color = particle.colorAlpha | particle.startColor;

                particle.blendMode.mode = particle.blendMode.choiceType;

                break;
            }
        }
    }

    particles->frameCount -= 1;

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            particles->isEmit = true;

            Vector2 startScale = { 0.0f, 0.0f };
            Vector2 endScale = { 1.0f, 1.0f };
            if (particle.easingIn.isEase) {
                LinearInterpolation(startScale, endScale, particle.scale, particle.easingIn);
                CountEaseInOutTimer(particle.easingIn);
                if (!particle.easingIn.isEase) {
                    particle.easingInOut.isEase = true;
                }
            }

            if (particle.easingInOut.isEase) {
                LinearInterpolation(endScale, startScale, particle.scale, particle.easingInOut);
                CountEaseInOutTimer(particle.easingInOut);
            }

            particle.pos.x += particle.velocity.x;
            particle.pos.y += particle.velocity.y;

            if (!particle.easingInOut.isEase && !particle.easingIn.isEase) {
                particle.isExist = false;
            }
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawPlaySceneParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitPlaySceneParticle(Particle* particles, int amount)
{

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 40;
        particle.emitterRange = { 20, 20 };
        particle.easingInOut.interval = 0.002f;
        particle.width = 30;
        particle.height = 30;
        particle.color = 0xffffffff;
        particle.startColor = 0xffffff00;
        particle.endColor = 0xffffff00;
        particle.colorAlpha = 0xff;
        particle.colorRGB = 0xffffff;
        particle.blendMode.choiceType = particles[i].blendMode.Add;
        particle.GH = 0;
        particle.srcW = 80;
        particle.srcH = 80;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.speed = { 0.1f, 0.1f };
    }
}

// セレクトシーンの背景のパーティクル
void UpdateSelectSceneParticle(Particle* particles, int amount)
{
    if (particles->frameCount <= 0) {
        particles->frameCount = particles->appearInterval;
    }

    particles->isEmit = false;

    // フレームごとに新しいパーティクルを生成
    if (particles->frameCount == particles->appearInterval) {

        for (int i = 0; i < amount; ++i) {
            Particle& particle = particles[i];

            if (!particle.isExist) {

                particle.pos.x = static_cast<float>((rand()) % 1000);
                particle.pos.y = static_cast<float>((rand()) % 650);

                particle.speed.y = static_cast<float>(rand() % 2 + 0.5f);
                particle.speed.x = particle.speed.y;
                particle.velocity.x = particle.speed.x;
                particle.velocity.y = particle.speed.y;

                particle.isExist = true;

                particle.easingIn.isEase = true;

                particle.colorAlpha = rand() % 200 + 28;
                particle.color = particle.colorAlpha | particle.startColor;

                particle.blendMode.mode = particle.blendMode.choiceType;

                break;
            }
        }
    }

    particles->frameCount -= 1;

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            particles->isEmit = true;

            Vector2 startScale = { 0.0f, 0.0f };
            Vector2 endScale = { 1.0f, 1.0f };
            if (particle.easingIn.isEase) {
                LinearInterpolation(startScale, endScale, particle.scale, particle.easingIn);
                CountEaseInOutTimer(particle.easingIn);
                if (!particle.easingIn.isEase) {
                    particle.easingInOut.isEase = true;
                }
            }

            if (particle.easingInOut.isEase) {
                LinearInterpolation(endScale, startScale, particle.scale, particle.easingInOut);
                CountEaseInOutTimer(particle.easingInOut);
            }

            particle.pos.x += particle.velocity.x;
            particle.pos.y += particle.velocity.y;

            if (!particle.easingInOut.isEase && !particle.easingIn.isEase) {
                particle.isExist = false;
            }
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawSelectSceneParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitSelectSceneParticle(Particle* particles, int amount)
{

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 40;
        particle.emitterRange = { 20, 20 };
        particle.easingInOut.interval = 0.002f;
        particle.width = 30;
        particle.height = 30;
        particle.color = 0xffffffff;
        particle.startColor = 0x00ff0000;
        particle.endColor = 0xffffff00;
        particle.colorAlpha = 0xff;
        particle.colorRGB = 0x00ff00;
        particle.blendMode.choiceType = particles[i].blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.speed = { 0.1f, 0.1f };
    }
}

// タイトルシーンの背景パーティクル
void UpdateTitleSceneParticle(Particle* particles, int amount)
{

    particles->isEmit = false;

    // フレームごとに新しいパーティクルを生成

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (!particle.isExist) {

            particle.randNum = rand() % 4;

            if (particle.randNum == 0) {
                particle.pos.x = 0;
                particle.pos.y = static_cast<float>((rand()) % 720);
            }
            else if (particle.randNum == 1) {
                particle.pos.x = 1280;
                particle.pos.y = static_cast<float>((rand()) % 720);
            }
            else if (particle.randNum == 2) {
                particle.pos.x = static_cast<float>((rand()) % 1280);
                particle.pos.y = 0;
            }
            else if (particle.randNum == 3) {
                particle.pos.x = static_cast<float>((rand()) % 1280);
                particle.pos.y = 720;
            }

            particle.startPos = { particle.pos.x, particle.pos.y };

            particle.speed.y = static_cast<float>(rand() % 2 + 0.5f);
            particle.speed.x = particle.speed.y;
            particle.velocity.x = particle.speed.x;
            particle.velocity.y = particle.speed.y;

            particle.isExist = true;

            particle.easingInOut.isEase = true;

            particle.blendMode.mode = particle.blendMode.choiceType;

            break;
        }
    }

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            particles->isEmit = true;

            if (particle.easingInOut.isEase) {
                ColorLinearInterpolation(particle.startColor, particle.endColor, particle.color, particle.easingInOut);
                CountEaseInOutTimer(particle.easingInOut);

                if (!particle.easingInOut.isEase) {
                    particle.easingOut.isEase = true;
                }
            }

            if (particle.easingOut.isEase) {
                LinearInterpolation(
                    particle.startPos,
                    particle.endPos,
                    particle.pos,
                    particle.easingOut);
                CountEaseOutTimer(particle.easingOut);

                if (!particle.easingOut.isEase) {
                    particle.easingIn.isEase = true;
                }
            }

            if (particle.easingIn.isEase) {
                ColorLinearInterpolation(particle.endColor, particle.startColor, particle.color, particle.easingIn);
                CountEaseInOutTimer(particle.easingIn);
            }

            if (!particle.easingInOut.isEase && !particle.easingOut.isEase && !particle.easingIn.isEase) {
                particle.isExist = false;
            }
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawTitleSceneParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            UpdateBlendMode(&particle.blendMode);

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);

            ResetBlendMode();
        }
    };
}

void InitTitleSceneParticle(Particle* particles, int amount)
{

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 40;
        particle.emitterRange = { 20, 20 };
        particle.easingInOut.interval = 0.01f;
        particle.width = 30;
        particle.height = 30;
        particle.color = 0xffffff00;
        particle.startColor = 0xffffff00;
        particle.endColor = 0xffffffff;
        particle.colorAlpha = 0xff;
        particle.colorRGB = 0x00ff00;
        particle.blendMode.choiceType = particles[i].blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.speed = { 0.1f, 0.1f };
        particle.startPos = {};
        particle.endPos = { 426, 420 };
        particle.easingOut.isEase = false;
    }
}

// タイトルシーンの背景の風のパーティクル
void ApplyRotation(Particle& particle, float angle)
{
    // 回転行列を使って回転を適用
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);

    float newX = cosAngle * particle.velocity.x - sinAngle * particle.velocity.y;
    float newY = sinAngle * particle.velocity.x + cosAngle * particle.velocity.y;

    particle.velocity.x = newX;
    particle.velocity.y = newY;
}

void UpdateTitleWindParticle(Particle* particles, int amount)
{
    if (particles->frameCount <= 0) {
        particles->frameCount = particles->appearInterval;
    }

    particles->isEmit = false;

    // フレームごとに新しいパーティクルを生成
    if (particles->frameCount == particles->appearInterval) {
        for (int i = 0; i < amount; ++i) {
            Particle& particle = particles[i];

            if (!particle.isExist) {

                particle.randNum = rand() % 2;

                if (particle.randNum == 0) {
                    particle.p0 = { float(rand() % 400), float(rand() % 500 + 200) };
                    particle.p1 = { particle.p0.x + float(rand() % 100 + 200),
                        particle.p0.y + float(rand() % 100 + 150) };
                    particle.p2 = { particle.p1.x + float(rand() % 100 + 200),
                        particle.p0.y + float(rand() % 100 - 150) };
                    particle.p3 = { particle.p2.x + float(rand() % 100 + 200),
                        particle.p0.y + float(rand() % 50 - 25) };
                }
                else if (particle.randNum == 1) {
                    particle.p0 = { float(rand() % 400), float(rand() % 500 + 200) };
                    particle.p1 = { particle.p0.x + float(rand() % 100 + 200),
                        particle.p0.y + float(rand() % 100 - 150) };
                    particle.p2 = { particle.p1.x + float(rand() % 100 + 200),
                        particle.p0.y + float(rand() % 100 + 150) };
                    particle.p3 = { particle.p2.x + float(rand() % 100 + 200),
                        particle.p0.y + float(rand() % 50 - 25) };
                }

                particle.isExist = true;

                particle.afterImage.fadeTimer = 0;

                particle.easingIn.isEase = true;

                particle.blendMode.mode = particle.blendMode.choiceType;

                break;
            }
        }
    }
    particles->frameCount -= 1;

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        if (particle.isExist) {
            particles->isEmit = true;
            // 進行状況に応じたベジエ曲線計算

            if (particle.easingIn.isEase) {
                particle.pos = CubicBezier(particle.p0, particle.p1, particle.p2, particle.p3, &particle.easingIn);
                CountEaseOutTimer(particle.easingIn);
            }

            // ベジエ曲線に沿って位置を計算

            /*if (particle.easingOut.isEase)
            {
                    Vector2 startScale = { 1.0f,1.0f };
                    Vector2 endScale = { 0.0f,0.0f };
                    LinearInterpolation(startScale, endScale, particle.scale, particle.easingOut);
                    CountEaseInOutTimer(particle.easingOut);
            }*/

            if (!particle.easingIn.isEase) {
                particle.isExist = false;
                particle.afterImage.isFading = true;
            }

            // 残像の処理
            particle.afterImage.frameCounter++;

            if (particle.afterImage.frameCounter >= 1) {

                particle.afterImage.posHistory.push_front(particle.pos);

                if (particle.afterImage.posHistory.size() > particle.afterImage.maxHistory) {
                    particle.afterImage.posHistory.pop_back();
                }

                // フレームカウンタをリセット
                particle.afterImage.frameCounter = 0;
            }
        }

        if (!particle.isExist && particle.afterImage.isFading) {
            // 残像の透明度を時間経過で減少させる
            if (particle.afterImage.fadeTimer < 1.0f) {
                particle.afterImage.fadeTimer += 0.03f;

            }
            else {
                // 完全に透明になったら残像を削除
                particle.afterImage.posHistory.clear();
                particle.afterImage.isFading = false;
            }
        }

        CalcVertexRectangle(&particle);
        ConvertWorldToScreenRectangle(&particle);
    }
}

void DrawTitleWindParticle(Particle* particles, int amount)
{
    for (int i = 0; i < amount; i++) {
        Particle& particle = particles[i];

        UpdateBlendMode(&particle.blendMode);

        // 残像を描画
        for (int j = 0; j < particle.afterImage.posHistory.size(); ++j) {

            particle.afterImage.pastPos = particle.afterImage.posHistory[j];

            particle.afterImage.colorAlpha = 1.0f - (j / static_cast<float>(particle.afterImage.maxHistory));
            particle.afterImage.scale = 1.0f - (j / static_cast<float>(particle.afterImage.maxHistory));

            if (!particle.isExist) {
                particle.afterImage.colorAlpha *= 1.0f - particle.afterImage.fadeTimer;
                particle.afterImage.scale *= 1.0f - particle.afterImage.fadeTimer;
            }

            Novice::DrawQuad(
                static_cast<int>(particle.afterImage.pastPos.x - particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y - particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.afterImage.pastPos.x + particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y - particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.afterImage.pastPos.x - particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y + particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.afterImage.pastPos.x + particle.width * particle.afterImage.scale / 2), kWindowHeight - static_cast<int>(particle.afterImage.pastPos.y + particle.height * particle.afterImage.scale / 2),
                static_cast<int>(particle.srcW * particle.spriteNum), 0,
                static_cast<int>(particle.srcW), static_cast<int>(particle.srcH),
                particle.GH, (particle.afterImage.colorRGB << 8) | static_cast<unsigned int>(particle.afterImage.colorAlpha * 255));
        }

        if (particle.isExist) {

            DrawQuadWithData(&particle, particle.srcW, particle.srcH, particle.GH, particle.spriteNum, 0, particle.color);
        }

        ResetBlendMode();
    };
}

void InitTitleWindParticle(Particle* particles, int amount)
{

    for (int i = 0; i < amount; ++i) {
        Particle& particle = particles[i];

        particle.appearInterval = 150;
        particle.emitterRange = { 20, 20 };
        particle.easingInOut.interval = 0.01f;
        particle.easingIn.interval = 0.005f;
        particle.width = 10;
        particle.height = 10;
        particle.color = 0xffffff45;
        particle.startColor = 0xffffff45;
        particle.endColor = 0xffffff00;
        particle.colorAlpha = 0xff;
        particle.colorRGB = 0x00ff00;
        particle.blendMode.choiceType = particles[i].blendMode.Add;
        particle.GH = GHs[TextureName::Particle1];
        particle.srcW = 80;
        particle.srcH = 80;
        particle.isExist = false;
        particle.hasExisted = false;
        particle.speed = { 0.1f, 0.1f };
        particle.startPos = {};
        particle.easingOut.isEase = false;
        particle.afterImage.colorRGB = 0xffffff;
        particle.afterImage.posHistory.clear();

        particle.afterImage.fadeTimer = 0;
    }
}