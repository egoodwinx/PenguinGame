/*
 * File:			Player.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the Player methods.
 * First Version:	January 10, 2019
 */

#include "Player.h"
#include "Laser.h"

/*
 * FUNC:	Player constructor
 * DESC:	Constructs a player object with a game window.
 * PARAMS:	GameWindow* gameWindow - The game window.
 * RET:		na
 */
Player::Player(Scene* scene, GameWindow* gameWindow) : MoveableObject(scene)
{
	p_GameWindow = gameWindow;
	int yStart = scene->GetGroundBlockY(0)-1;
	startingBlock = gameWindow->GetGrid()->GetBlock(0,yStart);
	endingBlock = gameWindow->GetGrid()->GetBlock(gameWindow->GetGrid()->COLS - 1, yStart);
	SetRectToBlock(startingBlock);
	std::pair<float, float> startCoor ={ startingBlock.topLeft.x, startingBlock.topLeft.y};
	std::pair<float, float> endCoor = { endingBlock.bottomRight.x, endingBlock.topLeft.y };
	this->isCollidable = true;
}

/*
 * FUNC:	Draw
 * DESC:	Draw the player object. Check if it is past the right side.
 * PARAMS:	DrawingManager* drawingManager - the drawing manager.
 * RET:		void
 */
void Player::Draw(DrawingManager* drawingManager)
{
	// player moved to next area
	if (directionChanged)
	{
		if (spriteFlipped != NULL)
		{
			Sprite* tmp = sprite;
			this->sprite = spriteFlipped;
			this->spriteFlipped = tmp;
		}
		directionChanged = false;
	}
	if (this->rect.right >= p_GameWindow->GetWindowWidth())
	{
		playerOutOfBoundsRight = true;
	}
	// player cant go father than start
	else if (this->rect.left <= 0)
	{
		if (GetXSpeed() < 0)
		{
			SetXSpeed(0);
		}
	}
	if (laser != NULL)
	{
		laser->Draw(drawingManager);
	}
	MoveableObject::Draw(drawingManager);
}

/*
 * FUNC:	ResetPosition
 * DESC:	Reset the player position to the initial position.
 * PARAMS:	void
 * RET:		void
 */
void Player::ResetPosition()
{
	this->SetRectToBlock(startingBlock);
	playerOutOfBoundsRight = false;
}

/*
 * FUNC:	GetPlayerOutOfBoundsRightSide
 * DESC:	Get if the player is out of bounds on the right side.
 * PARAMS:	void
 * RET:		bool - the player out of bounds right side state
 */
bool Player::GetPlayerOutOfBoundsRightSide()
{
	return playerOutOfBoundsRight;
}

/*
 * FUNC:	MoveLeft
 * DESC:	Move the player to the left.
 * PARAMS:	void
 * RET:		void
 */
void Player::MoveLeft()
{
	if (GetXSpeed() > -MAX_VELOCITY)
	{
		this->SetXSpeed(GetXSpeed() - ACCELERATION);
		if (isFacingRight)
		{
			isFacingRight = false;
			directionChanged = true;
		}
	}
}

/*
 * FUNC:	MoveRight
 * DESC:	Move the player to the right.
 * PARAMS:	void
 * RET:		void
 */
void Player::MoveRight()
{
	if (GetXSpeed() < MAX_VELOCITY)
	{
		this->SetXSpeed(GetXSpeed() + ACCELERATION);
		if (!isFacingRight)
		{
			isFacingRight = true;
			directionChanged = true;
		}
	}
}

/*
 * FUNC:	Jump
 * DESC:	Have the player jump
 * PARAMS:	void
 * RET:		bool - did the player jump
 */
bool Player::Jump()
{
	bool ret = false;
	if (IsOnGround())
	{
		// reset y force and speed
		this->SetYForce(0);
		this->SetYSpeed(0);

		this->SetYSpeed(GetYSpeed() + IMPULSE_JUMP_FORCE);
		this->SetYForce(UPWARDS_ACCELERATION);
		ret = true;
	}
	return ret;
}

/*
 * FUNC:	SetScene
 * DESC:	Set the player's current scene
 * PARAMS:	void
 * RET:		void
 */
void Player::SetScene(Scene* scene)
{
	this->p_scene = scene;
}

/*
 * FUNC:	SetSprite
 * DESC:	Set the player sprite and the flipped sprite
 * PARAMS:	
 *	Sprite* sprite - sprite to set the player sprite to
 *	Sprite* flipped - flipped sprite to save to player
 * RET:		void
 */
void Player::SetSprite(Sprite* sprite, Sprite* flipped)
{
	this->sprite = sprite;
	this->spriteFlipped = flipped;
}

/*
 * FUNC:	FireLaser
 * DESC:	Create a laser object to fire. Will be drawn in player draw method.
 * PARAMS:	void
 * RET:		bool - was it fired?
 */
bool Player::FireLaser()
{
	bool ret = false;
	if (laser == NULL)
	{
		laser = new Laser(GetCenter(), isFacingRight, p_scene);
		ret = true;
	}
	else
	{
		if ((laser->IsOffScreen()) || (!laser->IsVisible()))
		{
			delete laser;
			laser = NULL;
		}
	}
	return ret;
}
