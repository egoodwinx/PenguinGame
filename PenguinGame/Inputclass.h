/*
 * File:			InputClass.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		contains input class definition
 * http://www.rastertek.com/dx11tut02.html
 * First Version:	February 10, 2019
 */

#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_


/*
 * Class	InputClass
 * Desc:	Models input class
 */
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);
	void LeftMouseDown();
	void LeftMouseUp();
	bool IsLeftMouseDown();
	bool IsKeyDown(unsigned int);

private:
	bool m_keys[256];
	bool lMouseButton = false;
};

#endif