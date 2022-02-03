/*
 * File:			main.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		This project contains the code for a 'game' where the background is 
 *					randomly generated while a sprite moves across the screen. When the sprite
 *					reaches the end it creates a new randomly generated background and continues moving.
 * First Version:	February 10, 2019
 */

#include "systemclass.h"

// main 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;

	// Create the system object.
	System = new SystemClass;
	if (!System)
	{
		return 0;
	}

	// Initialize and run the system object.
	result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	// Shutdown and release the system object.
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}