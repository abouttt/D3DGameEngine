#include "EngineUtil.h"

namespace engine
{
	const std::size_t HashKey::InvalidHash = std::hash<std::string>()("!@#$NULL!@#$");

	// 메쉬.
	const std::size_t HashKey::Mesh::Cube = std::hash<std::string>()("CubeMesh");
	const std::size_t HashKey::Mesh::Sphere = std::hash<std::string>()("SphereMesh");
	const std::size_t HashKey::Mesh::Quad = std::hash<std::string>()("QuadMesh");

	// 텍스쳐.
	const std::size_t HashKey::Texture::Crate = std::hash<std::string>()("CrateTex");
	const std::size_t HashKey::Texture::Fire = std::hash<std::string>()("FireTex");
	const std::size_t HashKey::Texture::Ice = std::hash<std::string>()("IceTex");
	const std::size_t HashKey::Texture::CacoDoom = std::hash<std::string>()("CacoDoomTex");
	const std::size_t HashKey::Texture::DoomGuy = std::hash<std::string>()("DoomGuyTex");

	// 머터리얼.
	const std::size_t HashKey::Material::White = std::hash<std::string>()("WhiteMtrl");
	const std::size_t HashKey::Material::Red = std::hash<std::string>()("RedMtrl");
	const std::size_t HashKey::Material::Crate = std::hash<std::string>()("CrateMtrl");
	const std::size_t HashKey::Material::Fire = std::hash<std::string>()("FireMtrl");
	const std::size_t HashKey::Material::Ice = std::hash<std::string>()("IceMtrl");
	const std::size_t HashKey::Material::CacoDoom = std::hash<std::string>()("CacoDoomMtrl");
	const std::size_t HashKey::Material::DoomGuy = std::hash<std::string>()("DoomGuyMtrl");

}