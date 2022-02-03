/*
 * File:			Level.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the class definition for the level class.
 * First Version:	Febuary 10 , 2019
 */

#pragma once

#include "scene.h"
#include "Inputclass.h"
#include "GameObject.h"

/*	
 *	Class	: Level	
 *	Desc	: Models a game level. Base class for levels. 
*/
class Level
{
public:
	Level(GameWindow* gameWindow, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo);
	virtual void DrawLevel() = 0;
	virtual void CheckObjects() = 0;
	virtual void CheckInput(InputClass* input) = 0;
	bool AreRectsColliding(D2D1_RECT_F firstRect, D2D1_RECT_F secondRect);
private:
protected:
	Scene* currentScene;
	DrawingManager* p_DrawingManager;
	AssetManager* p_AssetManager;
	GameWindow* p_game_window;
	GameInfo* p_GameInfo;
};
