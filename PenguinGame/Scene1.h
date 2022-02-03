/*
 * File:			Scene1.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the class definition for Scene1 object.
 * First Version:	Febuary 10, 2019
 */

#pragma once

#include "scene.h"
/*
 * Class	Scene1
 * Desc:	Models the first scene in the game.
 */
class Scene1 : public Scene
{
public:
	Scene1(Grid* grid, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo);
	const enum ROWS
	{
		FIRST_ROW = 0,
		SECOND_ROW,
		THIRD_ROW,
		FOURTH_ROW,
		FIFTH_ROW,
		SIXTH_ROW,
		SEVENTH_ROW,
		EIGHTH_ROW,
		NINETH_ROW,
		TENTH_ROW
	};
	int GetCoinY(int x);
	void RemoveCoin(int x);

private:
	const int CLOUD_AREA = 4;
	const int CLOUD_PERCENT = 20;
	const int PLANT_AREA = 6;
	const int PLANT_PERCENT = 35;
	const int EACH_PLANT_PERCENT = 33;
	const int HOLE_PERCENT = 5;
	const int STAY_SAME_HEIGHT_PERCENT = 50;
	const int CHANGE_HEIGHT_UPDOWN_PERCENT = 50;
	const int GROUND_MAX_Y = 9;
	const int GROUND_MIN_Y = 5;
	const int GROUND_DEFAULT = 8;

	float moveValue = 0;

	virtual void GenerateSceneAssets();
	virtual void DrawDefaultBackground();
	virtual void DrawScene() override;
	void GenerateHillsAndHoles();
	void DrawHillsAndHoles();
	void DrawScoreAndLives();
	void DrawClouds();
	std::map<int, int> coins;
};