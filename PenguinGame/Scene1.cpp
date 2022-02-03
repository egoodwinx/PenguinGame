/*
 * File:			Scene1.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains methods for scene1.
 * First Version:	Febuary 10, 2019
 */

#include "scene1.h"

/*
 * FUNC:	Scene1
 * DESC:	Constructor for the scene1 taking in the required assets
 * PARAMS:	
 *	Grid* - The grid
 *	DrawingManager* - The drawing manager
 *	AssetManager* - the asset manager 
 * RET:		na
 */
Scene1::Scene1(Grid* grid, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo) : Scene (grid, drawingManager, assetManager, gameInfo)
{
	GenerateSceneAssets();
}

/*
 * FUNC:	GetCoinY
 * DESC:	Get the coin's y position based on the given x position.
 * PARAMS:	int x - the x position to use to get the y position
 * RET:		int - the y position of the coin 
 */
int Scene1::GetCoinY(int x)
{
	return coins[x];
}

/*
 * FUNC:	RemoveCoin
 * DESC:	remove the coin at the given x coordinate in the grid.
 * PARAMS:	int x - the x position to remove the coin at.
 * RET:		void
 */
void Scene1::RemoveCoin(int x)
{
	try
	{
		coins.erase(x);
	}
	catch (std::exception e)
	{

	}
}


/*
 * FUNC:	GenerateSceneAssets
 * DESC:	Generate the scene1 assets 
 * PARAMS:	void
 * RET:		void
 */
void Scene1::GenerateSceneAssets()
{
	std::pair<int, int> coordinates;
	std::pair<Sprite*, std::pair<int, int>> asset;

	GenerateHillsAndHoles();

	for (int i = 0; i < Grid::COLS; i++)
	{
		for (int j = 0; j < Grid::ROWS; j++)
		{
			if (j <= CLOUD_AREA)
			{
				if (RandomizeByPercent(CLOUD_PERCENT))
				{
					coordinates.first = i;
					coordinates.second = j;
					asset.first = p_AssetManager->Sprites.at(p_AssetManager->cloud);
					asset.second = coordinates;
					clouds.push_back(asset);
				}
			}
			else if (j == (ground.at(i) - 1))
			{
				bool hasDrawn = false;
				 if (RandomizeByPercent(PLANT_PERCENT))
				 {
					 if (RandomizeByPercent(EACH_PLANT_PERCENT))
					 {
						 coordinates.first = i;
						 coordinates.second = j;
						 asset.first = p_AssetManager->Sprites.at(p_AssetManager->shrub);
						 asset.second = coordinates;
						 sceneAssets.push_back(asset);
					 }
					 else if (RandomizeByPercent(EACH_PLANT_PERCENT))
					 {
						 coordinates.first = i;
						 coordinates.second = j;
						 asset.first = p_AssetManager->Sprites.at(p_AssetManager->tree1);
						 asset.second = coordinates;
						 sceneAssets.push_back(asset);
					 }
					 else 
					 {
						 coordinates.first = i;
						 coordinates.second = j;
						 asset.first = p_AssetManager->Sprites.at(p_AssetManager->tree2);
						 asset.second = coordinates;
						 sceneAssets.push_back(asset);
					 }
				 }
			}
		}
	}
}

/*
 * FUNC:	DrawDefaultBackground
 * DESC:	Draw the default background
 * PARAMS:	void
 * RET:		void
 */
void Scene1::DrawDefaultBackground()
{
	// sky
	p_DrawingManager->DrawRectangle(p_Grid->GetRow(FIRST_ROW), D2D1::ColorF::SkyBlue);
	p_DrawingManager->DrawRectangle(p_Grid->GetRow(SECOND_ROW), D2D1::ColorF::SkyBlue);
	p_DrawingManager->DrawRectangle(p_Grid->GetRow(THIRD_ROW), D2D1::ColorF::SkyBlue);
	p_DrawingManager->DrawRectangle(p_Grid->GetRow(FOURTH_ROW), D2D1::ColorF::SkyBlue);
	p_DrawingManager->DrawRectangle(p_Grid->GetRow(FIFTH_ROW), D2D1::ColorF::SkyBlue);
	//horizon
	p_DrawingManager->DrawRectangle(p_Grid->GetRow(SIXTH_ROW), D2D1::ColorF::LightBlue);
	p_DrawingManager->DrawRectangle(p_Grid->GetRow(SEVENTH_ROW), D2D1::ColorF::LightBlue);
	p_DrawingManager->DrawRectangle(p_Grid->GetRow(EIGHTH_ROW), D2D1::ColorF::LightBlue);
	p_DrawingManager->DrawRectangle(p_Grid->GetRow(NINETH_ROW), D2D1::ColorF::LightBlue);
	p_DrawingManager->DrawRectangle(p_Grid->GetRow(TENTH_ROW), D2D1::ColorF::LightBlue);
	DrawHillsAndHoles();
	DrawClouds();
}

