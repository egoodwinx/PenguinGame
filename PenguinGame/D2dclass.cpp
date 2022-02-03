/*
 * File:			d2dclass.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains D2Dclass methods 
 * http://www.rastertek.com/dx11tut02.html used as base 
 * First Version:	February 10, 2019
 */

#include "d2dclass.h"

/*
 * FUNC:	D2DClass
 * DESC:	Constructor for D2D class
 * PARAMS:	void
 * RET:		na
 */
D2DClass::D2DClass()
{
	m_factory = NULL;
	m_rendertarget = NULL;
	m_brush = NULL;
}

/*
 * FUNC:	~D2DClass
 * DESC:	Destructor for d2d class
 * PARAMS:	na
 * RET:		na
 */
D2DClass::~D2DClass()
{
}

/*
 * FUNC:	Initalize 
 * DESC:	initalize the d2d class
 * PARAMS:	
 *	int screenWidth - screen height
 *	int screenHeight - screen width
 *	HWND hwnd - window handle
 *	bool fullscreen - if it is full screen or not
 * RET:		
 */
bool D2DClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, bool fullscreen)
{
	// create factory
	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);
	if (result != S_OK)
	{
		return false;
	}

	// get window as rectangle
	RECT drawingArea;
	result = GetClientRect(hwnd, &drawingArea);
	
	//create render target for window
	result = m_factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(drawingArea.right, drawingArea.bottom)), &m_rendertarget);
	if (result != S_OK)
	{
		return false;
	}

	// create brush for rendertarer
	result = m_rendertarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &m_brush);
	if (result != S_OK)
	{
		return false;
	}

	SetTextFormat(72);

	return true;
}

/*
 * FUNC:	Shutdown
 * DESC:	shuts down the d2d class and cleans up the stuff.
 * PARAMS:	void
 * RET:		void
 */
void D2DClass::Shutdown()
{
	if (m_factory!=NULL)
	{
		m_factory->Release();
		m_factory = NULL;
	}

	if (m_brush != NULL)
	{
		m_brush->Release();
		m_brush = NULL;
	}

	if (m_rendertarget != NULL)
	{
		m_rendertarget->Release();
		m_rendertarget = NULL;
	}

	return;
}

/*
 * FUNC:	ClearScreen
 * DESC:	clear screen to desired colour
 * PARAMS:	
 *	float r - red colour value
 *	float g - green colour value
 *	float b - blue colour value
 * RET:		void
 */
void D2DClass::ClearScreen(float r, float g, float b)
{
	m_rendertarget->Clear(D2D1::ColorF(r, g, b));
}

/*
 * FUNC:	DrawRectangle
 * DESC:	Draw the rectangle at the given coordinates.
 * PARAMS:	
 *	float topX - the top x value
 *	float topY - the top y value
 *	float botX - the bottom x value
 *	float botY - the bottom y value
 * RET:		void
 */
void D2DClass::DrawRectangle(float topX, float topY, float botX, float botY)
{
	D2D1_RECT_F rect = { topX,topY,botX, botY};
	m_rendertarget->FillRectangle(&rect, m_brush);
	D2D1_SIZE_F rtSize = m_rendertarget->GetSize();
}

/*
 * FUNC:	SetBrushColour 
 * DESC:	Set the brushes colour using d2d1 colour
 * PARAMS:	
 *	D2D1::ColorF colour - the colour to set it to;
 * RET:		void
 */
void D2DClass::SetBrushColour(D2D1::ColorF colour)
{
	m_brush->SetColor(colour);
}

/*
 * FUNC:	SetBrushColour
 * DESC:	set the brushes colour using rgba
 * PARAMS:	
 *	float r - red value
 *	float b - blue value
 *	float g - green value
 *	float a - alpha value
 * RET: void		
 */
void D2DClass::SetBrushColour(float r, float b, float g, float a)
{
	m_brush->SetColor(D2D1::ColorF(r,g,b, a));
}

/*
 * FUNC:	GetRenderTarget 
 * DESC:	Get the render target
 * PARAMS:	void
 * RET:		ID2D1HwndTenderTarger* - get the render target 
 */
ID2D1HwndRenderTarget* D2DClass::GetRenderTarget()
{
	return m_rendertarget;
}

/*
 * FUNC:	DrawSprite
 * DESC:	Draws the sprite at the given location
 * PARAMS:	
 *	ID2D1Bitmap sprite - the sprite to draw
 *	float topX - the top x coordinate
 *	float topY - the top y coordinate
 *	float botX - the bottom x coordinate
 *	float botY - the bottom y cooridnate
 *	float scale - size
 * RET:		
 */
