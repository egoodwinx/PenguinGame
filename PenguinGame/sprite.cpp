/*
 * File:			sprite.cpp
 * Programmer:		Emily Goodwin
 * Project:			GAS A1
 * Description:		Contains methods for sprite class.
 * First Version:	Febuary 10, 2019
 */

#include "sprite.h"

/*
 * FUNC:	LoadBitmapFromFile
 * DESC:	Load a bitmap from a file.
 * PARAMS:	
 *  ID2D1RengerTarget - the render target
 *	IWICImagingFactory *pIWICFactory - IWIC factory.
 *	PCWSTR uri - the file path
 *	UINT destinationWidth - sprite rectangle width
 *	UINT destinationHeight - sprite rectangle height
 * RET: int - if it was successful.		
 */
int Sprite::LoadBitmapFromFile(ID2D1RenderTarget *pRenderTarget,
	IWICImagingFactory *pIWICFactory,
	PCWSTR uri,
	UINT destinationWidth,
	UINT destinationHeight)
{
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

    HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
        uri,
        NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder);
    if (SUCCEEDED(hr))
    {
        // Create the initial frame.
        hr = pDecoder->GetFrame(0, &pSource);
    }

	if (SUCCEEDED(hr))
	{

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);

	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.0f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			&this->p_Bitmap);
		this->p_WicBitmapFrame = pSource;
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

void Sprite::UpdateBitmap(ID2D1RenderTarget* renderTarget)
{
	int result = 0;
	IWICImagingFactory *pIWICFactory; 
	IWICFormatConverter *pConverter;
	result = CoCreateInstance(
		CLSID_WICImagingFactory, //CLS ID of the object about to be made
		NULL, //not needed here, but just denotes this isn't part of an aggregate
		CLSCTX_INPROC_SERVER, //Indicates this DLL runs in the same process
		IID_IWICImagingFactory, //Reference to an Interface that talks to the object
		(LPVOID*)&pIWICFactory); //This is our pointer to the WICFactory, once set up.
	pIWICFactory->CreateFormatConverter(&pConverter);
	result = pConverter->Initialize(
		p_WicBitmapFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0f,
		WICBitmapPaletteTypeMedianCut
	);
	result = renderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &p_Bitmap);
}


/*
 * FUNC:	SafeRelease 
 * DESC:	Safely release object
 * PARAMS:	T **ppT - the object to release
 * RET:		void
 */
template <class T> void Sprite::SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}