/*
 * File:			GraphicsClass.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains Graphics Class definition. Handles the graphics.
 * http://www.rastertek.com/dx11tut02.html
 * First Version:	February 10, 2019
 */

#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include <windows.h>
#include "D2DClass.h"
#include "GameWindow.h"
#include "GameManager.h"
#include "D3DClass.h"

const bool FULL_SCREEN = false;

/*
 * Class	GraphicsClass
 * Desc:	Handles graphics stuff.
 */
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	D2DClass* GetD2D();
	D3DClass* GetD3D();
	GameWindow* GetGameWindow();

private:

private:
	D2DClass* p_D2D;
	GameWindow* p_GameWindow;
	D3DClass* p_D3D;
};

#endif
