#pragma once

#include "D3DUtil.h"

namespace engine
{
	enum class RenderingMode
	{
		Opaque,
		Cutout
	};

	struct HashKey
	{
		static const std::size_t InvalidHash;

		struct Mesh
		{
			static const std::size_t Cube;
			static const std::size_t Sphere;
			static const std::size_t Quad;
		};

		struct Texture
		{
			static const std::size_t Crate;
			static const std::size_t Fire;
			static const std::size_t Ice;
			static const std::size_t CacoDoom;
			static const std::size_t DoomGuy;
		};

		struct Material
		{
			static const std::size_t White;
			static const std::size_t Red;
			static const std::size_t Crate;
			static const std::size_t Fire;
			static const std::size_t Ice;
			static const std::size_t CacoDoom;
			static const std::size_t DoomGuy;
		};
		
	};
}
