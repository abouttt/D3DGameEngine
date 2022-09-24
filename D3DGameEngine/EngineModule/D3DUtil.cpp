#include "D3DUtil.h"

namespace d3d
{
	IDirect3DDevice9* gDevice = nullptr;

	namespace Math
	{
		D3DXVECTOR3 Vec3Multiply(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2)
		{
			D3DXVECTOR3 result;
			result.x = v1.x * v2.x;
			result.y = v1.y * v2.y;
			result.z = v1.z * v2.z;
			return result;
		}

		D3DXVECTOR3 Vec3Rotate(const D3DXVECTOR3& v, const D3DXQUATERNION& q)
		{
			D3DXQUATERNION q1, q2;
			D3DXQuaternionConjugate(&q1, &q);
			q2 = q1 * D3DXQUATERNION(v.x, v.y, v.z, 1.0f) * q;
			return D3DXVECTOR3(q2.x, q2.y, q2.z);
		}

		D3DXQUATERNION EulerToQuaternion(const D3DXVECTOR3& v)
		{
			float sp = 0.f, sy = 0.f, sr = 0.f;
			float cp = 0.f, cy = 0.f, cr = 0.f;

			Math::GetSinCos(&sp, &cp, v.x * 0.5f);
			Math::GetSinCos(&sy, &cy, v.y * 0.5f);
			Math::GetSinCos(&sr, &cr, v.z * 0.5f);

			D3DXQUATERNION result;
			result.w = sy * sp * sr + cy * cp * cr;
			result.x = sy * sr * cp + sp * cy * cr;
			result.y = sy * cp * cr - sp * sr * cy;
			result.z = -sy * sp * cr + sr * cy * cp;

			return result;
		}

		D3DXVECTOR3 QuaternionToEuler(const D3DXQUATERNION& q)
		{
			D3DXVECTOR3 result;

			float sinrCosp = 2 * (q.w * q.z + q.x * q.y);
			float cosrCosp = 1 - 2 * (q.z * q.z + q.x * q.x);
			result.z = atan2f(sinrCosp, cosrCosp);

			float pitchTest = q.w * q.x - q.y * q.z;
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

			float sinyCosp = 2 * (q.w * q.y + q.x * q.z);
			float cosyCosp = 1.f - 2 * (q.x * q.x + q.y * q.y);
			result.y = atan2f(sinyCosp, cosyCosp);

			return result;
		}

		bool EqualsInTolerance(const float float1, const float float2, const float tolerance)
		{
			return std::abs(float1 - float2) <= tolerance;
		}

		void GetSinCos(float* const outSin, float* const outCos, const float degree)
		{
			assert(outSin);
			assert(outCos);

			if (degree == 0.f)
			{
				*outSin = 0.f;
				*outCos = 1.f;
			}
			else if (degree == 90.f)
			{
				*outSin = 1.f;
				*outCos = 0.f;
			}
			else if (degree == 180.f)
			{
				*outSin = 0.f;
				*outCos = -1.f;
			}
			else if (degree == 270.f)
			{
				*outSin = -1.f;
				*outCos = 0.f;
			}
			else
			{
				Math::GetSinCosRad(outSin, outCos, D3DXToRadian(degree));
			}
		}

		// Copied from UE4 Source Code
		void GetSinCosRad(float* const outSin, float* const outCos, const float radian)
		{
			assert(outSin);
			assert(outCos);

			float quotient = (D3DX_1BYPI * 0.5f) * radian;
			if (radian >= 0.0f)
			{
				quotient = (float)((int)(quotient + 0.5f));
			}
			else
			{
				quotient = (float)((int)(quotient - 0.5f));
			}
			float y = radian - (2.0f * D3DX_PI) * quotient;

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

		float FMod(const float x, const float y)
		{
			if (fabsf(y) <= (1.e-8f))
			{
				return 0.f;
			}

			const float quotient = (float)TruncToInt(x / y);
			float intPortion = y * quotient;
			if (fabsf(intPortion) > fabsf(x))
			{
				intPortion = x;
			}

			return (x - intPortion);
		}

		int TruncToInt(const float value)
		{
			return (int)value;
		}
	}

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