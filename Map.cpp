#include "Structures.h"
#include "Camera.h"
#include "Draw.h"
#include "Rectangle.h"
#include "Map.h"

//========================================================
// マップの設定、初期化
//========================================================

// マップの設定
void Map::SetMap()
{
    int static chipData[stageSum][kFloorHeight][kFloorWidth] = 
    {
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
        }
    };

    // チップデータの設定
    for (int k = stageNo_; k < stageNo_ + 1; ++k)
    {
        for (int i = 0; i < kFloorHeight; ++i)
        {
            for (int j = 0; j < kFloorWidth; ++j)
            {

                chip[i][j].SetChipType(chipData[k][i][j]);

                CalcVertexRectangle(&chip[i][j].GetRectangleObject());

                switch (chip[i][j].GetChipType())
                {
                case none:
                    chip[i][j].SetColor(0x00000000);
                    break;
                case block:
                    chip[i][j].SetColor(0xff00ffff);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

 // マップの描画
void Map::DrawMap()
{
    for (int i = 0; i < kFloorHeight; ++i)
    {
        for (int j = 0; j < kFloorWidth; ++j)
        {
            DrawQuadWithData(&chip[i][j].GetRectangleObject(), 0, 0, 0, 0, 0, chip[i][j].GetColor());
        }
    }
}