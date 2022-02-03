/*
 * File:			GameManager.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the gamemanager class definition.
 * First Version:	February 20, 2019
 */

#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "GameWindow.h"
#include "D2DClass.h"
#include "LevelManager.h"
#include "assetManager.h"
#include "Level1.h"
#include "inputclass.h"
#include "GameInfo.h"

class D3DClass;

/*
 * Class	GameManager
 * Desc:	Manages the game.
 */
class GameManager
{
public:
	GameManager::GameManager(GameWindow* gameWindow, D2DClass* d2d, D3DClass* d3d, InputClass* input);
	void Shutdown();
	void Frame();
	void InitialLoad();
	bool Quit();
private:
	GameWindow* p_GameWindow;
	D2DClass* p_D2D;
	D3DClass* p_D3D;
	DrawingManager* p_DrawingManager;
	LevelManager* p_LevelManager;
	AssetManager* p_AssetManager;
	Level* p_CurrentLevel;
	InputClass* p_Input;
	GameInfo* p_GameInfo;
	bool quit = false;
};
#endif