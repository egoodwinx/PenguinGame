/*
* File:			inputclass.cpp
* Programmer:	Emily Goodwin
* Description:	Contains the methods for input class.
* First Version: February 8th
* http://www.rastertek.com/dx11s2tut02.html
*/
#include "inputclass.h"

/*
* Name:		InputClass Constructor
* Desc:		Constructor
* Param:	void
* return:	na
*/
InputClass::InputClass()
{
}

/*
* Name:		InputClass
* Desc:		Constructor that takes in an InputClass
* Param:	
*	const InputClass& other: the input class to use to take in
* return:	na
*/
InputClass::InputClass(const InputClass& other)
{
}

/*
* Name:		~InputClass
* Desc:		The destructor
* Param:	na
* return:	na
*/
InputClass::~InputClass()
{
}

/*
* Name:		Initialize
* Desc:		Initialize the 
* Param:	inputclass
* return:	void
*/
void InputClass::Initialize()
{
	int i;


	// Initialize all the keys to being released and not pressed.
	for (i = 0; i<256; i++)
	{
		m_keys[i] = false;
	}

	return;
}

/*
* Name:		KeyDown
* Desc:		Called when a key is pressed dodwn to update its status
* Param:	unsigned int input - The key that was pressed down
* return:	void
*/
void InputClass::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;
	return;
}

/*
* Name:		KeyUp
* Desc:		Called when a key is released to update its status.
* Param:	unsigned int input - the key that was released.
* return:	void 
*/
void InputClass::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	m_keys[input] = false;
	return;
}

/*
* Name:		LeftMouseDown
* Desc:		Called when the left mouse button is pressed down
* Param:	void
* return:	void
*/
void InputClass::LeftMouseDown()
{
	lMouseButton = true;
}

/*
* Name:		LeftMouseUp
* Desc:		Called when the left mouse button is released
* Param:	void
* return:	void
*/
void InputClass::LeftMouseUp()
{
	lMouseButton = false;
}

/*
* Name:		IsLeftMouseDown
* Desc:		Is the left mouse button down?
* Param:	void
* return:	bool - is the button down
*/
bool InputClass::IsLeftMouseDown()
{
	return lMouseButton;
}

/*
* Name:		IsKeyDown
* Desc:		Returns if the key is pressed down.
* Param:	unsigned int key - the key to query if it's pressed down
* return:	bool - is they key down
*/
bool InputClass::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return m_keys[key];
}
