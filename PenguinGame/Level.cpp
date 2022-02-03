/*
 * File:			Level.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains level methods.
 * First Version:	Febuary 10, 2019
 */

#include "Level.h"

/*
 * Name		:	Level	
 * Desc		:	Constructor for the Level class.
 * Params	:	
 *	GameWindow*	gameWindow		The game window.
 *	DrawingManager*	drawingManager	The drawing manager.
 *	AssetManager*	assetManager	The asset manager
 *	LevelManager*	sceneManager	The scene manager.
 * Return	:	
 */
Level::Level(GameWindow* gameWindow, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo)
{
	this->p_DrawingManager = drawingManager;
	this->p_AssetManager = assetManager;
	this->p_game_window = gameWindow;
	this->p_GameInfo = gameInfo;
	currentScene = NULL;
}

/*
 * Name		:	AreRectsColliding
 * Desc		:	Are the rectangles colliding?
 * Params	:	D2D1_RECT_F - the first rectangle
 *	D2D1_RECT_F - the second rectangle
 * Return	:	if they are colliding or not
 */
bool Level::AreRectsColliding(D2D1_RECT_F firstRect, D2D1_RECT_F secondRect)
{
	bool ret = false;
	if((firstRect.left < secondRect.right) &&
		(firstRect.right > secondRect.left) && 
		(firstRect.top < secondRect.bottom) &&
		(firstRect.bottom > secondRect.top))
	{
		ret = true;
	}
	return ret;
}
