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
void Map::DrawMap(Camera* camera)
{
    for (int i = 0; i < kFloorHeight; ++i)
    {
        for (int j = 0; j < kFloorWidth; ++j)
        {
            DrawQuadWithData(&chip[i][j].GetRectangleObject(), 0, 0, 0, 0, 0, chip[i][j].GetColor());
        }
    }

    // グリッド線を描画する処理
    for (int i = 0; i <= kFloorHeight; ++i) {
        // カメラ行列を使って、グリッド線の始点と終点の座標を変換
        Vector2 start = { -1275, (float)i * 50 - 25 };
        Vector2 end = { (float)kWindowWidth-1275, (float)i * 50 - 25 };

        // 座標変換を適用
        start = camera->Transform(start, camera->cameraMatrix);  // カメラ行列で変換
        end = camera->Transform(end, camera->cameraMatrix);      // 同上

        // 変換後の座標で線を描画
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, BLACK);
    }

    for (int i = 0; i <= kFloorWidth; ++i) {
        // カメラ行列を使って、グリッド線の始点と終点の座標を変換
        Vector2 start = { (float)i * 50 - 1275, -25 };
        Vector2 end = { (float)i * 50 - 1275, (float)kWindowHeight-25 };

        // 座標変換を適用
        start = camera->Transform(start, camera->cameraMatrix);  // カメラ行列で変換
        end = camera->Transform(end, camera->cameraMatrix);      // 同上

        // 変換後の座標で線を描画
        Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, BLACK);
    }
}

