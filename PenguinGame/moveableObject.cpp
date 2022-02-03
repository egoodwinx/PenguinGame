/*
 * File:			MoveableObject
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains methods for moveable object class.
 * First Version:	Febuary 10, 2019
 */

#include "MoveableObject.h"

/*
 * FUNC:	MoveableObject
 * DESC:	Constructor for moveable object.
 * PARAMS:	void
 * RET:		na
 */
MoveableObject::MoveableObject(Scene* scene) : GameObject(scene)
{	
	xSpeed = 0;
	ySpeed = 0;
}

/*
 * FUNC:	GenerateObjectSpeed
 * DESC:	Generate the object's speed given the displacement and speed.
 * PARAMS:	
 *	pair<int,int> startPosition - starting coordinates
 *	pair<int,int> endPosition - end coordinates
 *	int seconds - seconds to take for travel
 * RET:		void
 */
void MoveableObject::GenerateObjectSpeed(std::pair<float,float> startPosition, std::pair<float,float>endPosition, int seconds)
{
	// generate xspeed 
	float xDisplacement = endPosition.first - startPosition.first;
	float yDisplacement = endPosition.second - startPosition.second;

	xSpeed = (xDisplacement / seconds)/60;//fps
	ySpeed = (yDisplacement / seconds)/60;
}

/*
 * FUNC:	GetXSpeed
 * DESC:	get x speed
 * PARAMS:	void
 * RET:		int - xspeed
 */
float MoveableObject::GetXSpeed()
{
	return xSpeed;
}

/*
 * FUNC:	GetYSpeed
 * DESC:	get y speed
 * PARAMS:	void
 * RET:		int -y speed
 */
float MoveableObject::GetYSpeed()
{
	return ySpeed;
}

/*
 * FUNC:	SetXSpeed
 * DESC:	sets the x speed
 * PARAMS:	int xSpeedIn - new xspeed
 * RET:		void
 */
void MoveableObject::SetXSpeed(float xSpeedIn)
{
	xSpeed = xSpeedIn;
}

/*
 * FUNC:	SetYSpeed
 * DESC:	sets the y speed
 * PARAMS:	int ySpeedIn - the new y speed in
 * RET:		void
 */
void MoveableObject::SetYSpeed(float ySpeedIn)
{
	ySpeed = ySpeedIn;
}

/*
 * FUNC:	Draw
 * DESC:	Update the position then draw the movable object.
 * PARAMS:	DrawingManager* drawingManager - the drawing manager 
 * RET:		void
 */
void MoveableObject::Draw(DrawingManager* drawingManager)
{
	UpdateRectangle();
	if (sprite != NULL)
	{
		drawingManager->DrawSprite(rect, sprite);
	}
}

/*
 * FUNC:	UpdateRectangle
 * DESC:	update rectangle position based off of the speed.
 * PARAMS:	void
 * RET:		void
 */
void MoveableObject::UpdateRectangle()
{
	Wall hittingWall = IsHittingGroundWall();
	D2D1_RECT_F originalPosition = rect;
	// update friction
	if (IsOnGround())
	{
		// make speed 0 if we're between 0.3 so it wont keep going back and forth
		if ((xSpeed > -0.3f) && (xSpeed < 0.3f))
		{
			xSpeed = 0;
		}
		// add friction to speed so we slow down in either direction
		if (xSpeed < 0)
		{
			xSpeed += xForce + frictionForce;
		}
		else if (xSpeed > 0)
		{
			xSpeed += xForce - frictionForce;
		}
	}
	else
	{
		// if not on ground then there is no friction involved.
		xSpeed += xForce;
	}
	// move the rectangle by the speed
	this->rect.left += xSpeed;
	this->rect.right += xSpeed;

	if ((hittingWall == LEFT) && (xSpeed < 0))
	{
		rect = originalPosition;
		xSpeed = 0;
	}
	else if ((hittingWall == RIGHT) && (xSpeed > 0))
	{
		rect = originalPosition;
		xSpeed = 0;
	}
	
	// if we are not on the ground we need to add gravity.
	if (!IsOnGround())
	{
		ySpeed += yForce;		
		yForce += gravityForce;
	}
	else
	{
		if (yForce > 0)
		{		
			yForce = 0;
			ySpeed = 0;
		}
	}

	// move rectangle by the speed
	this->rect.top += ySpeed;
	this->rect.bottom += ySpeed;
	IsOnGround();
}

/*
 * FUNC:	GetGravityForce
 * DESC:	Get the gravity force of the object.
 * PARAMS:	void
 * RET:		float - the gravity force on the object
 */
float MoveableObject::GetGravityForce()
{
	return gravityForce;
}

/*
 * FUNC:	GetYForce
 * DESC:	Get the y force on the object.
 * PARAMS:	void
 * RET:		float - the y force affecting the object
 */
float MoveableObject::GetYForce()
{
	return yForce;
}

/*
 * FUNC:	IsObjectOutOfBounds
 * DESC:	Is the object out of the screen bounds (only top and bottom right now)
 * PARAMS:	void
 * RET:		bool - is the object out of bounds
 */
bool MoveableObject::IsObjectOutOfBounds()
{
	bool isOutOfBounds = false;
	// if it's too high or too low
	if ((rect.bottom > p_scene->GetGrid()->GetHeight()) ||
		(rect.top < 0))
	{
		isOutOfBounds = true;
	}
	return isOutOfBounds;
}

/*
 * FUNC:	GetXForce
 * DESC:	Get the X force of the object.
 * PARAMS:	void
 * RET:		float - the x force
 */
float MoveableObject::GetXForce()
{
	return xForce;
}

/*
 * FUNC:	SetGravityForce
 * DESC:	Set the gravity force acting on the object.
 * PARAMS:	float newForce - the new gravity force to act on the object
 * RET:		void
 */
void MoveableObject::SetGravityForce(float newForce)
{
	gravityForce = newForce;
}

/*
 * FUNC:	SetXForce
 * DESC:	Set the x force 
 * PARAMS:	float xForceIn - the new x force
 * RET:		void
 */
void MoveableObject::SetXForce(float xForceIn)
{
	xForce = xForceIn;
}


/*
 * FUNC:	SetYForce
 * DESC:	Set the Y force
 * PARAMS:	float yForceIn - the new y force
 * RET:		void
 */
void MoveableObject::SetYForce(float yForceIn)
{
	yForce = yForceIn;
}
