#include "Laser.h"

Laser::Laser(Coordinate startingArea, bool isFacingRight, Scene* scene) : MoveableObject(scene)
{
	rect = { startingArea.x - 30, startingArea.y - 10, startingArea.x + 30, startingArea.y +10};
	if (isFacingRight)
	{
		SetXSpeed(20);
	}
	else
	{
		SetXSpeed(-20);
	}
	SetGravityForce(0);
}

bool Laser::IsVisible()
{
	return isVisible;
}

void Laser::Draw(DrawingManager* drawingManager)
{	
	MoveableObject::UpdateRectangle();
	if (isVisible)
	{
			if (IsHittingGroundWall() || IsOnGround())
	{
		isVisible = false;
	}
	drawingManager->DrawRectangle(rect, D2D1::ColorF::Red);
	}
}

bool Laser::IsOffScreen()
{
	bool ret = false;
	if ((rect.left < 0) || (rect.right > p_scene->GetGrid()->GetWidth()))
	{
		ret = true;
	}
	return ret;
}