#include "D3DUtil.h"

namespace d3d
{
	IDirect3DDevice9* gDevice = nullptr;

	bool InitD3D(
		const HINSTANCE hInstance, 
		const HWND hWnd, 
		const int width, const int height, 
		const bool bWindowed, 
		const D3DDEVTYPE deviceType, 
		IDirect3DDevice9** outDevice)
	{
		Microsoft::WRL::ComPtr<IDirect3D9> d3d9;
		d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
		if (!d3d9)
		{
			::MessageBox(nullptr, "InitD3D() - Direct3DCreate9() : FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		// 하드웨어 버텍스 프로세싱을 확인한다.
		D3DCAPS9 caps;
		d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);
		long vp = caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ? 
			D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		
		D3DPRESENT_PARAMETERS d3dpp;
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // 32비트 픽셀 포맷
		d3dpp.BackBufferCount = 1;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hWnd;
		d3dpp.Windowed = bWindowed;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags = 0;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		HRESULT hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			deviceType,
			hWnd,
			vp,
			&d3dpp,
			outDevice);

		if (FAILED(hr))
		{
			// 16 비트 깊이 버퍼로 다시 시도한다.
			d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

			hr = d3d9->CreateDevice(
				D3DADAPTER_DEFAULT,
				deviceType,
				hWnd,
				vp,
				&d3dpp,
				outDevice);

			if (FAILED(hr))
			{
				::MessageBox(nullptr, "InitD3D() - CreateDevice() : FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
				return false;
			}
		}

		return true;
	}

	void Destroy()
	{
		if (gDevice)
		{
			gDevice->Release();
			gDevice = nullptr;
		}
	}

	D3DMATERIAL9 InitMtrl(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR specular, D3DXCOLOR emissive, const float power)
	{
		D3DMATERIAL9 mtrl;
		mtrl.Ambient = ambient;
		mtrl.Diffuse = diffuse;
		mtrl.Specular = specular;
		mtrl.Emissive = emissive;
		mtrl.Power = power;
		return mtrl;
	}

}