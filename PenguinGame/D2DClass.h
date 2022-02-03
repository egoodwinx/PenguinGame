/*
 * File:			D2DClass.h
 * Programmer:		EmilyGoodwin
 * Project:			GAS A1
 * Description:		Contains D2D class definitions. D2d class handles d2d stuff.
 * First Version:	February 10, 2019
 */

#ifndef _D2DCLASS_H_
#define _D2DCLASS_H_

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxguid.lib")

#include <Windows.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <d2d1effects_2.h>
#include <d2d1effecthelpers.h>
#include <string>
#include <dwrite.h>
#include <wincodec.h>
#pragma comment(lib, "Dwrite")


/*
 * Class	D2DClass
 * Desc:	Models the d2d class. Handles all d2d things.
 */
class D2DClass
{
public:
	D2DClass();
	D2DClass(const D2DClass&);
	~D2DClass();

	bool Initialize(int screenHeight, int screenWidth, HWND hwnd, bool fullscreen);
	void Shutdown();
	
	void BeginDraw() { m_rendertarget->BeginDraw(); }
	void EndDraw() { m_rendertarget->EndDraw(); }
	void SetBrushColour(float r, float g, float b, float a);
	void SetBrushColour(D2D1::ColorF colour);
	void DrawRectangle(float x, float y, float width, float height);
	void DrawSprite(ID2D1Bitmap* sprite, float topX, float topY, float botX, float botY, float scale = 1.0);
	ID2D1HwndRenderTarget* GetRenderTarget();
	void ApplyChroma(ID2D1Bitmap*& sprite);
	void ClearScreen(float r, float g, float b);
	void D2DClass::DrawString(std::string string, float topX, float topY, float botX, float botY, D2D1::ColorF colour = D2D1::ColorF::White, int fontSize = 32);
	void SetTextFormat(int fontSize);
private:
	ID2D1Factory* m_factory; 
	ID2D1HwndRenderTarget* m_rendertarget; 
	ID2D1SolidColorBrush* m_brush;
	IDWriteTextFormat* m_TextFormat = NULL;
	ID2D1DeviceContext* GetDeviceContext();
	ID2D1Bitmap* ImageToBitmap(ID2D1Image* pImg, D2D1_SIZE_U size, bool isEffect = false);
	ID2D1Effect* GetChromaEffect(ID2D1Bitmap* sprite);
};

#endif