#pragma once

#include "D3DUtil.h"
#include "Component.h"

namespace engine
{
	class Light : public Component
	{
	public:
		Light();

	public:
		const D3DLIGHT9& GetLight() const;
		void SetLightType(const D3DLIGHTTYPE inType);
		void SetColor(const D3DXCOLOR& inColor);
		void SetRange(const float inRange);
		DWORD GetIndex() const;
		void SetIndex(const DWORD inIndex);
		void UpdateTransform();

	private:
		void initDirectionLight();
		void initPointLight();
		void initSpotLight();

	private:
		D3DLIGHT9 mLight;
		DWORD mIndex;
	};
}

