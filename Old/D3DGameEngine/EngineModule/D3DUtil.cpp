#include "D3DUtil.h"

namespace d3d
{
	IDirect3DDevice9* Var::Device;

	const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	bool InitD3D(
		const HINSTANCE inHINSTANCE,
		const HWND inHWND,
		const int inWidth, int inHeight,
		const bool inbWindowed,
		const D3DDEVTYPE inDeviceType,
		IDirect3DDevice9** outDevice)
	{
		Microsoft::WRL::ComPtr<IDirect3D9> d3d9;
		d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

		if (!d3d9)
		{
			::MessageBox(0, _T("Direct3DCreate9() - FAILED"), 0, 0);
			return false;
		}

		// 하드웨어 버텍스 프로세싱을 확인한다.
		D3DCAPS9 caps;
		d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, inDeviceType, &caps);

		int vp = 0;
		if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		{
			vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		}
		else
		{
			vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		}

		D3DPRESENT_PARAMETERS d3dpp;
		d3dpp.BackBufferWidth = inWidth;
		d3dpp.BackBufferHeight = inHeight;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // 32비트 픽셀 포맷
		d3dpp.BackBufferCount = 1;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = inHWND;
		d3dpp.Windowed = inbWindowed;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags = 0;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		HRESULT hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			inDeviceType,
			inHWND,
			vp,
			&d3dpp,
			outDevice);

		if (FAILED(hr))
		{
			// 16 비트 깊이 버퍼로 다시 시도한다.
			d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

			hr = d3d9->CreateDevice(
				D3DADAPTER_DEFAULT,
				inDeviceType,
				inHWND,
				vp,
				&d3dpp,
				outDevice);

			if (FAILED(hr))
			{
				::MessageBox(0, _T("CreateDevice() - FAILED"), 0, 0);
				return false;
			}
		}

		return true;
	}

	void Destroy()
	{
		Release(Var::Device);
	}

	void SetNormalFVF(ID3DXMesh*& outMesh)
	{
		if (!(outMesh->GetFVF() & D3DFVF_NORMAL))
		{
			ID3DXMesh* tempMesh = nullptr;
			outMesh->CloneMeshFVF(
				outMesh->GetOptions(),
				outMesh->GetFVF() | D3DFVF_NORMAL,
				Var::Device,
				&tempMesh);

			// 법선 계산.
			D3DXComputeNormals(tempMesh, nullptr);

			Release<ID3DXMesh>(outMesh);
			outMesh = tempMesh;
		}
	}

	void SetTexFVF(ID3DXMesh*& outMesh)
	{
		if (!(outMesh->GetFVF() & D3DFVF_TEX1))
		{
			ID3DXMesh* tempMesh = nullptr;
			outMesh->CloneMeshFVF(
				outMesh->GetOptions(),
				outMesh->GetFVF() | D3DFVF_TEX1,
				Var::Device,
				&tempMesh);

			Release<ID3DXMesh>(outMesh);
			outMesh = tempMesh;
		}
	}

	D3DXVECTOR3 Math::Vec3Multiply(const D3DXVECTOR3& inV1, const D3DXVECTOR3& inV2)
	{
		D3DXVECTOR3 result;
		result.x = inV1.x * inV2.x;
		result.y = inV1.y * inV2.y;
		result.z = inV1.z * inV2.z;
		return result;
	}

	D3DXVECTOR3 Math::Vec3Rotate(const D3DXVECTOR3& inV, const D3DXQUATERNION& inQ)
	{
		D3DXQUATERNION q1, q2;
		D3DXQuaternionConjugate(&q1, &inQ);
		q2 = q1 * D3DXQUATERNION(inV.x, inV.y, inV.z, 1.0f) * inQ;
		return D3DXVECTOR3(q2.x, q2.y, q2.z);
	}

	D3DXQUATERNION Math::EulerToQuaternion(const D3DXVECTOR3& inV)
	{
		float sp = 0.f, sy = 0.f, sr = 0.f;
		float cp = 0.f, cy = 0.f, cr = 0.f;

		Math::GetSinCos(&sp, &cp, inV.x * 0.5f);
		Math::GetSinCos(&sy, &cy, inV.y * 0.5f);
		Math::GetSinCos(&sr, &cr, inV.z * 0.5f);

		D3DXQUATERNION result;
		result.w = sy * sp * sr + cy * cp * cr;
		result.x = sy * sr * cp + sp * cy * cr;
		result.y = sy * cp * cr - sp * sr * cy;
		result.z = -sy * sp * cr + sr * cy * cp;

		return result;
	}

	D3DXVECTOR3 Math::QuaternionToEuler(const D3DXQUATERNION& inQ)
	{
		D3DXVECTOR3 result;

		float sinrCosp = 2 * (inQ.w * inQ.z + inQ.x * inQ.y);
		float cosrCosp = 1 - 2 * (inQ.z * inQ.z + inQ.x * inQ.x);
		result.z = atan2f(sinrCosp, cosrCosp);

		float pitchTest = inQ.w * inQ.x - inQ.y * inQ.z;
		float asinThreshold = 0.4999995f;
		float sinp = 2 * pitchTest;
		if (pitchTest < -asinThreshold)
		{
			result.x = -90.f;
		}
		else if (pitchTest > asinThreshold)
		{
			result.x = 90.f;
		}
		else
		{
			result.x = asinf(sinp);
		}

		float sinyCosp = 2 * (inQ.w * inQ.y + inQ.x * inQ.z);
		float cosyCosp = 1.f - 2 * (inQ.x * inQ.x + inQ.y * inQ.y);
		result.y = atan2f(sinyCosp, cosyCosp);

		return result;
	}

	bool Math::EqualsInTolerance(const float inFloat1, const float inFloat2, const float inTolerance)
	{
		return std::abs(inFloat1 - inFloat2) <= inTolerance;
	}

	void Math::GetSinCos(float* const outSin, float* const outCos, const float inDegree)
	{
		assert(outSin);
		assert(outCos);

		if (inDegree == 0.f)
		{
			*outSin = 0.f;
			*outCos = 1.f;
		}
		else if (inDegree == 90.f)
		{
			*outSin = 1.f;
			*outCos = 0.f;
		}
		else if (inDegree == 180.f)
		{
			*outSin = 0.f;
			*outCos = -1.f;
		}
		else if (inDegree == 270.f)
		{
			*outSin = -1.f;
			*outCos = 0.f;
		}
		else
		{
			Math::GetSinCosRad(outSin, outCos, D3DXToRadian(inDegree));
		}
	}

	// Copied from UE4 Source Code
	void Math::GetSinCosRad(float* const outSin, float* const outCos, const float inRadian)
	{
		assert(outSin);
		assert(outCos);

		float quotient = (D3DX_1BYPI * 0.5f) * inRadian;
		if (inRadian >= 0.0f)
		{
			quotient = (float)((int)(quotient + 0.5f));
		}
		else
		{
			quotient = (float)((int)(quotient - 0.5f));
		}
		float y = inRadian - (2.0f * D3DX_PI) * quotient;

		// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
		float sign = 0.f;
		if (y > Math::HalfPI)
		{
			y = D3DX_PI - y;
			sign = -1.0f;
		}
		else if (y < -Math::HalfPI)
		{
			y = -D3DX_PI - y;
			sign = -1.0f;
		}
		else
		{
			sign = +1.0f;
		}

		float y2 = y * y;

		// 11-degree minimax approximation
		*outSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

		// 10-degree minimax approximation
		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
		*outCos = sign * p;
	}

	float Math::FMod(const float inX, const float inY)
	{
		if (fabsf(inY) <= (1.e-8f))
		{
			return 0.f;
		}

		const float quotient = (float)TruncToInt(inX / inY);
		float intPortion = inY * quotient;
		if (fabsf(intPortion) > fabsf(inX))
		{
			intPortion = inX;
		}

		return (inX - intPortion);
	}

	int Math::TruncToInt(const float inValue)
	{
		return (int)inValue;
	}

	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
	{
		D3DMATERIAL9 mtrl;
		mtrl.Ambient = a;
		mtrl.Diffuse = d;
		mtrl.Specular = s;
		mtrl.Emissive = e;
		mtrl.Power = p;
		return mtrl;
	}

	bool LoadTexture(IDirect3DTexture9** const outTexture, const std::string& inPath)
	{
		assert(outTexture);

		std::wstring wstr(inPath.begin(), inPath.end());

		HRESULT hr = D3DXCreateTextureFromFile(
			Var::Device,
			wstr.c_str(),
			outTexture);

		if (FAILED(hr))
		{
			std::string parentPath = "..\\" + inPath;
			wstr = std::wstring(parentPath.begin(), parentPath.end());
			HRESULT hr = D3DXCreateTextureFromFile(
				Var::Device,
				wstr.c_str(),
				outTexture);

			if (FAILED(hr))
			{
				std::string str = "LoadTexture() - FAILED : Not found " + inPath;
				wstr = std::wstring(str.begin(), str.end());
				::MessageBox(nullptr, wstr.c_str(), 0, 0);
				return false;
			}
		}

		return true;
	}

	bool OptimizeMesh(ID3DXMesh* outMesh)
	{
		assert(outMesh);

		std::vector<DWORD> adjBuffer(outMesh->GetNumFaces() * 3);
		outMesh->GenerateAdjacency(0.f, &adjBuffer[0]);

		HRESULT hr = outMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT |
			D3DXMESHOPT_COMPACT |
			D3DXMESHOPT_VERTEXCACHE,
			&adjBuffer[0],
			nullptr, nullptr, nullptr);

		if (FAILED(hr))
		{
			::MessageBox(nullptr, _T("OptimizeInplace() - FAILED"), 0, 0);
			return false;
		}

		return true;
	}

}
