/*
 * File:			MoveableObject.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the class definition for the moveable object class.
 * First Version:	January 10, 2019
 */

#pragma once
#include "GameObject.h"

/*
 * Class	MoveableObject 
 * Desc:	Models a moveable object. Updates the positioning every time its drawn.
 */
class MoveableObject : public GameObject
{
public:
	MoveableObject(Scene* scene);
	void SetYSpeed(float ySpeedIn);
	float GetYSpeed();
	void SetXSpeed(float xSpeedIn);
	float GetXSpeed();
	void GenerateObjectSpeed(std::pair<float,float> startPosition, std::pair <float,float> endPosition, int seconds);
	void Draw(DrawingManager* drawingManager);
	void SetGravityForce(float newForce);
	float GetGravityForce();
	void SetXForce(float xForceIn);
	void SetYForce(float yForceIn);
	float GetXForce();
	float GetYForce();
	bool IsObjectOutOfBounds();
private:
	float gravityForce = 0.3f;
	float frictionForce = 0.1f;
	float xSpeed = 0; //< pixels/second
	float ySpeed = 0; //< pixels/second
	float xForce = 0;
	float yForce = 0;
protected:
	void UpdateRectangle();
};