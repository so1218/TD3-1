#pragma once

#include "Structures.h"

class Character
{
public:
    //コンストラクタで初期化
    Character(float posX, float posY, float speedX, float speedY)
        : pos_{ posX, posY }, velocity_{ speedX, speedY }, width_(50), height_(50), color_(0xFFFFFFFF) {}

    //デストラクタ
    virtual ~Character() {}

    //ゲッターとセッター
    Vector2 GetPos() const { return pos_; }
    void SetPos(Vector2 newPos) { pos_ = newPos; }

    Vector2 GetVelocity() const { return velocity_; }
    void SetVelocity(Vector2 newVelocity) { velocity_ = newVelocity; }

    int GetHeight() const { return height_; }
    void SetHeight(int newHeight) { height_ = newHeight; }

    int GetWidth() const { return width_; }
    void SetWidth(int newWidth) { width_ = newWidth; }

    unsigned int GetColor() const { return color_; }
    void SetColor(unsigned int newColor) { color_ = newColor; }

protected:
    //メンバ変数
    Vector2 pos_;      
    Vector2 velocity_; 
    int width_;        
    int height_;       
    unsigned int color_; 
};