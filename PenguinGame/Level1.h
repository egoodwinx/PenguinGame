/*
 * File:			Level1.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A2
 * Description:		Contains the class definition for the level1 class.
 * First Version:	March 22, 2019
 */


#pragma once

#include "Level.h"
#include "Player.h"
#include <WinUser.h>
#include "Coin.h"
#include "Powerup.h"

/*
*	Class:	Level1
*	Desc:	Models Level1. Contains actual penguin game play.
*/
class Level1 : public Level
{
public:
	Level1(GameWindow* gameWindow, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo);
	void DrawLevel() override;
	void CheckObjects() override;
	void CheckInput(InputClass* input) override;
	void PlaceCoins();	
	void PlacePowerup();
private:
	Player* player;
	Scene* currentScene;
	std::vector<Coin*> coins;
	Powerup* powerup = NULL;
	CWave* currentMusic = NULL;
	AssetManager::WaveDef currentMusicType = AssetManager::WaveDef::normal;
};