void D2DClass::DrawSprite(ID2D1Bitmap* sprite, float topX, float topY, float botX, float botY, float scale)
{
	m_rendertarget->DrawBitmap(sprite, D2D1::RectF(topX, topY, botX, botY), scale, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
}

/*
 * FUNC:	GetDeviceContext
 * DESC:	Get the device context
 * PARAMS:	void
 * RET:		ID2D1DeviceContext* the device context
 */
ID2D1DeviceContext* D2DClass::GetDeviceContext()
{
	ID2D1DeviceContext* rtDC;
	m_rendertarget->QueryInterface(&rtDC);
	return rtDC;
}

/*
 * FUNC:	ImageToBitmap
 * DESC:	Convert an image to a bitmap
 * PARAMS:	
 *	ID2D1Image* pImage - image to convert
 *	D2D1_Size_U size - the image size
 *	bool iseffect - if the image is really an effect
 * RET:		return ID2D1Bitmap* - the created 3bitmap
 */
//https://stackoverflow.com/questions/31118397/direct2d-convert-id2d1image-to-id2d1bitmap
ID2D1Bitmap* D2DClass::ImageToBitmap(ID2D1Image* pImg, D2D1_SIZE_U size, bool isEffect)
{
	ID2D1Image* oldTarget = NULL;
	ID2D1Bitmap1* targetBitmap = NULL;

	//Create a Bitmap with "D2D1_BITMAP_OPTIONS_TARGET"
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
	GetDeviceContext()->CreateBitmap(size, 0, 0, bitmapProperties, &targetBitmap);
	m_rendertarget->BeginDraw();
	//Save current Target, replace by ID2D1Bitmap
	GetDeviceContext()->GetTarget(&oldTarget);
	GetDeviceContext()->SetTarget(targetBitmap);
	//Draw Image on Target (if currently not drawing also call Begin/EndDraw)
	if (isEffect)
	{
		GetDeviceContext()->DrawImage((ID2D1Effect*)pImg);
	}
	else
	{
		GetDeviceContext()->DrawImage(pImg);
	}

	//Set previous Target
	GetDeviceContext()->SetTarget(oldTarget);

	oldTarget->Release();
	m_rendertarget->EndDraw();

	return targetBitmap;
}

/*
 * FUNC:	GetChromaEffect
 * DESC:	Get the chroma effect for the sprite
 * PARAMS:	
 * ID2D1Bitmap* sprite - the sprite to chroma key
 * RET:		
 */
ID2D1Effect* D2DClass::GetChromaEffect(ID2D1Bitmap* sprite)
{
	ID2D1Effect *chromakeyEffect = NULL;
	D2D1_VECTOR_3F vector{ 0.0f, 0.0f, 1.0f };
	GetDeviceContext()->CreateEffect(CLSID_D2D1ChromaKey, &chromakeyEffect);
	chromakeyEffect->SetInput(0, sprite);
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, vector);
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.5f);
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, true);

	return chromakeyEffect;
}

/*
 * FUNC:	ApplyChroma
 * DESC:	Apply chromakey to a sprite
 * PARAMS:	
 *	ID2D1Bitmap*& - the sprite to chroma key
 * RET:		void
 */
void D2DClass::ApplyChroma(ID2D1Bitmap*& sprite)
{
	ID2D1Effect *chromakeyEffect = GetChromaEffect(sprite);
	D2D1_SIZE_U size = (sprite)->GetPixelSize();
	sprite->Release();
	sprite = ImageToBitmap((ID2D1Image*) chromakeyEffect, size, true);
}

/*
 * FUNC:	DrawString
 * DESC:	Draw the given string in the given area with the given colour as the given size.
 * PARAMS:
 *	std::string string - the string to draw
 *	float topX - top x coordinate
 *	float topY - top y coordinate
 *	float botX - bottom x cooridate
 *	float botY - bottom y coordinate 
 *	D2D1::ColorF colour - the colour of the string
 *	int fontSize - the font size of the string
 * RET:		void
 * https://docs.microsoft.com/en-us/windows/desktop/direct2d/how-to--draw-text
 */
void D2DClass::DrawString(std::string string, float topX, float topY, float botX, float botY, D2D1::ColorF colour, int fontSize)
{	
	SetTextFormat(fontSize);
	std::wstring widestr = std::wstring(string.begin(), string.end());
	WCHAR* stringPrinting = (WCHAR*)widestr.c_str();
	D2D1_RECT_F rect = { topX,topY,botX, botY };
	SetBrushColour(colour);
	m_rendertarget->DrawText(stringPrinting, 
								((long)string.length()+1),
								m_TextFormat,
								rect,
								m_brush);
}

/*
 * FUNC:	SetTextFormat
 * DESC:	Set the text format, how we should draw the string
 * PARAMS:
 *	int fontSize - the font size of the text
 * RET:		void
 */
//https://docs.microsoft.com/en-us/windows/desktop/direct2d/how-to--draw-text
void D2DClass::SetTextFormat(int fontSize)
{
	const WCHAR msc_fontName[] = L"Verdana";
	const FLOAT msc_fontSize = float(fontSize);
	HRESULT hr;
	IDWriteFactory* m_WriteFactory;

	// Create a DirectWrite factory.
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_ISOLATED,
		__uuidof(m_WriteFactory),
		reinterpret_cast<IUnknown **>(&m_WriteFactory)
	);

	if (SUCCEEDED(hr))
	{
		if (m_TextFormat)
		{
			m_TextFormat->Release();
		}
		// Create a DirectWrite text format object.
		hr = m_WriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&m_TextFormat
		);
		m_WriteFactory->Release();
	}
	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		m_TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
}

