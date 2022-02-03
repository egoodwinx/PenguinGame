/*
 * File:			DrawingManager.cpp
 * Programmer:		Emily goodwin
 * Project:			GAS A1
 * Description:		Contains methods for the drawing manager.
 * First Version:	Febuary 10, 2019
 */

#include "DrawingManager.h"
#include "GameWindow.h"
#include "D2DClass.h"

/*
 * FUNC:	DrawingManager
 * DESC:	Constructor for drawing manager.
 * PARAMS:	
 *	GameWindow* gameWindow - the game window
 *	D2DClass d2d - the d2d class
 * RET:		na
 */
DrawingManager::DrawingManager(GameWindow* gameWindow, D2DClass* d2d)
{
	this->p_D2D = d2d;
	this->p_GameWindow = gameWindow;
}

/*
 * FUNC:	DrawRectangle
 * DESC:	Draw the rectangle taking in a block
 * PARAMS:	
 *	Grid::Block block - the block to use to draw as the rectangle.
 *	D2D1::colorF colour - the colour of the rectangle
 * RET:		
 */
void DrawingManager::DrawRectangle(Grid::Block block, D2D1::ColorF colour)
{
	p_D2D->SetBrushColour(colour);
	p_D2D->DrawRectangle(float(block.topLeft.x), float(block.topLeft.y), float(block.bottomRight.x), float(block.bottomRight.y));
}

/*
 * FUNC:	DrawRectangle
 * DESC:	Draw the rectangle taking in a rectangle
 * PARAMS:
 *	D2D1_RECT_F - the rectangle.
 *	D2D1::colorF colour - the colour of the rectangle
 * RET:
 */
void DrawingManager::DrawRectangle(D2D1_RECT_F rect, D2D1::ColorF colour)
{
	p_D2D->SetBrushColour(colour);
	p_D2D->DrawRectangle(float(rect.left), float(rect.top), float(rect.right), float(rect.bottom));
}

/*
 * FUNC:	DrawSprite
 * DESC:	Draw the sprite given in the place.
 * PARAMS:	
 *	Grid::Block block - The block to draw the sprite in.
 *	Sprite* sprite - The sprite to draw
 *	flloat size - the size to draw the sprite at
 * RET:		void
 */
void DrawingManager::DrawSprite(Grid::Block block, Sprite* sprite, float xOffset, float yOffset, float size)
{
	p_D2D->DrawSprite(sprite->p_Bitmap, float(block.topLeft.x) + xOffset, 
										float(block.topLeft.y) + yOffset, 
										float(block.bottomRight.x) + xOffset, 
										float(block.bottomRight.y) + yOffset, size);
}

/*
 * FUNC:	DrawSprite
 * DESC:	Draw the sprite in the given rectangle
 * PARAMS:	
 *	D2D1_RECT_F rectangle - the rectangle to draw it in.
 *	Sprite* sprite - the sprite to draw;
 *	float size - the size to scale the sprite at
 * RET:		void
 */
void DrawingManager::DrawSprite(D2D1_RECT_F rect, Sprite* sprite, float size)
{
	p_D2D->DrawSprite(sprite->p_Bitmap, rect.left, rect.top, rect.right, rect.bottom);
}

/*
 * FUNC:	DrawString
 * DESC:	Draw the string in the given area.
 * PARAMS:
 *	Grid::Block block - the block to colour as the rectangle.
 *	std::string text - the string to write
 *	D2D1::colorF colour - the colour of the text
 *	int fontSize - the size of the string
 * RET:
 */
void DrawingManager::DrawString(Grid::Block block, std::string text, D2D1::ColorF colour, int fontSize)
{
	p_D2D->DrawString(text, block.topLeft.x, block.topLeft.y, block.bottomRight.x, block.bottomRight.y, colour, fontSize);
}

/*
 * FUNC:	GetCursorPosition
 * DESC:	Get the cursor's position relative to the game window
 * PARAMS:  void
 * RET:		pair<int,int> - the coordinates of the cursor's position
 */
std::pair<int, int> DrawingManager::GetCursorPosition()
{
	std::pair<int, int> cursorPos = { 0, 0 };
	POINT p = {0,0};
	if (GetCursorPos(&p))
	{	
		ScreenToClient(p_GameWindow->GetWindowHandle(), &p);
		cursorPos.first = (int)p.x ;
		cursorPos.second = (int)p.y;
	}
	return cursorPos;
}
