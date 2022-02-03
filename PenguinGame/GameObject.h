/*
 * File:			GameObject.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains te class definition for Game Object.
 * First Version:	Febuary 10, 2019
 */

#pragma once
#include "grid.h"
#include "scene.h"
#include "sprite.h"
#include <utility>
#include "DrawingManager.h"
/*
 * Class	GameObject
 * Desc:	Models a game object.
 */
class GameObject
{
public:
	enum Wall
	{
		NONE,
		LEFT,
		RIGHT
	};
	GameObject(Scene* scene);
	void Draw(Grid::Block block, DrawingManager* drawingManager);
	void Draw(DrawingManager* drawingManager);
	void SetRectToBlock(Grid::Block block);
	bool IsOnGround();
	Wall IsHittingGroundWall();
	Coordinate GetCenter();
	D2D1_RECT_F GetRectangle();	
	void SetSprite(Sprite* sprite);
	std::pair<int,int> GetNearestBlockCoor();
	bool IsVisible();
	void Hide();
	void Show();
protected:
	Scene* p_scene;
	D2D1_RECT_F rect;
	std::pair<int, int> initialPosition;
	Sprite* sprite;
	bool isCollidable = false;
	bool isVisible = true;
private:

};
