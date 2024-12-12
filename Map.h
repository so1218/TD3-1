#pragma once

#include "Structures.h"
#include "Draw.h"
#include "Rectangle.h"


enum ChipType
{
    none = 0,
    block = 1,
};

class MapChip: GameObject
{
public:

    //コンストラクタで初期化
    MapChip()
    {
        ro_.width = width_;
        ro_.height = height_;
    }

    // ゲッターとセッター
    //メンバ関数

    // チップの位置を設定
    Vector2 GetPosition() const { return pos_; }
    void SetPosition(float newPosX, float newPosY)
    {
        pos_.x = newPosX;
        pos_.y = newPosY;
        ro_.wCenterPos.x = newPosX + width_ / 2;
        ro_.wCenterPos.y = newPosY + height_ / 2;
    }

    //メンバ変数
    float GetHeight() const { return height_; }
    void SetHeight(float newHeight) { height_ = newHeight; }

    float GetWidth() const { return width_; }
    void SetWidth(float newWidth) { width_ = newWidth; }

    unsigned int GetColor() const { return color_; }
    void SetColor(unsigned int newColor) { color_ = newColor; }

    int GetChipType() const { return chipType_; }
    void SetChipType(int newChipType) { chipType_ = newChipType; }

    RectangleObject& GetRectangleObject() { return ro_; }
    void SetRectangleObject(const RectangleObject& newRectangle) { ro_ = newRectangle; }

    
   
private:
    //メンバ変数
    int chipType_ = 0;
    Vector2 pos_;
    float height_ = 50.0f;
    float width_ = 50.0f;
    unsigned int color_ = WHITE;
        
    //Rectangleオブジェクト
    RectangleObject ro_;
};

class Map
{
public:
    //コンストラクタで初期化
    Map()
    {
        // チップの座標と角を設定
        for (int i = 0; i < kFloorHeight; ++i)
        {
            for (int j = 0; j < kFloorWidth; ++j)
            {
                chip[i][j].SetPosition(float((j * chip[i][j].GetWidth())),
                    float(GameManager::screenTop - chip[i][j].GetHeight() - (i * chip[i][j].GetHeight())));
            }
        }
    }

    //メンバ関数
    void SetMap();
    void DrawMap();


    //メンバ変数
    //ゲッターとセッター
    static int GetFloorWidth() { return kFloorWidth; }
    static int GetFloorHeight() { return kFloorHeight; }

    int GetStageNo() const { return stageNo_; }
    void SetStageNo(int newStage) { stageNo_ = newStage; }

    MapChip& GetChip(int x, int y)
    {
        if (x >= 0 && x < kFloorWidth && y >= 0 && y < kFloorHeight)
        {
            return chip[y][x];
        }
        //エラーチェック、MapChipを返す
        static MapChip defaultChip;
        return defaultChip;
    }

    void SetChip(int x, int y, const MapChip& mapChip)
    {
        if (x >= 0 && x < kFloorWidth && y >= 0 && y < kFloorHeight)
        {
            chip[y][x] = mapChip;
        }
    }

private:
    //メンバ変数
    static const int kFloorWidth = 26;
    static const int kFloorHeight = 14;
    static const int stageSum = 1;
    int stageNo_ = 0;

    Easing easing;
    Vector2 pos;
    float easingTimer = 0.0f;

    MapChip chip[kFloorHeight][kFloorWidth]; // チップの配列

    float targetPosX[kFloorHeight][kFloorWidth]; // ターゲットのX位置
    float targetPosY[kFloorHeight][kFloorWidth]; // ターゲットのY位置
    float moveSpeed = 0.0f; // 補完速度
};