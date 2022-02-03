/*
 * File:			AssetManager.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the methods for the asset manager
 * First Version:	Febuary 10, 2019
 */


#include "assetManager.h"

/*
 * FUNC:	AssetManager
 * DESC:	constructor for asset manager
 * PARAMS:	
 *	D2DClass* d2d - the d2d class 
 *	GameWindow* gameWindow - the game window
 * RET:		na
 */
AssetManager::AssetManager(D2DClass* d2d, GameWindow* gameWindow)
{
	p_D2DClass = d2d;
	p_GameWindow = gameWindow;
	LoadSprites(); // need to release
};

/*
 * FUNC:	InitializeImageFactory
 * DESC:	Initialize the image factory
 * PARAMS:	void
 * RET:		void
 */
void AssetManager::InitializeImageFactory()
{
	int result = 0;
	result = CoCreateInstance(
		CLSID_WICImagingFactory, //CLS ID of the object about to be made
		NULL, //not needed here, but just denotes this isn't part of an aggregate
		CLSCTX_INPROC_SERVER, //Indicates this DLL runs in the same process
		IID_IWICImagingFactory, //Reference to an Interface that talks to the object
		(LPVOID*)&p_ImageFactory); //This is our pointer to the WICFactory, once set up.
};

/*
 * FUNC:	ReleaseImageFactory
 * DESC:	release the image factory.
 * PARAMS:	void
 * RET:		void
 */
void AssetManager::ReleaseImageFactory()
{
	if (p_ImageFactory != NULL)
	{
		p_ImageFactory->Release();
		p_ImageFactory = NULL;
	}
};

/*
 * FUNC:	LoadSprites
 * DESC:	Load all of the sprites and add effects if necessary.
 * PARAMS:	void
 * RET:		void
 */
void AssetManager::LoadSprites()
{
	InitializeImageFactory();
	LoadSprite(SpriteDef::tree1, tree1File);
	p_D2DClass->ApplyChroma(Sprites.at(SpriteDef::tree1)->p_Bitmap);
	LoadSprite(SpriteDef::tree2, tree2File);
	p_D2DClass->ApplyChroma(Sprites.at(SpriteDef::tree2)->p_Bitmap);
	LoadSprite(SpriteDef::shrub, shrubFile);
	p_D2DClass->ApplyChroma(Sprites.at(SpriteDef::shrub)->p_Bitmap);
	LoadSprite(SpriteDef::penguin, penguinFile);
	p_D2DClass->ApplyChroma(Sprites.at(SpriteDef::penguin)->p_Bitmap);
	LoadSprite(SpriteDef::penguinFlipped, penguinFlippedFile);
	p_D2DClass->ApplyChroma(Sprites.at(SpriteDef::penguinFlipped)->p_Bitmap);
	LoadSprite(SpriteDef::cloud, cloudFile);
	p_D2DClass->ApplyChroma(Sprites.at(SpriteDef::cloud)->p_Bitmap);
	LoadSprite(coin, coinFile);
	p_D2DClass->ApplyChroma(Sprites.at(coin)->p_Bitmap);
	LoadSprite(heart, heartFile);
	p_D2DClass->ApplyChroma(Sprites.at(heart)->p_Bitmap);
	ReleaseImageFactory();
}

/*
* FUNC:		LoadWaves
* DESC:		Load the music/sound effects into the asset manager.
* PARAMS:	void
* RET:		void
*/
void AssetManager::LoadWaves()
{
	CWave* normalWave = new CWave();
	normalWave->Load(normalWaveFile);
	CWave* dangerWave = new CWave();
	dangerWave->Load(dangerWaveFile);
	CWave* lastLifeWave = new CWave();
	lastLifeWave->Load(lastLifeWaveFile);
	CWave* laserWave = new CWave();
	laserWave->Load(laserWaveFile);
	CWave* jumpWave = new CWave();
	jumpWave->Load(jumpWaveFile);
	CWave* coinWave = new CWave();
	coinWave->Load(coinWaveFile);
	Waves.insert(std::pair <WaveDef, CWave*>(WaveDef::normal, normalWave));
	Waves.insert(std::pair <WaveDef, CWave*>(WaveDef::danger, dangerWave));
	Waves.insert(std::pair <WaveDef, CWave*>(WaveDef::oneLife, lastLifeWave));
	Waves.insert(std::pair <WaveDef, CWave*>(WaveDef::coinWave, coinWave));
	Waves.insert(std::pair <WaveDef, CWave*>(WaveDef::laser, laserWave));
	Waves.insert(std::pair <WaveDef, CWave*>(WaveDef::jump, jumpWave));
}

/*
 * FUNC:	LoadSprite
 * DESC:	Load a sprite.
 * PARAMS:	
 *	SpriteDef sprite - sprite enum value
 *	LPCWSTR name - sprite file name
 * RET:		void 
 */
void AssetManager::LoadSprite(SpriteDef sprite, LPCWSTR name)
{
	Grid::Block tmpBlock = (p_GameWindow->GetGrid())->GetBlock(0, 0);
	Sprite* tmp = new Sprite();
	int result = tmp->LoadBitmapFromFile(p_D2DClass->GetRenderTarget(), p_ImageFactory, name, UINT(tmpBlock.width), UINT(tmpBlock.height));
	if (result == 0)
	{
		Sprites.insert(std::pair<SpriteDef, Sprite*>(sprite, tmp));
	}
}