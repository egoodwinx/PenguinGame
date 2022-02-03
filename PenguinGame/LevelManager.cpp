/*
 * File:			LevelManager.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains scene manager methods.
 * First Version:	February 10, 2019
 */


#include "LevelManager.h"
#include "Level1.h"
LevelManager::Levels LevelManager::currentLevel;
bool LevelManager::levelChanged = false;
bool LevelManager::quit = false;



/*
 * FUNC:	LevelManager
 * DESC:	Constructor
 * PARAMS:	
 *	GameWindow* gameWindow- the game window
 *	DrawingManager* drawingManager - the drawing manager 
 *	AssetManager* assetManager - the asset manager 
 * RET:		na
 */
LevelManager::LevelManager(GameWindow* gameWindow, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo, D3DClass* d3d)
{
	this->p_D3D = d3d;
	this->p_GameInfo = gameInfo;
	this->p_GameWindow = gameWindow;
	this->p_DrawingManager = drawingManager;
	this->p_AssetManager = assetManager;
	this->p_Level = new Level0(gameWindow, drawingManager, assetManager, gameInfo, d3d);
}

/*
 * FUNC:	LevelManager
 * DESC:	Constructor
 * PARAMS: 
 * RET:
 */
Level* LevelManager::GetLevel()
{
	if (levelChanged)
	{
		switch (currentLevel)
		{
		case QUIT:
			quit = true;
			break;
		case MAIN:
			p_Level = new Level0(p_GameWindow, p_DrawingManager, p_AssetManager, p_GameInfo, p_D3D);
			break;
		case LEVEL1:
			p_Level = new Level1(p_GameWindow, p_DrawingManager, p_AssetManager, p_GameInfo);
			break;
		}
		levelChanged = false;
	}

	return p_Level;
}

/*
 * FUNC:	ChangeLevel
 * DESC:	Change the current level to the given level
 * PARAMS: Levels level - the level to change it to
 * RET: void
 */
void LevelManager::ChangeLevel(Levels level)
{
	currentLevel = level;
	levelChanged = true;
}

/*
 * FUNC:	ShouldQuit
 * DESC:	Should we quit the application
 * PARAMS: void
 * RET: bool - should we quit the application
 */
bool LevelManager::ShouldQuit()
{
	return quit;
}

/*
 * FUNC:	GetCurrentLevel
 * DESC:	Get the current level
 * PARAMS: void
 * RET: Levels - the current level type
 */
LevelManager::Levels LevelManager::GetCurrentLevel()
{
	return currentLevel;
}
