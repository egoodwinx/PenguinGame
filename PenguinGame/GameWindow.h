/*
 * File:			GameWindow.H
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the class definition for the game window
 * First Version:	Febuary 10, 2019
 */


#ifndef GAME_WINDOW_H_
#define GAME_WINDOW_H_

#include <windows.h>
#include "grid.h"

/*
 * Class	GameWindow 
 * Desc:	Models the game window.
 */
class GameWindow
{
public:
	GameWindow(HWND winHandle);
	~GameWindow();
	float GetWindowHeight();
	float GetWindowWidth();
	void UpdateDimensions();
	Grid* GetGrid();
	HWND GetWindowHandle();
private:
	Grid grid;
	HWND winHandle;
	float height;
	float width;
	void UpdateGrid();
};
#endif