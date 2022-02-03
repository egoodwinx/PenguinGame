/*
 * File:			Player.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the Player class definition.
 * First Version:	January 10, 2019
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "MoveableObject.h"
#include <list>
#include "Laser.h"

/*
 * Class	Player
 * Desc:	Models the player class. Allows for controlling the player.
 */
class Player : public MoveableObject
{
public:
	Player(Scene* scene, GameWindow* gameWindow);
	void Draw(DrawingManager* drawingManager);
	void ResetPosition();
	bool GetPlayerOutOfBoundsRightSide();
	void MoveLeft();
	void MoveRight();
	bool Jump();
	bool FireLaser();
	void SetScene(Scene* scene);
	void SetSprite(Sprite* sprite, Sprite* flipped);
private:
	const float MAX_VELOCITY = 7.0;
	const float ACCELERATION = 0.5;
	const float IMPULSE_JUMP_FORCE = -9.0;
	const float UPWARDS_ACCELERATION = -1.5;
	GameWindow* p_GameWindow;
	Grid::Block startingBlock;
	Grid::Block endingBlock;
	bool playerOutOfBoundsRight;
	bool isFacingRight = true;
	bool directionChanged = false;
	bool canFire = true;
	Laser* laser = NULL;
	Sprite* spriteFlipped = NULL;
};
#endif