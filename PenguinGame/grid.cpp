/*
 * File:			grid.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		contains grid methods
 * First Version:	February 10, 2019
 */

#include "grid.h"
#include "common.h"
#include <chrono>
float Grid::blockWidth = 0;
float Grid::blockHeight = 0;

/*
 * FUNC:	Grid
 * DESC:	grid constructor
 * PARAMS:	void
 * RET:		na
 */
Grid::Grid()
{	
}
/*
 * FUNC:	Grid
 * DESC:	Construtor that takes in grid width and height
 * PARAMS:	
 * int width - the width
 * int height - the height
 * RET:		na
 */

Grid::Grid(float width, float height)
{
	UpdateGrid(width, height);
}

/*
 * FUNC:	GetBlock
 * DESC:	Get the block asked for
 * PARAMS:	int row - the row number
 * int col - the column number
 * RET:		Grid::Block the block coordinates
 */
Grid::Block Grid::GetBlock(int col, int row)
{
	Block block;

	block.topLeft = Coordinate(blockWidth * col, blockHeight * row);
	block.bottomRight = Coordinate(blockWidth * (col + 1), blockHeight * (row + 1));
	block.center = Coordinate(block.bottomRight.x/2, block.bottomRight.y/2);
	block.width = block.bottomRight.x - block.topLeft.x;
	block.height = block.bottomRight.y - block.topLeft.y;
	block.gridBlocks = row * col;

	return block;
}

/*
 * FUNC:	GetRow
 * DESC:	Get the rowasked for
 * PARAMS:	int row - the row number
 * RET:		Grid::Block the row coordinates
 */
Grid::Block Grid::GetRow(int row)
{
	Block block;
	
	block.topLeft = Coordinate(0,this->blockHeight * row);
	block.bottomRight = Coordinate(width, this->blockHeight * (row+1));
	block.center = Coordinate(block.bottomRight.x/HALVE, block.bottomRight.y/HALVE);
	block.width = block.bottomRight.x - block.topLeft.x;
	block.height = block.bottomRight.y - block.topLeft.y;
	block.gridBlocks = this->COLS;

	return block;
}

/*
 * FUNC:	GetColumn
 * DESC:	Get the column asked for
 * PARAMS:	int col - the column number
 * RET:		Grid::Block the column coordinates
 */
Grid::Block Grid::GetColumn(int col)
{
	Block block;

	block.topLeft = Coordinate(col * this->blockWidth, 0);
	block.bottomRight = Coordinate((col + 1) * this->blockWidth, 0);
	block.center = Coordinate(ceil(block.bottomRight.x / HALVE), ceil(block.bottomRight.y / HALVE));
	block.width = block.bottomRight.x - block.topLeft.x;
	block.height = block.bottomRight.y - block.topLeft.y;
	block.gridBlocks = this->ROWS;

	return block;
}

/*
 * FUNC:	SetWidth
 * DESC:	set the width
 * PARAMS:	int width - new value to 
 * RET:		void
 */
void Grid::SetWidth(float width)
{
	if (width >= 0)
	{
		this->width = width;
	}
}

/*
 * FUNC:	SetHeight
 * DESC:	set grid height to given height
 * PARAMS:	
 *	int height
 * RET:		void
 */
void Grid::SetHeight(float height)
{
	if (height >= 0)
	{
		this->height = height;
	}
}

/*
 * FUNC:	UpgradeGrid
 * DESC:	Ugrade the grid with the new width and height
 * PARAMS:	 
 *	int Width - the grid width
 *	int Height - the grid height
 * RET:		void
 */
void Grid::UpdateGrid(float width, float height)
{
	if ((width >= 0) && (height >= 0))
	{
		this->width = width + 1;
		this->height = height + 1;
		this->blockWidth =  ceil(float(width) / float(COLS));
		this->blockHeight = ceil(float(height) / float(ROWS));
	}
}

/*
 * FUNC:	GetHeight
 * DESC:	get grid height 
 * PARAMS: void
 * RET:		float - height
 */
float Grid::GetHeight()
{
	return height;
}

/*
 * FUNC:	GetWidth
 * DESC:	Get the width
 * PARAMS:	void
 * RET:		float - width
 */
float Grid::GetWidth()
{
	return width;
}

/*
 * FUNC:	GetArea
 * DESC:	Get an area made out of blocks with the given values. Will use the largest area made of of blocks, ie left values of the left blocks and the right values of the right block.
 * PARAMS:	
 *	int topLeftCol - the top left column block
 *	int bottomLeftRow - the bottom left row block
 *	int topRightCol - the top right column block
 *	int bottomRightRow - the bottom right row block.
 * RET:		Grid::Block - the area that was gotten
 */
Grid::Block Grid::GetArea(int topLeftCol, int bottomLeftRow, int topRightCol, int bottomRightRow)
{
	Block block;

	block.topLeft = GetBlock(topLeftCol, bottomLeftRow).topLeft;
	block.bottomRight = GetBlock(topRightCol, bottomRightRow).bottomRight;
	block.center.x = block.bottomRight.x - block.topLeft.x;
	block.center.y = block.bottomRight.y - block.topLeft.y;
	block.width = block.bottomRight.x - block.topLeft.x;
	block.height = block.bottomRight.y - block.topLeft.y;

	return block;
}

/*
 * FUNC:	GetBlockCoorFromLocation
 * DESC:	Get the block cooridnates from the given x,y location ( using the window coordinates)
 * PARAMS:	float x - the x position
 *	float y - the y position
 * RET:		pair<int,int> - the block coordinates in the grid 
 */
std::pair<int,int> Grid::GetBlockCoorFromLocation(float x, float y)
{
	std::pair<int,int> position = {0,0};

	if (blockWidth != 0)
	{
		position.first = int(ceil(x / blockWidth) - 1);
	}
	if (blockHeight != 0)
	{
		position.second = int(ceil(y / blockHeight) - 1);
	}

	return position;
}
