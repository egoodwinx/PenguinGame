/*
 * File:			sprite.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains the class definition for the sprite object.
 * First Version:	Febuary 10, 2019
 */

#pragma once

#include "common.h"
#include "D2DClass.h"
#include <d2d1.h>
#include <wincodec.h>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

/*
 * Class	Sprite
 * Desc:	Models a sprite
 */
class Sprite
{
private:
	D2DClass d2d;
	template <class T> void SafeRelease(T **ppT);
public:

	int LoadBitmapFromFile(ID2D1RenderTarget *pRenderTarget,
		IWICImagingFactory *pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight);
	void UpdateBitmap(ID2D1RenderTarget* renderTarget);
	ID2D1Bitmap* p_Bitmap;
	IWICBitmapFrameDecode* p_WicBitmapFrame;
};