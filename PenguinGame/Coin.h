#pragma once
/*
 * File:			Coin.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A2
 * Description:		Contains the coin class definition.
 * First Version:	March 13, 2019
 */

#ifndef COIN_H_
#define COIN_H_

#include "GameObject.h"

 /*
  * Class	Coin
  * Desc:	Models the coin class. Allows for handling coins.
  */
class Coin : public GameObject
{
public:
	Coin(Grid::Block block, Scene* scene);
private:
};
#endif