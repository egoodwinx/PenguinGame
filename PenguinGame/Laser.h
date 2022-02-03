#pragma once
/*
 * File:			Laser.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A2
 * Description:		Contains the laser class definition.
 * First Version:	April 8, 2019
 */

#ifndef LASER_H_
#define LASER_H_

#include "MoveableObject.h"

 /*
  * Class	Coin
  * Desc:	Models the coin class. Allows for handling coins.
  */
class Laser : public MoveableObject
{
public:
	Laser(Coordinate startingCoor, bool isFacingRight, Scene* scene);
	bool IsVisible();
	void Draw(DrawingManager* drawingManager);
	bool IsOffScreen();
private:
	bool isVisible = true;
};
#endif