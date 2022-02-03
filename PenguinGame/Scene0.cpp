#include "Scene0.h"

/*
 * FUNC:	Scene0 Constructor
 * DESC:	Scene0 constructor
 * PARAMS: 
 * Grid* grid- the grid
 * DrawingManager* drawingManager - the drawing manager
 * AssetManager* assetManager - the asset manager
 * GameInfo* gameInfo - the game info
 * RET: na
 */
Scene0::Scene0(Grid* grid, DrawingManager* drawingManager, AssetManager* assetManager, GameInfo* gameInfo) : Scene(grid, drawingManager, assetManager, gameInfo)
{
	
}

/*
 * FUNC:	DrawDefaultBackground
 * DESC:	Draw the default background. This is the main menu scene.
 * PARAMS: void
 * RET: void
 */
void Scene0::DrawDefaultBackground()
{
	// background
	p_DrawingManager->DrawRectangle(p_Grid->GetArea(0, 0, 9, 9), D2D1::ColorF::LightBlue);
	// title
	p_DrawingManager->DrawString(p_Grid->GetArea(startCol, titleRow, endCol, titleRow), "Penguin Game", D2D1::ColorF::White, 38);
	//score
	p_DrawingManager->DrawString(p_Grid->GetArea(scoreStartCol, scoreRow, scoreEndCol, scoreRow), "Last Score:" + std::to_string(p_GameInfo->GetLastScore()));
	// play button
	p_DrawingManager->DrawRectangle(p_Grid->GetArea(startCol, playRow, endCol, playRow), D2D1::ColorF::DeepSkyBlue);
	p_DrawingManager->DrawString(p_Grid->GetArea(startCol, playRow, endCol, playRow), "Play");
	// quit button
	p_DrawingManager->DrawRectangle(p_Grid->GetArea(startCol, quitRow, endCol, quitRow), D2D1::ColorF::DeepSkyBlue);
	p_DrawingManager->DrawString(p_Grid->GetArea(startCol, quitRow, endCol, quitRow), "Quit");
}

/*
 * FUNC:	GenerateSceneAssets
 * DESC:	Generate the scene assets, virtual method needs to be overrode
 * PARAMS: void
 * RET: void
 */
void Scene0::GenerateSceneAssets()
{
	
}
