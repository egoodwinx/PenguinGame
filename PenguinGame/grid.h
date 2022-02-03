/*
 * File:			Grid.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the class definition for the grid class.
 * First Version:	Febuary 10 ,2019
 */

#pragma once
#ifndef GRID_H_
#define GRID_H_	
#include "common.h"
#include <utility>

/*
 * Class	Grid
 * Desc:	Models the grid for the games window.
 */
class Grid 
{
public:	
	const static int ROWS = 10;
	const static int COLS = 10;
	struct Block
	{
		Coordinate center;
		Coordinate topLeft;
		Coordinate bottomRight;
		float width;
		float height;
		int gridBlocks;
	};
	Grid();
	Grid(float width, float height);
	Block GetRow(int row);
	Block GetColumn(int col);
	static Block GetBlock(int col, int row);
	Block GetArea(int topLeftCol, int bottomLeftRow, int topRightCol, int bottomRightRow);
	void SetWidth(float width);
	void SetHeight(float height);
	void UpdateGrid(float width, float height);
	float GetHeight();
	float GetWidth();
	static std::pair<int, int> GetBlockCoorFromLocation(float x, float y);

private:
	const int HALVE = 2;
	float width = 0;
	float height = 0;
	static float blockWidth;
	static float blockHeight;
};
#endif