#pragma once
/*
* File:				Powerup.h
* Programmer:		Emily Goodwin
* Project:			GAS A3
* Description:		Contains the powerup class definition.
* First Version:	March 13, 2019
*/

#ifndef POWERUP_H_
#define POWERUP_H_

#include "GameObject.h"

/*
* Class	Powerup
* Desc:	Models the powerup class.
*/
class Powerup : public GameObject
{
public:
	enum Type
	{
		ExtraLife
	};
	Powerup(Grid::Block block, Scene* scene, Powerup::Type type, Sprite* sprite);
	Type GetPowerupType();
private:
	Type type;
};
#endif