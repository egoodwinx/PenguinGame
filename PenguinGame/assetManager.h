/*
 * File:			AssetManager.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the class definition for the assetmanager class.
 * First Version:	February 10, 2019
 */

#pragma once
#ifndef ASSET_MANAGER_H_
#define ASSET_MANAGER_H_

#pragma comment(lib, "windowscodecs.lib")
#include <wincodec.h>
#include <map>
#include <string>
#include "sprite.h"
#include "D2DClass.h"
#include "GameWindow.h"
#include "grid.h"
#include "Wave.h"

/*
 * Class	AssetManager
 * Desc:	Manages the assets.
 */
class AssetManager
{
public:
	AssetManager(D2DClass* d2d, GameWindow* gameWindow);
	enum SpriteDef
	{
		tree1,
		tree2,
		shrub,
		penguin,
		cloud,
		coin,
		heart,
		penguinFlipped
	};
	enum WaveDef
	{
		normal,
		danger,
		oneLife,
		coinWave,
		jump,
		laser
	};
	std::map<SpriteDef, Sprite*> Sprites;
	std::map<WaveDef, CWave*> Waves;
	void LoadSprites();
	void LoadWaves();

private:
	LPCWSTR tree1File = L".\\img\\tree1.bmp";
	LPCWSTR tree2File = L".\\img\\tree2.bmp";
	LPCWSTR shrubFile = L".\\img\\shrub1.bmp";
	LPCWSTR penguinFile = L".\\img\\penguin.bmp";
	LPCWSTR penguinFlippedFile = L".\\img\\penguinFlipped.bmp";
	LPCWSTR cloudFile = L".\\img\\cloud.bmp";
	LPCWSTR coinFile = L".\\img\\coin.bmp";
	LPCWSTR heartFile = L".\\img\\heart.bmp";
	LPCWSTR normalWaveFile = L".\\music\\normal.wav";
	LPCWSTR dangerWaveFile = L".\\music\\danger.wav";
	LPCWSTR lastLifeWaveFile = L".\\music\\lastLife.wav";
	LPCWSTR coinWaveFile = L".\\music\\coin.wav";
	LPCWSTR jumpWaveFile = L".\\music\\jump.wav";
	LPCWSTR laserWaveFile = L".\\music\\laser.wav";

	GameWindow* p_GameWindow;
	D2DClass* p_D2DClass;

	IWICImagingFactory* p_ImageFactory;
	void InitializeImageFactory();
	void ReleaseImageFactory();
	void LoadSprite(SpriteDef sprite, LPCWSTR name);
};

#endif