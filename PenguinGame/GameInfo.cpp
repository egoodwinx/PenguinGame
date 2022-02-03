/*
 * File:			GameInfo.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A2
 * Description:		Contains the class methods for the game info class
 * First Version:	March 22, 2019
 */

#include "GameInfo.h"

 /*
 * FUNC:	GetLives
 * DESC:	get the current lives
 * PARAMS:	void
 * RET:		int - the current lives
 */
int GameInfo::GetLives()
{
	return lives;
}

/*
* FUNC:	GetScore
* DESC:	get the current score
* PARAMS:	void
* RET:		int - the current score
*/
int GameInfo::GetScore()
{
	return score;
}

/*
* FUNC:	SetLives
* DESC:	Set the current lives
* PARAMS:	int newLives - the new lives to set the lives to
* RET:		void
*/
void GameInfo::SetLives(int newLives)
{
	lives = newLives;
}

/*
* FUNC:	SetLastScore
* DESC:	Set the last score
* PARAMS:	int newLastScore- the new last score to set the lastScore to.
* RET:		void
*/
void GameInfo::SetLastScore(int newLastScore)
{
	lastScore = score;
}

/*
* FUNC:	GetLastScore
* DESC:	Get the last score
* PARAMS:	void
* RET:		int - the last score
*/
int GameInfo::GetLastScore()
{
	return lastScore;
}

/*
* FUNC:	SetScore
* DESC:	set the current score
* PARAMS:	int newScore - the new score to set the score to
* RET:		void
*/
void GameInfo::SetScore(int newScore)
{
	score = newScore;
}