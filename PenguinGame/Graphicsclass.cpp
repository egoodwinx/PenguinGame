/*
 * File:			GraphicsClass.cpp
 * Programmer:		Emily Goodwin	
 * Project:			GAS A1
 * Description:		Contains the graphics class methods
 *  http://www.rastertek.com/dx11s2tut02.html
 * First Version:	February 10 ,2019
 */

#include "GraphicsClass.h"

/*
 * FUNC:	GraphicsClass
 * DESC:	constractor
 * PARAMS:	void
 * RET:		na
 */
GraphicsClass::GraphicsClass()
{
	p_D2D = 0;
	p_GameWindow = 0;
	p_D3D = 0;
}


/*
 * FUNC:	~graphicsclass
 * DESC:	destructor
 * PARAMS:	na
 * RET:		na
 */
GraphicsClass::~GraphicsClass()
{
}

/*
 * FUNC:	Initailize
 * DESC:	initialize the class
 * PARAMS:	
 *	int screenWidth - screen width
 *	int screenHeight - screen height
 *	HWND hwn - window handle
 * RET: bool if it was successful or not		
 */
bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	// create direct2d object
	p_D2D = new D2DClass;
	if (!p_D2D)
	{
		return false;
	}
	result = p_D2D->Initialize(screenWidth, screenHeight, hwnd, FULL_SCREEN);
	if (!result)
	{
		MessageBox(hwnd, L"Could Not initialize DirectX", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	p_D3D = new D3DClass;
	if (!p_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	HINSTANCE hinstance = GetModuleHandle(NULL);
	result = p_D3D->InitWindow(hinstance, 1, hwnd);
	if (result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}
	p_D3D->InitDevice();

	p_GameWindow = new GameWindow(hwnd);
	if (!p_GameWindow)
	{
		return false;
	}

	return true;
}

/*
 * FUNC:	Shutdown
 * DESC:	shut down the class
 * PARAMS:	void
 * RET:		void
 */
void GraphicsClass::Shutdown()
{
	if (p_D2D)
	{
		p_D2D->Shutdown();
		delete p_D2D;
		p_D2D = 0;
	}
	return;
}


/*
* FUNC:	GetD2D
* DESC:	 Get the D2D class
* PARAMS:	void
* RET:		D2DClass* - the d2d class
*/
D2DClass* GraphicsClass::GetD2D()
{
	return p_D2D;
}


/*
* FUNC:	GetD3D
* DESC: Get the d3d class
* PARAMS:	void
* RET:		D3DClass* - the d3d class
*/
D3DClass* GraphicsClass::GetD3D()
{
	return p_D3D;
}


/*
* FUNC:	GetGameWindow
* DESC:	get the game window
* PARAMS:	void
* RET:		GameWindow* - the game window
*/
GameWindow* GraphicsClass::GetGameWindow()
{
	return p_GameWindow;
}