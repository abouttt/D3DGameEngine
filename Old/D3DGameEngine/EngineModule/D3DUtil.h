#pragma once

#include <assert.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <string>
#include <tchar.h>
#include <vector>
#include <wrl.h>

namespace d3d
{
	struct Vertex;

	struct Var
	{
		static IDirect3DDevice9* Device;
	};

	struct Math
	{
		static constexpr float TwoPI = { 2.f * D3DX_PI };
		static constexpr float HalfPI = { 1.57079632679f };

		static D3DXVECTOR3 Vec3Multiply(const D3DXVECTOR3& inV1, const D3DXVECTOR3& inV2);
		static D3DXVECTOR3 Vec3Rotate(const D3DXVECTOR3& inV, const D3DXQUATERNION& inQ);
		static D3DXQUATERNION EulerToQuaternion(const D3DXVECTOR3& inV);
		static D3DXVECTOR3 QuaternionToEuler(const D3DXQUATERNION& inQ);
		static bool EqualsInTolerance(const float inFloat1, const float inFloat2, const float inTolerance = (1.e-8f));
		static void GetSinCos(float* const outSin, float* const outCos, const float inDegree);
		static void GetSinCosRad(float* const outSin, float* const outCos, const float inRadian);
		static float FMod(const float inX, const float inY);
		static int TruncToInt(const float inValue);
	};

	//
	// Create / Delete
	//

	bool InitD3D(
		const HINSTANCE inHINSTANCE,
		const HWND inHWND,
		const int inWidth, const int inHeight,
		const bool inbWindowed,
		const D3DDEVTYPE inDeviceType,
		IDirect3DDevice9** outDevice);

	void Destroy();

	//
	// Cleanup
	//

	template<typename T>
	inline void Release(T*& outT)
	{
		if (outT)
		{
			outT->Release();
			outT = nullptr;
		}
	}

	template<typename T>
	inline void Delete(T*& outT)
	{
		if (outT)
		{
			delete outT;
			outT = nullptr;
		}
	}

	template<typename T>
	inline void DeleteArray(T*& outT)
	{
		if (outT)
		{
			delete[] outT;
			outT = nullptr;
		}
	}

	//
	// Vertex
	//

	void SetNormalFVF(ID3DXMesh*& outMesh);
	void SetTexFVF(ID3DXMesh*& outMesh);

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

	D3DMATERIAL9 InitMtrl(D3DXCOLOR inAmbient, D3DXCOLOR inDiffuse, D3DXCOLOR inSpecular, D3DXCOLOR inEmissive, const float inPower);

	const D3DMATERIAL9 WHITE_MTRL = InitMtrl(WHITE, WHITE, WHITE, BLACK, 8.0f);
	const D3DMATERIAL9 RED_MTRL = InitMtrl(RED, RED, RED, BLACK, 8.0f);
	const D3DMATERIAL9 GREEN_MTRL = InitMtrl(GREEN, GREEN, GREEN, BLACK, 8.0f);
	const D3DMATERIAL9 BLUE_MTRL = InitMtrl(BLUE, BLUE, BLUE, BLACK, 8.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 8.0f);

	//
	// Texture
	//

	bool LoadTexture(IDirect3DTexture9** const outTexture, const std::string& inPath);

	//
	// Mesh
	//

	bool OptimizeMesh(ID3DXMesh* outMesh);

	//
	// Vertex Structures
	//

	struct Vertex
	{
		Vertex()
			: X(0), Y(0), Z(0)
			, NX(0), NY(0), NZ(0)
			, U(0), V(0)
		{}

		Vertex(float inX, float inY, float inZ,
			float inNX, float inNY, float inNZ,
			float inU, float inV)
			: X(inX), Y(inY), Z(inZ)
			, NX(inNX), NY(inNY), NZ(inNZ)
			, U(inU), V(inV)
		{}

		float X, Y, Z;
		float NX, NY, NZ;
		float U, V;

		static const DWORD FVF;
	};

}