/*
* Name:		GenerateHillsAndHoles()
* Desc:		Generate the procedurally generated ground by increasing,decreasing height and creating holes.
* Param:	void
* return:	void
*/
void Scene1::GenerateHillsAndHoles()
{
	int lastYHeight = GROUND_DEFAULT;
	for (int i = 0; i < p_Grid->COLS; i++)
	{
		if ((RandomizeByPercent(HOLE_PERCENT) &&
			(i > 1) && // no hole for first two blocks
			(ground[i-1] != NO_GROUND) && // make sure we dont have two holes together
			(i != p_Grid->COLS-1))) // no hole at end
		{
			ground.insert(std::pair<int,int>(i, NO_GROUND));
			containsHoles = true;
		}
		else
		{
			if (!RandomizeByPercent(STAY_SAME_HEIGHT_PERCENT))
			{
				if (RandomizeByPercent(CHANGE_HEIGHT_UPDOWN_PERCENT))
				{
					lastYHeight += 1;
					if (lastYHeight > GROUND_MAX_Y)
					{
						lastYHeight = GROUND_MAX_Y;
					}
				}
				else
				{
					lastYHeight -= 1;
					if (lastYHeight < GROUND_MIN_Y)
					{
						lastYHeight = GROUND_MIN_Y;
					}
				}
			}
			ground.insert(std::pair<int, int>(i, lastYHeight));
		}
	}
}

/*
* Name:		DrawHillsAndHoles()
* Desc:		Draw the hills and holes over the bakground.
* Param:	void
* return:	void
*/
void Scene1::DrawHillsAndHoles()
{
	for(int i= 0; i < p_Grid->COLS; i++)
	{
		int yValue = ground.at(i);
		D2D1::ColorF colour = D2D1::ColorF::AliceBlue;
		if (yValue == NO_GROUND)
		{
			yValue = GROUND_DEFAULT;
			colour = D2D1::ColorF::LightBlue;
		}
		p_DrawingManager->DrawRectangle(p_Grid->GetArea(i, yValue,i,9), colour);
	}
}

/*
* Name:		DrawScoreAndLives()
* Desc:		Draw the current score and lives
* Param:	void
* return:	void
*/
void Scene1::DrawScoreAndLives()
{
	p_DrawingManager->DrawString(p_Grid->GetBlock(9, 1), "Score: " + std::to_string(p_GameInfo->GetScore()), D2D1::ColorF::Black, 20);
	p_DrawingManager->DrawString(p_Grid->GetBlock(9, 2), "Lives: " + std::to_string(p_GameInfo->GetLives()), D2D1::ColorF::Black, 20);
}

/*
* Name:		DrawScene()
* Desc:		Draw the current scene.
* Param:	void
* return:	void
*/
void Scene1::DrawScene()
{
	Scene::DrawScene();
	DrawScoreAndLives();
}

/*
 * FUNC:	DrawClouds
 * DESC:	Draw the clouds that are moving across the screne.
 * PARAMS:	void
 * RET:		void
 */
void Scene1::DrawClouds()
{
	std::pair<int, int> coordinates;
	std::pair<Sprite*, std::pair<int, int>> asset;

	moveValue+=1;
	if ((int(floor(moveValue))% int(p_Grid->GetBlock(0,0).width)) == 0)
	{			
		std::pair<int, int> coordinates;
		std::vector<std::pair<Sprite*, std::pair<int, int>>>::iterator it;	
		moveValue = 0;
		for (unsigned int i = 0; i < clouds.size(); i++)
		{
			clouds.at(i).second.first -= 1;
		}
		for ( it = clouds.begin(); it != clouds.end(); ++it)
		{
			coordinates = it->second;
			if (coordinates.first < 0)
			{
				clouds.erase(it);
				it = clouds.begin();
				if (it== clouds.end())
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
		for (int j = 0; j < CLOUD_AREA; j++)
		{
			if (j <= CLOUD_AREA)
			{
				if (RandomizeByPercent(CLOUD_PERCENT))
				{
					coordinates.first = 9;
					coordinates.second = j;
					asset.first = p_AssetManager->Sprites.at(p_AssetManager->cloud);
					asset.second = coordinates;
					clouds.push_back(asset);
				}
			}
		}
	}
	for(unsigned int i = 0; i < clouds.size(); i++)
	{
		p_DrawingManager->DrawSprite(p_Grid->GetBlock(clouds.at(i).second.first, clouds.at(i).second.second), clouds.at(i).first, -moveValue);
	}
}