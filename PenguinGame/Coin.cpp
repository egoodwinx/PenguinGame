/*
 * File:			Coin.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A2
 * Description:		Contains the class methods for the coin class
 * First Version:	March 22, 2019
 */

#include "Coin.h"

 /*
 * Name:	Coin Constructor
 * Desc:	Constructor for Coin class
 * Param:	
 *	Grid::Block - the block that the object is in
 *	Scene* scene - the scene the object is in
 * return:	na
 */
Coin::Coin(Grid::Block block, Scene* scene) : GameObject(scene)
{
	this->SetRectToBlock(block);
}