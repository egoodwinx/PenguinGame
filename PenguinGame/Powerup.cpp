/*
 * File:			Powerup
 * Programmer:		Emily Goodwin
 * Project:			GAS A3
 * Description:		Contains methods for Powerup object class.
 * First Version:	Febuary 10, 2019
 */


#include "Powerup.h"

/*
 * FUNC:	Powerup
 * DESC:	Powerup constructor
 * PARAMS:	
 *	Grid::Block block- the block its in
 *	Scene* scene - its scene
 *	Powerup::Type type - the powerup type
 *	Sprite* sprite - its sprite
 * RET:		na
 */
Powerup::Powerup(Grid::Block block, Scene* scene, Powerup::Type type, Sprite* sprite) : GameObject(scene)
{
	SetRectToBlock(block);
	this->type = type;
	SetSprite(sprite);
}

/*
 * FUNC:	GetPowerupType
 * DESC:	Get the powerup type
 * PARAMS:	void
 * RET:		Powerup::Type - the powerup's type
 */
Powerup::Type Powerup::GetPowerupType()
{
	return type;
}
