#pragma once

#include "Component.h"
#include "D3DUtil.h"

namespace engine
{
	class Light : public Component
	{
	public:
		Light();
		~Light() = default;

	public:
		const D3DLIGHT9& GetSource() const;
		void SetLightType(const D3DLIGHTTYPE lightType);
		void SetColor(const D3DXCOLOR& color);
		void SetRange(const float range);
		DWORD GetIndex() const;
		void SetIndex(const DWORD index);
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
