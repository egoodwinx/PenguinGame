/*
 * File:			Level0.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A2
 * Description:		Contains the class definition for the level0 class.
 * First Version:	March 22 , 2019
 */

#pragma once

#include "Level.h"
#include "Player.h"
#include <WinUser.h>
#include "D3DClass.h"

/*
*	Class: Level0
*	Desc: Models the first level which is the main menu screen
*/
class Level0 : public Level
{
public:
	Level0(GameWindow* gameWindow, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo, D3DClass* d3d);
	void DrawLevel() override;
	void CheckObjects() override;
	void CheckInput(InputClass* input) override;
private:
	D3DClass* p_D3D;
	Scene* currentScene;
	bool startGame = false;
};