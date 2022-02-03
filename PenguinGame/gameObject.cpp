/*
 * File:			GameObject.cpp
 * Programmer:		Emily Goodwin
 * Project:			GameObject
 * Description:		Contains the game object methods.
 * First Version:	Febuary 10, 2019
 */

#include "GameObject.h"

/*
 * FUNC:	GameObject 
 * DESC:	Constructs a game object
 * PARAMS:	void
 * RET:		na
 */
GameObject::GameObject(Scene* scene)
{
	rect = D2D1_RECT_F();
	initialPosition = { 0,0 };
	sprite = NULL;	
	this->p_scene = scene;
}

/*
 * FUNC:	Draw
 * DESC:	Draw the game object's sprite or a rectangle.
 * PARAMS:	
 *	Grid::Block - the block to draw it in
 *	DrawingManager* - the drawing manager
 * RET:		void
 */
void GameObject::Draw(Grid::Block block, DrawingManager* drawManager)
{
	if (sprite)
	{
		drawManager->DrawSprite(block, sprite);
	}
	else
	{
		drawManager->DrawRectangle(block, D2D1::ColorF::Black);
	}
}

/*
 * FUNC:	Draw
 * DESC:	Draw the game object's sprite or a rectangle in its respected rectangle.
 * PARAMS:
 *	DrawingManager* - the drawing manager
 * RET:		void
 */
void GameObject::Draw(DrawingManager* drawingManager)
{
	if (isVisible)
	{
		if (sprite)
		{
			drawingManager->DrawSprite(rect, sprite);
		}
		else
		{
			drawingManager->DrawRectangle(rect, D2D1::ColorF::Black);
		}
	}
}

/*
 * FUNC:	SetRectToBlock
 * DESC:	Set the object rectangle to the given block.
 * PARAMS:	
 *	Grid::Block the block to use
 * RET:		void
 */
void GameObject::SetRectToBlock(Grid::Block block)
{
	this->rect = { float(block.topLeft.x), float(block.topLeft.y), float(block.bottomRight.x),float(block.bottomRight.y) };
}

/*
 * FUNC:	IsOnGround
 * DESC:	Is the object on the ground?
 * PARAMS:  void
 * RET:		bool - if it is on the ground
 */
bool GameObject::IsOnGround()
{
	bool isOnGround = true;
	Coordinate center = GetCenter();
	std::pair<int,int> currentBlock = Grid::GetBlockCoorFromLocation(center.x,center.y);
	int groundBlockY = p_scene->GetGroundBlockY(currentBlock.first);
	if (groundBlockY == Scene::NO_GROUND)
	{
		isOnGround = false;
	}
	else
	{
		float groundHeight = Grid::GetBlock(currentBlock.first, groundBlockY).topLeft.y;
		if (rect.bottom < groundHeight)
		{
			isOnGround = false;
		}
		else if (rect.bottom >= groundHeight)
		{
			float yDifference = rect.bottom - groundHeight;
			isOnGround = true;
			if (yDifference > 0.1)
			{
				rect.top -= yDifference;
				rect.bottom -= yDifference;
			}
		}
	}
	return isOnGround;
}

/*
 * FUNC:	IsHittingGroundWall
 * DESC:	is the object hitting the ground's wall (side)
 * PARAMS:  void
 * RET:		GameObject::Wall - which wall its hitting
 */
GameObject::Wall GameObject::IsHittingGroundWall()
{
	Wall isHittingWall = NONE;
	Coordinate center = GetCenter();
	std::pair<int, int> currentBlock = Grid::GetBlockCoorFromLocation(center.x, center.y);
	int leftGroundBlockY = -1;
	int rightGroundBlockY = -1;
	Grid::Block leftBlock;
	if (currentBlock.first != 0)
	{
		leftGroundBlockY = p_scene->GetGroundBlockY(currentBlock.first - 1);
		leftBlock = Grid::GetBlock(currentBlock.first - 1, leftGroundBlockY);
	}
	Grid::Block rightBlock;
	if (currentBlock.first != 9)
	{
		rightGroundBlockY = p_scene->GetGroundBlockY(currentBlock.first + 1);
		rightBlock = Grid::GetBlock(currentBlock.first + 1, rightGroundBlockY);
	}

	if (leftBlock.bottomRight.x >= rect.left)
	{
		if ((leftGroundBlockY != -1) &&
			(leftGroundBlockY != Scene::NO_GROUND) &&
			(leftGroundBlockY <= currentBlock.second))
		{
			isHittingWall = LEFT;
		}
	}
	if (rightBlock.topLeft.x <= rect.right)
	{
		if ((rightGroundBlockY != -1) && 
			(rightGroundBlockY != Scene::NO_GROUND) &&
			(rightGroundBlockY <= currentBlock.second))
		{
			isHittingWall = RIGHT;
		}
	}
	return isHittingWall;
}

/*
 * FUNC:	GetCenter
 * DESC:	Get the object's center based on the rectangle.
 * PARAMS:
 *	Grid::Block - the block to draw it in
 *	DrawingManager* - the drawing manager
 * RET:		void
 */
Coordinate GameObject::GetCenter()
{
	Coordinate coordinate;
	coordinate.x = rect.left + ((rect.right - rect.left) / 2);
	coordinate.y = rect.top + ((rect.bottom - rect.top) / 2);
	return coordinate;
}

/*
 * FUNC:	GetRectangle
 * DESC:	Get the object's rectangle
 * PARAMS:	void
 * RET:		D2D1_RECT_F the rectangle
 */
D2D1_RECT_F GameObject::GetRectangle()
{
	return rect;
}

/*
 * FUNC:	SetSprite
 * DESC:	Set the object sprite.
 * PARAMS:	Sprite* sprite - the new sprite to set the sprite to.
 * RET:		void
 */
void GameObject::SetSprite(Sprite* sprite)
{
	this->sprite = sprite;
}

/*
 * FUNC:	GetNearestBlockCoor
 * DESC:	get the objects current block's coordinates based on which its center is in
 * PARAMS:	void
 * RET:		pair<int,int> - the nearest block's coordinates
 */
std::pair<int,int> GameObject::GetNearestBlockCoor()
{
	return Grid::GetBlockCoorFromLocation(this->GetCenter().x, this->GetCenter().y);
}

/*
* Name:		IsVisible()
* Desc:		Is the object visible
* Param:	void
* return:	bool - if the object is visible or not
*/
bool GameObject::IsVisible()
{
	return isVisible;
}

/*
* Name:		Hide()
* Desc:		change that the object should be hidden.
* Param:	void
* return:	void
*/
void GameObject::Hide()
{
	isVisible = false;
}

/*
* Name:		Show()
* Desc:		change that the object should be visible
* Param:	void
* return:	void
*/
void GameObject::Show()
{
	isVisible = true;
}
