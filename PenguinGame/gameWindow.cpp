/*
 * File:			GameWindow.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the gamewindow methods.
 * First Version:	Febuary 10, 2019
 */


#include "GameWindow.h"

/*
 * FUNC:	GameWindow
 * DESC:	Constructs the game window using the window handle
 * PARAMS:	HWND winHandle - the window handle 
 * RET:		na
 */
GameWindow::GameWindow(HWND winHandle)
{
	this->winHandle = winHandle;
	UpdateDimensions();
}

/*
 * FUNC:	~GameWindow
 * DESC:	Desconstructor for the the gameWindow
 * PARAMS:	na
 * RET:		na
 */
GameWindow::~GameWindow()
{
}

/*
 * FUNC:	UpdateDimension
 * DESC:	Update the window dimensions
 * PARAMS:	void
 * RET:		void
 */
void GameWindow::UpdateDimensions()
{
	RECT windowRectangle;
	GetClientRect (this->winHandle, &windowRectangle);
	this->width = float(windowRectangle.right) - float(windowRectangle.left + 1);
	this->height = float(windowRectangle.bottom) - float(windowRectangle.top + 1);

	UpdateGrid();
}

/*
 * FUNC:	UpdateGrid
 * DESC:	Update the grid.
 * PARAMS:	void
 * RET:		void
 */
void GameWindow::UpdateGrid()
{
	this->grid.UpdateGrid(this->width, this->height);
}

/*
 * FUNC:	GetGrid
 * DESC:	Get the grid
 * PARAMS:	void
 * RET:		Grid* - the grid
 */
Grid* GameWindow::GetGrid()
{
	return &grid;
}

/*
 * FUNC:	GetWindowHeight
 * DESC:	Get the window height
 * PARAMS:	void
 * RET:		int- the window's height
 */
float GameWindow::GetWindowHeight()
{
	return height;
}

/*
 * FUNC:	GetWindowWidth
 * DESC:	Get the window width
 * PARAMS:	void
 * RET:		int - the window width
 */
float  GameWindow::GetWindowWidth()
{
	return width;
}

/*
 * FUNC:	GetWindowHandle
 * DESC:	Get the window handle
 * PARAMS:	void
 * RET:		HWND - the window handle
 */
HWND GameWindow::GetWindowHandle()
{
	return winHandle;
}
