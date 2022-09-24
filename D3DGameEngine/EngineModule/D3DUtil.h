#pragma once

#include <assert.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <cmath>
#include <wrl.h>

namespace d3d
{
	extern IDirect3DDevice9* gDevice;

	namespace Math
	{
		constexpr float TwoPI = { 2.f * D3DX_PI };
		constexpr float HalfPI = { 1.57079632679f };

		D3DXVECTOR3 Vec3Multiply(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2);
		D3DXVECTOR3 Vec3Rotate(const D3DXVECTOR3& vec, const D3DXQUATERNION& quat);
		D3DXQUATERNION EulerToQuaternion(const D3DXVECTOR3& vec);
		D3DXVECTOR3 QuaternionToEuler(const D3DXQUATERNION& quat);
		bool EqualsInTolerance(const float float1, const float float2, const float tolerance = (1.e-8f));
		void GetSinCos(float* const outSin, float* const outCos, const float degree);
		void GetSinCosRad(float* const outSin, float* const outCos, const float radian);
		float FMod(const float x, const float y);
		int TruncToInt(const float value);
	}

	//
	// Create / Delete
	//

	bool InitD3D(
		const HINSTANCE hInstance,
		const HWND hWnd,
		const int width, const int height,
		const bool bWindowed,
		const D3DDEVTYPE deviceType,
		IDirect3DDevice9** outDevice);

	void Destroy();

	//
	// Vector3
	//

	const D3DXVECTOR3 VECTOR3_ZERO = D3DXVECTOR3(0.f, 0.f, 0.f);
	const D3DXVECTOR3 VECTOR3_ONE = D3DXVECTOR3(1.f, 1.f, 1.f);
	const D3DXVECTOR3 VECTOR3_FORWARD = D3DXVECTOR3(0.f, 0.f, 1.f);
	const D3DXVECTOR3 VECTOR3_BACKWARD = D3DXVECTOR3(0.f, 0.f, -1.f);
	const D3DXVECTOR3 VECTOR3_UP = D3DXVECTOR3(0.f, 1.f, 0.f);
	const D3DXVECTOR3 VECTOR3_DOWN = D3DXVECTOR3(0.f, -1.f, 0.f);
	const D3DXVECTOR3 VECTOR3_RIGHT = D3DXVECTOR3(1.f, 0.f, 0.f);
	const D3DXVECTOR3 VECTOR3_LEFT = D3DXVECTOR3(-1.f, 0.f, 0.f);

	//
	// Quaternion
	//

	const D3DXQUATERNION QUATERNION_IDENTITY = D3DXQUATERNION(0.f, 0.f, 0.f, 1.f);

	//
	// Colors
	//

	const D3DXCOLOR WHITE(D3DCOLOR_XRGB(255, 255, 255));
	const D3DXCOLOR BLACK(D3DCOLOR_XRGB(0, 0, 0));
	const D3DXCOLOR GRAY(D3DCOLOR_XRGB(128, 128, 128));
	const D3DXCOLOR RED(D3DCOLOR_XRGB(255, 0, 0));
	const D3DXCOLOR GREEN(D3DCOLOR_XRGB(0, 255, 0));
	const D3DXCOLOR BLUE(D3DCOLOR_XRGB(0, 0, 255));
	const D3DXCOLOR YELLOW(D3DCOLOR_XRGB(255, 255, 0));
	const D3DXCOLOR CYAN(D3DCOLOR_XRGB(0, 255, 255));
	const D3DXCOLOR MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

	//
	// Materials
	//

	D3DMATERIAL9 InitMtrl(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR specular, D3DXCOLOR emissive, const float power);

	const D3DMATERIAL9 WHITE_MTRL = InitMtrl(WHITE, WHITE, WHITE, BLACK, 8.0f);
	const D3DMATERIAL9 RED_MTRL = InitMtrl(RED, RED, RED, BLACK, 8.0f);
	const D3DMATERIAL9 GREEN_MTRL = InitMtrl(GREEN, GREEN, GREEN, BLACK, 8.0f);
	const D3DMATERIAL9 BLUE_MTRL = InitMtrl(BLUE, BLUE, BLUE, BLACK, 8.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 8.0f);
}

