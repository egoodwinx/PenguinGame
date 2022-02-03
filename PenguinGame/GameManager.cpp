  /*
 * File:			GameManager.cpp
 * Programmer:		Emily Goodwin 
 * Project:			GAS A1
 * Description:		Contains methods for the game manager class.
 * First Version:	February 10, 2019
 */

#include "GameManager.h"
#include "Level0.h"

  /*
 * FUNC:	GameManager
 * DESC:	Constructor for GameManager
 * PARAMS:	
 *	GameWindow* gameWindow - the game window
 *	D2DClass* d2d - the d2d class
 * RET:		na
 */
  GameManager::GameManager(GameWindow* gameWindow, D2DClass* d2d, D3DClass* d3d, InputClass* input)
{
	this->p_GameWindow = gameWindow;
	this->p_GameInfo = new GameInfo();
	this->p_D2D = d2d;
	this->p_D3D = d3d;
	this->p_DrawingManager = new DrawingManager(gameWindow, d2d);
	this->p_AssetManager = new AssetManager(d2d, gameWindow);
	this->p_LevelManager = new LevelManager(gameWindow, p_DrawingManager, p_AssetManager, p_GameInfo, p_D3D);
	InitialLoad();
	this->p_CurrentLevel = new Level0(p_GameWindow, p_DrawingManager, p_AssetManager, p_GameInfo, p_D3D);
	this->p_Input = input;
}

/*
 * FUNC:	Frame
 * DESC:	Draws the current levels frame and checks the objects
 * PARAMS:	void
 * RET:		void
 */
void GameManager::Frame()
{
	if(p_LevelManager->ShouldQuit())
	{
		this->Shutdown();
		quit = true;
		return;
	}
	p_D2D->BeginDraw();
	p_LevelManager->GetLevel()->CheckInput(p_Input);
	p_LevelManager->GetLevel()->DrawLevel();
	p_LevelManager->GetLevel()->CheckObjects();
	p_D2D->EndDraw();
	p_D3D->Render();

}

  /*
 * FUNC:	InitialLoad
 * DESC:	Initially load the sprites.
 * PARAMS:	void
 * RET:		void
 */
void GameManager::InitialLoad()
{
	p_AssetManager->LoadSprites();
	p_AssetManager->LoadWaves();
}

/*
* FUNC:	Quit
* DESC:	if we should quit
* PARAMS:	void
* RET:		bool - if we are to quit or not
*/
bool GameManager::Quit()
{
  return  quit;
}

  /*
 * FUNC:	Shutdown
 * DESC:	Deletes the objects
 * PARAMS:	void
 * RET:		void
 */
void GameManager::Shutdown()
{
  if (this->p_GameWindow != NULL)
  {
	  delete this->p_GameWindow;
  }
  if (this->p_AssetManager != NULL)
  {
	  delete this->p_AssetManager;
  }
  if (this->p_CurrentLevel != NULL)
  {
	  delete this->p_CurrentLevel;
  }
  if (this->p_D2D != NULL)
  {
	  p_D2D->Shutdown();
	  delete this->p_D2D;
  }
  if (this->p_D3D != NULL)
  {
	  p_D3D->CleanupDevice();
	  delete this->p_D3D;
  }
  if (this->p_DrawingManager != NULL)
  {
	  delete this->p_DrawingManager;
  }
  if (this->p_LevelManager != NULL)
  {
	  delete this->p_LevelManager;
  }
}
