#pragma once

#include <assert.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <wrl.h>

namespace d3d
{
	extern IDirect3DDevice9* gDevice;

	bool InitD3D(
		const HINSTANCE hInstance,
		const HWND hWnd,
		const int width, const int height,
		const bool bWindowed,
		const D3DDEVTYPE deviceType,
		IDirect3DDevice9** outDevice);

	void Destroy();
}

