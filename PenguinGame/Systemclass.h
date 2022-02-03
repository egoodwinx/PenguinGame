#pragma once
/*
 * File:			SystemClass.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		contains system class definition
 * http://www.rastertek.com/dx11tut02.html
 * First Version:	February 10, 2019
 */

#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "inputclass.h"
#include "graphicsclass.h"	

/*
 * Class	SystemClass
 * Desc:	Models system.
 */
class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);	
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input;
	GraphicsClass* m_Graphics;
	GameManager* m_GameManager;
};
static SystemClass* ApplicationHandle = 0;
#endif