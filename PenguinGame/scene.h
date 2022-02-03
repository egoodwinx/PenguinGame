/*
 * File:			scene.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the class definition for Scene class.
 * First Version:	February 10, 2019
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "grid.h"
#include "DrawingManager.h"
#include "AssetManager.h"
#include <random>
#include "GameInfo.h"

typedef std::mt19937 RandomNumber;

/*
 * Class	Scene
 * Desc:	Models a scene
 */
class Scene
{
public:
	static const int NO_GROUND = 0;
	const int GROUND_NOT_SET = -1;
	Scene(Grid* grid, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo);
	Grid* GetGrid();
	virtual void DrawScene();
	int GetGroundBlockY(int x);
	bool IsCursorOverArea(Grid::Block area);
	bool SceneContainsHoles();
	bool RandomizeByPercent(unsigned int percent);
	int GetRandomInt(int min, int max);
private:	
	RandomNumber rngEngine;
protected:
	virtual void GenerateSceneAssets() = 0;
	virtual void DrawDefaultBackground() = 0;	
	std::vector<std::pair < Sprite*, std::pair<int, int>>> sceneAssets;
	std::vector<std::pair<Sprite*, std::pair<int, int>>> clouds;
	AssetManager* p_AssetManager;
	DrawingManager* p_DrawingManager;
	GameInfo* p_GameInfo;
	Grid* p_Grid;
	void DrawDefaultBackgroundAssets();
	std::map<int, int> ground;
	bool containsHoles = false;

};

#endif