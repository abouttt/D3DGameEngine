#include "Light.h"
#include "Transform.h"
#include "GameEngine.h"

namespace engine
{
	Light::Light()
		: mLight()
		, mIndex(-1)
	{
		::ZeroMemory(&mLight, sizeof(D3DLIGHT9));
		initDirectionLight();
		SetColor(d3d::WHITE);
	}

	Light::~Light()
	{
		auto it = find(GetEngine()->LightBegin(), GetEngine()->LightEnd(), this);
		if (it != GetEngine()->LightEnd())
		{
			GetEngine()->GetLights().erase(it);
		}
	}

	const D3DLIGHT9& Light::GetSource() const
	{
		return mLight;
	}

	void Light::SetLightType(const D3DLIGHTTYPE lightType)
	{
		switch (lightType)
		{
		case D3DLIGHT_DIRECTIONAL:
			initDirectionLight();
			break;

		case D3DLIGHT_POINT:
			initPointLight();
			break;

		case D3DLIGHT_SPOT:
			initSpotLight();
			break;

		default:
			assert(false);
		}
	}

	void Light::SetColor(const D3DXCOLOR& color)
	{
		mLight.Ambient = color * 0.6f;
		mLight.Diffuse = color;
		mLight.Specular = color * 0.6f;
	}

	void Light::SetRange(const float range)
	{
		mLight.Range = range;
	}

	DWORD Light::GetIndex() const
	{
		return mIndex;
	}

	void Light::SetIndex(const DWORD index)
	{
		mIndex = index;
	}

	void Light::UpdateTransform()
	{
		mLight.Position = GetTransform()->GetPosition();
		auto dir = GetTransform()->GetEulerAngles();
		D3DXVec3Normalize(static_cast<D3DXVECTOR3*>(&mLight.Direction), &dir);
	}

	void Light::initDirectionLight()
	{
		mLight.Type = D3DLIGHT_DIRECTIONAL;
	}

	void Light::initPointLight()
	{
		mLight.Type = D3DLIGHT_POINT;
		mLight.Range = 1000.0f;
		mLight.Falloff = 1.0f;
		mLight.Attenuation0 = 1.0f;
		mLight.Attenuation1 = 0.0f;
		mLight.Attenuation2 = 0.0f;
	}

	void Light::initSpotLight()
	{
		mLight.Type = D3DLIGHT_SPOT;
		mLight.Range = 1000.0f;
		mLight.Falloff = 1.0f;
		mLight.Attenuation0 = 1.0f;
		mLight.Attenuation1 = 0.0f;
		mLight.Attenuation2 = 0.0f;
		mLight.Theta = 0.5f;
		mLight.Phi = 0.7f;
	}

	void Light::addToComponentPtrContainer()
	{
		GetEngine()->GetLights().emplace_back(this);
	}
}