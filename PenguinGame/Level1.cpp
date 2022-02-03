/*
 * File:			Level1.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A2
 * Description:		Contains the class methods for the level1 class
 * First Version:	March 22, 2019
 */

#include "Level1.h"
#include "Scene1.h"
#include "GameManager.h"

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
Level1::Level1(GameWindow* gameWindow, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo) : Level(gameWindow, drawingManager, assetManager, gameInfo)
{
	this->currentScene = new Scene1(gameWindow->GetGrid(), drawingManager, assetManager, gameInfo);
	this->player = new Player(currentScene, gameWindow);
	this->player->SetSprite(assetManager->Sprites.at(assetManager->penguin), assetManager->Sprites.at(assetManager->penguinFlipped));
	PlaceCoins();
}

/*
* Name:		DrawLevel()
* Desc:		Draw all the assets in the level.
* Param:	void
* return:	void
*/
void Level1::DrawLevel()
{
	currentScene->DrawScene();
	player->Draw(p_DrawingManager);
	for (Coin* coin : coins)
	{
		if (coin->IsVisible())
		{
			coin->Draw(p_DrawingManager);
		}
	}
	if (powerup != NULL)
	{
		powerup->Draw(p_DrawingManager);
	}


	CWave* oldMusic = currentMusic;
	AssetManager::WaveDef oldMusicType = currentMusicType;
	if (p_GameInfo->GetLives() == 1)
	{
		currentMusic = p_AssetManager->Waves.at(AssetManager::WaveDef::oneLife);
		currentMusicType = AssetManager::WaveDef::oneLife;
	}
	else if (currentScene->SceneContainsHoles())
	{
		currentMusic = p_AssetManager->Waves.at(AssetManager::WaveDef::danger);
		currentMusicType = AssetManager::WaveDef::danger;
	}
	else
	{
		currentMusic = p_AssetManager->Waves.at(AssetManager::WaveDef::normal);
		currentMusicType = AssetManager::WaveDef::normal;
	}
	if ((oldMusic != NULL) && (oldMusicType != currentMusicType))
	{
		oldMusic->Stop();
	}
	currentMusic->Play();
}

/*
* Name:		CheckObjects()
* Desc:		Check the game objects statuses
* Param:	void
* return:	void
*/
void Level1::CheckObjects()
{
	int playerNearestBlockX = player->GetNearestBlockCoor().first;
	if ((coins.size() >= (unsigned int)playerNearestBlockX) && ((unsigned int)coins.size() > 0))
	{
		if (AreRectsColliding(player->GetRectangle(), coins[playerNearestBlockX]->GetRectangle()))
		{
			Coin* coin = coins.at(playerNearestBlockX);
			if (coin->IsVisible())
			{
				coin->Hide();
				p_GameInfo->SetScore(p_GameInfo->GetScore() + 100);
				p_AssetManager->Waves.at(AssetManager::WaveDef::coinWave)->Play();
			}
		}
	}
	if (powerup != NULL)
	{
		if (AreRectsColliding(player->GetRectangle(), powerup->GetRectangle()) && (powerup->IsVisible()))
		{
			p_GameInfo->SetLives(p_GameInfo->GetLives() + 1);
			powerup->Hide();
		}
	}
	if (player->GetPlayerOutOfBoundsRightSide())
	{
		player->ResetPosition();
		currentScene = new Scene1(p_game_window->GetGrid(), p_DrawingManager,p_AssetManager, p_GameInfo);
		player->SetScene(currentScene);
		delete powerup;
		powerup = NULL;
		PlacePowerup();
		PlaceCoins();
	}
	// if the player falls lose a life
	if (player->IsObjectOutOfBounds())
	{
		player->ResetPosition();
		p_GameInfo->SetLives(p_GameInfo->GetLives() - 1);
	}
	// if we ran out of lives then go back to title screen and reset game info
	if (p_GameInfo->GetLives() <= 0)
	{
		p_GameInfo->SetLastScore(p_GameInfo->GetScore());
		p_GameInfo->SetLives(p_GameInfo->DEFAULT_LIVES);
		p_GameInfo->SetScore(0);
		LevelManager::ChangeLevel(LevelManager::MAIN);
		currentMusic->Stop();
		delete powerup;
		powerup = NULL;
	}
}

/*
* Name:		CheckInput()
* Desc:		Check the users input to see what buttons are pressed down.
* Param:	InputClass* input - the input manager class
* return:	void
*/
void Level1::CheckInput(InputClass* input)
{
	if (input->IsKeyDown(VK_LEFT))
	{
		player->MoveLeft();
	}
	else if (input->IsKeyDown(VK_RIGHT))
	{
		player->MoveRight();
	}
	if (input->IsKeyDown(VK_UP))
	{
		if (player->Jump())
		{
			p_AssetManager->Waves.at(AssetManager::WaveDef::jump)->Play();
		}
	}
	if (input->IsKeyDown(VK_SPACE))
	{
		if (player->FireLaser())
		{
			p_AssetManager->Waves.at(AssetManager::WaveDef::laser)->Play();
		}
	}
}

/*
* Name:		PlaceCoins
* Desc:		Place the coins above the ground on each block.
* Param:	void
* return:	void
*/
void Level1::PlaceCoins()
{
	coins.clear();
	for (int i = 0; i < Grid::COLS; i++)
	{
		int groundY = currentScene->GetGroundBlockY(i) - 1;
		coins.push_back(new Coin(p_game_window->GetGrid()->GetBlock(i, groundY), currentScene));
		coins[i]->SetSprite(p_AssetManager->Sprites.at(AssetManager::SpriteDef::coin));
	}
}

/*
* Name:		PlacePowerup
* Desc:		Place a powerup in the level
* Param:	void
* return:	void
*/
void Level1::PlacePowerup()
{
	if(currentScene->RandomizeByPercent(25))
	{
		int x =currentScene->GetRandomInt(0, Grid::COLS);
		int y = currentScene->GetGroundBlockY(x) - 2;
		if (powerup != NULL)
		{
			delete powerup;
			powerup = NULL;
		}
		powerup = new Powerup(p_game_window->GetGrid()->GetBlock(x, y), currentScene, Powerup::Type::ExtraLife, (Sprite*)p_AssetManager->Sprites.at(AssetManager::SpriteDef::heart));
	}
}