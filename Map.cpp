#include "Structures.h"
#include "Camera.h"
#include "Draw.h"
#include "Rectangle.h"

//========================================================
// マップの設定、初期化
//========================================================

void MapSetting(Map* map)
{
	//マップチップの配置
	int static chipData[map->stageSum][map->kFloorHeight][map->kFloorWidth]
	{
		//ステージ0
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
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		},


	};

	if (map->stageNo == 0)
	{
		
	}


	
	
	//チップデータを設定
	for (int k = map->stageNo; k < map->stageNo + 1; ++k)
	{
		
		for (int i = 0; i < map->kFloorHeight; ++i)
		{
			for (int j = 0; j < map->kFloorWidth; ++j)
			{
				map->chip[i][j].chipType = chipData[k][i][j];

				map->chip[i][j].ro.width = 50;
				map->chip[i][j].ro.height = 50;
				CalcVertexRectangle(&map->chip[i][j].ro);

				switch (map->chip[i][j].chipType)
				{
					case map->none:

						map->chip[i][j].color = 0x00000000;
						

						break;			

					case map->block:

						map->chip[i][j].color = 0xff00ffff;

						break;

					default:

						break;
				}
			}

		}
	}
}

//========================================================
// マップの描画
//========================================================

void DrawMap(Map* map)
{
	for (int i = 0; i < map->kFloorHeight; ++i)
	{
		for (int j = 0; j < map->kFloorWidth; ++j)
		{
			DrawQuadWithData(&map->chip[i][j].ro, 0, 0, 0, 0, map->chip[i][j].color);

			Novice::ScreenPrintf(0, 20, "map->chip[i][j].ro.x : %.1f", map->chip[2][0].camera.scale.x);
			Novice::ScreenPrintf(0, 40, "map->chip[i][j].ro.x : %.1f", map->chip[2][0].camera.scale.y);
		}
	}

}