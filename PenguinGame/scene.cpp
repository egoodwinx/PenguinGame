/*
 * File:			Scene.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains scene methods.
 * First Version:	February 10, 2019
 */

#include "scene.h"

 /*
  * FUNC:	Scene
  * DESC:	Constructor
  * PARAMS:
  *	Grid* - the grid
  *	DrawingManager* drawingManager - the drawing manager
  *	AssetManager* assetManager - the asset manager
  * RET:
  */
Scene::Scene(Grid* grid, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo)
{
	this->p_Grid = grid;
	this->p_DrawingManager = drawingManager;
	this->p_AssetManager = assetManager;
	this->rngEngine.seed(GetCurrentTime());
	this->p_GameInfo = gameInfo;
}

/*
 * FUNC:	GetGrid
 * DESC:	Get the grid
 * PARAMS:	void
 * RET:		Grid* - the grid
 */
Grid* Scene::GetGrid()
{
	return p_Grid;
}

/*
 * FUNC:	DrawScene
 * DESC:	Draw the scene
 * PARAMS:	void
 * RET:		void
 */
void Scene::DrawScene()
{
	DrawDefaultBackground();
	DrawDefaultBackgroundAssets();
}

/*
 * FUNC:	GetGroundBlockY
 * DESC:	Get the ground y position from the x coordinate.
 * PARAMS:	int x - the x position of the block we're looking for
 * RET:		int - the y position of the ground.
 */
int Scene::GetGroundBlockY(int x)
{
	int y = GROUND_NOT_SET;
	if ((unsigned int)x < ground.size())
	{
		y = ground.at(x);
	}
	return y;
}

/*
 * FUNC:	IsCursorOverArea
 * DESC:	Is the cursor over the given area
 * PARAMS: Grid::Block area - the area to look over
 * RET:		bool - is the cursor over the area
 */
bool Scene::IsCursorOverArea(Grid::Block area)
{
	std::pair<int, int> cursor = p_DrawingManager->GetCursorPosition();
	Grid::Block block = area;
	bool ret = false;

	if ((cursor.first < block.bottomRight.x) && (cursor.first > block.topLeft.x) &&
		(cursor.second < block.bottomRight.y) && (cursor.second > block.topLeft.y))
	{
		ret = true;
	}

	return ret;
}

/*
 * FUNC:	RandomizeByPercent
 * DESC:	Given a percent randomize it and then return if the percent hit or not
 * PARAMS:	
 *	unsigned int percent - the percent 
 * RET:		bool - true or false, random based on percentage
 */
bool Scene::RandomizeByPercent(unsigned int percent)
{
	std::uniform_int_distribution<uint32_t> uint_dis;
	bool canDrawSprite = (uint_dis(rngEngine) % 100) < percent;
	return canDrawSprite;
}

int Scene::GetRandomInt(int min, int max)
{
	std::uniform_int_distribution<std::mt19937::result_type> uint_dis(min, max);
	return uint_dis(rngEngine);
}

/*
 * FUNC:	DrawDefaultBackgroundAssets
 * DESC:	Draw all the banground assets generated
 * PARAMS:	void
 * RET:		void
 */
void Scene::DrawDefaultBackgroundAssets()
{
	for (unsigned int i = 0; i <sceneAssets.size(); i++)
	{
		p_DrawingManager->DrawSprite(p_Grid->GetBlock(sceneAssets.at(i).second.first, sceneAssets.at(i).second.second), sceneAssets.at(i).first);
	}
}

bool Scene::SceneContainsHoles()
{
	return containsHoles;
}