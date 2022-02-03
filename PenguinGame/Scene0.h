/*
 * File:			Scene0.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the class definition for Scene0 object.
 * First Version:	Febuary 10, 2019
 */

#pragma once

#include "scene.h"
 /*
  * Class	Scene1
  * Desc:	Models the first scene in the game.
  */
class Scene0 : public Scene
{
public:
	Scene0(Grid* grid, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo);
	void DrawDefaultBackground() override;
	void GenerateSceneAssets() override;
	static const int startCol = 4;
	static const int endCol = 5;
	static const int scoreStartCol = 2;
	static const int scoreEndCol = 7;
	static const int quitRow = 8;
	static const int playRow = 7;
	static const int scoreRow = 5;
	static const int titleRow = 2;

private:

};