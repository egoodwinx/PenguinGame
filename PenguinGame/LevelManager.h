/*
 * File:			LevelManager.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A2
 * Description:		Contains the class definition for the LevelManager class.
 * First Version:	March 22 , 2019
 */

#pragma once
#include "GameWindow.h"
#include "DrawingManager.h"
#include "Level.h"
#include "Level0.h"

 /*
 *	Class: LevelManager
 *	Desc: Models the LevelManager. Manages the levels and which one is the current level.
 */
class LevelManager
{	
public:
	enum Levels
	{
		QUIT,
		MAIN,
		LEVEL1
	};
	LevelManager(GameWindow* gameWindow, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo, D3DClass* d3d);
	Level* GetLevel();
	static Levels GetCurrentLevel();
	static void ChangeLevel(Levels level);
	bool ShouldQuit();
private:
	Level* p_Level;
	D3DClass* p_D3D;
	static Levels currentLevel;
	static bool levelChanged;
	static bool quit;
	GameWindow* p_GameWindow;
	DrawingManager* p_DrawingManager;
	AssetManager* p_AssetManager;
	GameInfo* p_GameInfo;
};
