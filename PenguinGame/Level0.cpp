/*
 * File:			Level0.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the level 0 class definition. 
 * First Version:	March 22, 2019
 */

#include "Level0.h"
#include "Scene0.h"
#include "Level1.h"
#include "LevelManager.h"

/*
* Name:		Level1 Constructor
* Desc:		Constructs the Level1 Object.
* Param:
*	GameWindow* gameWindow	:	The game window.
*	DrawingManager*			:	The drawing manager.
*	AssetManager*			:	The asset manager.
*	LevelManager*			:	The scene manager.
* return:
*	nothing
*/
Level0::Level0(GameWindow* gameWindow, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo, D3DClass* d3d) : Level(gameWindow, drawingManager, assetManager, gameInfo)
{
	this->currentScene = new Scene0(gameWindow->GetGrid(), drawingManager, assetManager, gameInfo);
	p_D3D = d3d;
	p_D3D->ShowChildWindow();
}

/*
* Name:		DrawLevel()
* Desc:		Draw all the assets in the level.
* Param:	void
* return:	void
*/
void Level0::DrawLevel()
{
	currentScene->DrawScene();
	p_D3D->Render();
	p_AssetManager->Waves.at(AssetManager::WaveDef::normal)->Play();
}

/*
* Name:		CheckObjects()
* Desc:		Check the object in the level
* Param:	void
* return:	void
*/
void Level0::CheckObjects()
{
	
}

/*
* Name:		CheckInput()
* Desc:		Check the users input
* Param:	void
* return:	void
*/
void Level0::CheckInput(InputClass* input)
{
	if (input->IsLeftMouseDown())
	{
		if (currentScene->IsCursorOverArea(p_game_window->GetGrid()->GetArea(Scene0::startCol, Scene0::playRow, Scene0::endCol, Scene0::playRow)))
		{
			p_D3D->HideChildWindow();
			p_AssetManager->Waves.at(AssetManager::WaveDef::normal)->Stop();
			LevelManager::ChangeLevel(LevelManager::LEVEL1);
			input->LeftMouseUp();
		}
		if (currentScene->IsCursorOverArea(p_game_window->GetGrid()->GetArea(Scene0::startCol, Scene0::quitRow, Scene0::endCol, Scene0::quitRow)))
		{
			LevelManager::ChangeLevel(LevelManager::QUIT);
			input->LeftMouseUp();
		}
		input->LeftMouseUp();
	}
	if (input->IsKeyDown(VK_SPACE))
	{
		p_D3D->HideChildWindow();
		p_AssetManager->Waves.at(AssetManager::WaveDef::normal)->Stop();
		LevelManager::ChangeLevel(LevelManager::LEVEL1);
		input->KeyUp(VK_SPACE);
	}
	if (input->IsKeyDown(VK_ESCAPE))
	{
		LevelManager::ChangeLevel(LevelManager::QUIT);
	}
}

