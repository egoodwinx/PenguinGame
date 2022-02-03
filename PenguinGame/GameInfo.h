/*
 * File:			GameInfo.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A2
 * Description:		Contains the class definition for the game information class
 * First Version:	March 22, 2019
 */

#pragma once

 /*
  * Class: GameInfo
  * Desc:	Models the game information.
  */
class GameInfo
{
public:
	const int DEFAULT_LIVES = 3;
	int GetScore();
	int GetLives();
	void SetScore(int newScore);
	void SetLives(int newLives);
	void SetLastScore(int newLastScore);
	int GetLastScore();
private:
	int score = 0;
	int lives = 3;
	int lastScore = 0;
};