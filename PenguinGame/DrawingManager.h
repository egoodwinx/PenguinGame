/*
 * File:			DrawingManager.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the class definition for the drawingmanager
 * First Version:	Febuary 10, 2019
 */

#ifndef DRAWING_MANAGER_H_
#define DRAWING_MANAGER_H_
#include "GameWindow.h"
#include "D2DClass.h"
#include "sprite.h"
#include <string>

/*
 * Class	DrawingManager
 * Desc:	Manages drawing the different assets on the screen.
 */
class DrawingManager
{
public:
	DrawingManager(GameWindow* gameWin, D2DClass* d2d);
	void DrawRectangle(Grid::Block block, D2D1::ColorF colour);
	void DrawRectangle(D2D1_RECT_F rect, D2D1::ColorF colour);
	void DrawSprite(Grid::Block block, Sprite* sprite, float xOffset = 0.0f, float yOffset = 0.0f, float size = 1.0);
	void DrawSprite(D2D1_RECT_F rect, Sprite* sprite, float size = 1.0);
	void DrawString(Grid::Block block, std::string text, D2D1::ColorF colour = D2D1::ColorF::White, int fontSize = 24);
	std::pair<int,int> GetCursorPosition();
private:
	GameWindow* p_GameWindow;
	D2DClass* p_D2D;
};
#endif