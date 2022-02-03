/*
 * File:			common.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains coordinate struct definition
 * First Version:	February 10, 2019
 */

#ifndef COMMON_H_
#define COMMON_H_

// models a coordinate
struct Coordinate
{
public:
	float x = 0;
	float y = 0;
/*
 * FUNC:	Coordinate()
 * DESC:	Default Constructor 
 * PARAMS:	void
 * RET:		na
 */
	Coordinate()
	{
		x = 0;
		y = 0;
	}
/*
 * FUNC:	Coordinate
 * DESC:	coordinate set with values
 * PARAMS:	
 *	int xIn - the x coor
 *	int yIn -  the y coor
 * RET:		
 */
	Coordinate(float xIn, float yIn)
	{
		x = xIn;
		y = yIn;
	}
/*
 * FUNC:	~Coordinate()
 * DESC:	default desctructor
 * PARAMS:	na
 * RET:		na
 */
	~Coordinate() = default;
/*
 * FUNC:	Operator=
 * DESC:	equal to overloaded function
 * PARAMS:	
 * const Coordinate& newCoordinate - the new coordinate to use.
 * RET:		Coordinate& - the updated cooridnate object
 */
	Coordinate& operator =(const Coordinate& newCoordinate)
	{
		this->x = newCoordinate.x;
		this->y = newCoordinate.y;

		return *this;
	}
};

#endif