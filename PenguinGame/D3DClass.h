/*
* File:				D3DClass.h
* Programmer:		Emily Goodwin
* Project:			GAS A1
* Description:		Contains the D3D class definition.
* First Version:	March 22, 2019
*/
// uses Tutorial04 
// This application displays a 3D cube using Direct3D 11 
// http://msdn.microsoft.com/en-us/library/windows/apps/ff729721.aspx 

#pragma once
#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_ 

#define IDS_APP_TITLE           103 

#define IDR_MAINFRAME           128 
#define IDD_TUTORIAL1_DIALOG    102 
#define IDD_ABOUTBOX            103 
#define IDM_ABOUT               104 
#define IDM_EXIT                105 
#define IDI_TUTORIAL1           107 
#define IDI_SMALL               108 
#define IDC_TUTORIAL1           109 
#define IDC_MYICON              2 
#define IDC_STATIC              -1 
// Next default values for new objects 
//  
#ifdef APSTUDIO_INVOKED 
#ifndef APSTUDIO_READONLY_SYMBOLS 

#define _APS_NO_MFC                 130 
#define _APS_NEXT_RESOURCE_VALUE    129 
#define _APS_NEXT_COMMAND_VALUE     32771 
#define _APS_NEXT_CONTROL_VALUE     1000 
#define _APS_NEXT_SYMED_VALUE       110 
#endif 
#endif 
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <d3d11.h>
#include <windows.h> 
#include <d3d11_1.h> 
#include <d3dcompiler.h> 
#include <directxmath.h> 
#include <directxcolors.h> 
#include <directxmath.h>
using namespace DirectX;
class D3DClass
{

public:
	struct SimpleVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};


	struct ConstantBuffer
	{
		XMMATRIX mWorld;
		XMMATRIX mView;
		XMMATRIX mProjection;
	};
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, HWND parentWin);
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT InitDevice();
	void CleanupDevice();
	void Render();
	void ShowChildWindow();
	void HideChildWindow();
	void* operator new(size_t i);
	void operator delete(void* p);
private:
	HINSTANCE               g_hInst = nullptr;
	HWND                    g_hWnd = nullptr;
	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           g_pd3dDevice = nullptr;
	ID3D11Device1*          g_pd3dDevice1 = nullptr;
	ID3D11DeviceContext*    g_pImmediateContext = nullptr;
	ID3D11DeviceContext1*   g_pImmediateContext1 = nullptr;
	IDXGISwapChain*         g_pSwapChain = nullptr;
	IDXGISwapChain1*        g_pSwapChain1 = nullptr;
	ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
	ID3D11VertexShader*     g_pVertexShader = nullptr;
	ID3D11PixelShader*      g_pPixelShader = nullptr;
	ID3D11InputLayout*      g_pVertexLayout = nullptr;
	ID3D11Buffer*           g_pVertexBuffer = nullptr;
	ID3D11Buffer*           g_pIndexBuffer = nullptr;
	ID3D11Buffer*           g_pConstantBuffer = nullptr;
	XMMATRIX                g_World;
	XMMATRIX                g_View;
	XMMATRIX                g_Projection;
};

#endif