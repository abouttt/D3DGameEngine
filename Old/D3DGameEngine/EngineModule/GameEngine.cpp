#include "GameEngine.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Transform.h"
#include "Light.h"
#include "UI.h"
#include "Image.h"
#include "Text.h"

namespace engine
{
	std::unordered_map<std::size_t, ComPtr<ID3DXMesh>> GameEngine::MeshResources;
	std::unordered_map<std::size_t, std::unique_ptr<Material>> GameEngine::MaterialResources;
	std::unordered_map<std::size_t, ComPtr<IDirect3DTexture9>> GameEngine::TextureResources;

	GameEngine::GameEngine()
		: mbInit(false)
		, mLightCount(-1)
		, mInput()
		, mTimer()
		, mMainCameraPtr(nullptr)
		, mScene()
		, mBehaviorsPtr()
		, mLightsPtr()
		, mMeshRenderersPtr()
		, mUIsPtr()
	{}

	GameEngine::~GameEngine()
	{
		mMainCameraPtr = nullptr;
	}

	bool GameEngine::Init(const HINSTANCE inHINSTANCE, const HWND inHWND)
	{
		// 이미 초기화 되었다면 진행하지 않는다.
		if (mbInit)
		{
			return false;
		}

		if (!mInput.Init(inHINSTANCE, inHWND))
		{
			return false;
		}

		MeshResources[HashKey::InvalidHash] = nullptr;
		TextureResources[HashKey::InvalidHash] = nullptr;
		MaterialResources[HashKey::InvalidHash] = nullptr;

		mTimer.Init();

		loadResources();

		mbInit = true;
		return true;
	}

	GameObject* GameEngine::CreateGameObject(const std::string& inName)
	{
		auto newGameObject = std::make_unique<GameObject>(inName);
		newGameObject.get()->mTransformPtr = newGameObject.get()->AddComponent<Transform>();
		newGameObject.get()->mGameEnginePtr = this;
		mScene.emplace_back(std::move(newGameObject));
		return mScene.back().get();
	}

	GameObject* GameEngine::CreateCube(const std::string& inName)
	{
		auto newGameObject = CreateGameObject(inName);
		auto meshFilter = newGameObject->AddComponent<MeshFilter>();
		auto meshRenderer = newGameObject->AddComponent<MeshRenderer>();

		meshFilter->SetMesh(HashKey::Mesh::Cube);
		meshRenderer->AddMaterialHashKey(HashKey::Material::White);
		meshRenderer->SetMeshFilter(meshFilter);

		return mScene.back().get();
	}

	GameObject* GameEngine::CreateSphere(const std::string& inName)
	{
		auto newGameObject = CreateGameObject(inName);
		auto meshFilter = newGameObject->AddComponent<MeshFilter>();
		auto meshRenderer = newGameObject->AddComponent<MeshRenderer>();

		meshFilter->SetMesh(HashKey::Mesh::Sphere);
		meshRenderer->AddMaterialHashKey(HashKey::Material::White);
		meshRenderer->SetMeshFilter(meshFilter);

		return mScene.back().get();
	}

	GameObject* GameEngine::CreateQuad(const std::string& inName)
	{
		auto newGameObject = CreateGameObject(inName);
		auto meshFilter = newGameObject->AddComponent<MeshFilter>();
		auto meshRenderer = newGameObject->AddComponent<MeshRenderer>();

		meshFilter->SetMesh(HashKey::Mesh::Quad);
		meshRenderer->AddMaterialHashKey(HashKey::Material::White);
		meshRenderer->SetMeshFilter(meshFilter);

		return mScene.back().get();
	}

	GameObject* GameEngine::CreateCamera(const std::string& inName)
	{
		auto newGameObject = CreateGameObject(inName);
		auto camera = newGameObject->AddComponent<Camera>();
		if (!mMainCameraPtr)
		{
			mMainCameraPtr = camera;
		}

		return mScene.back().get();
	}

	GameObject* GameEngine::CreateLight(const std::string& inName, const D3DLIGHTTYPE inType)
	{
		auto newGameObject = CreateGameObject(inName);
		auto light = newGameObject->AddComponent<Light>();
		light->SetLightType(inType);
		light->SetIndex(++mLightCount);
		mLightsPtr.emplace_back(light);

		return mScene.back().get();
	}

	GameObject* GameEngine::CreateImage(const std::string& inName, const std::size_t inTextureHashKey)
	{
		auto newGameObject = CreateGameObject(inName);
		newGameObject->AddComponent<Image>(inTextureHashKey);
		return mScene.back().get();
	}

	GameObject* GameEngine::CreateText(const std::string& inName)
	{
		auto newGameObject = CreateGameObject(inName);
		newGameObject->AddComponent<Text>();
		return mScene.back().get();
	}

	GameObject* GameEngine::FindGameObject(const std::string& inName)
	{
		auto it = findGameObjectIter(inName);
		return it != mScene.end() ? (*it).get() : nullptr;
	}

	bool GameEngine::RemoveGameObject(const std::string& inName)
	{
		auto it = findGameObjectIter(inName);

		if (it != mScene.end())
		{
			mScene.erase(it);
			return true;
		}

		return false;
	}

	const std::vector<std::unique_ptr<GameObject>>& GameEngine::GetScene() const
	{
		return mScene;
	}

	std::vector<std::unique_ptr<GameObject>>::const_iterator GameEngine::SceneBegin() const
	{
		return mScene.begin();
	}

	std::vector<std::unique_ptr<GameObject>>::const_iterator GameEngine::SceneEnd() const
	{
		return mScene.end();
	}

	std::vector<Behavior*>& GameEngine::GetBehaviors()
	{
		return mBehaviorsPtr;
	}

	std::vector<Behavior*>::iterator GameEngine::BehaviorBegin()
	{
		return mBehaviorsPtr.begin();
	}

	std::vector<Behavior*>::iterator GameEngine::BehaviorEnd()
	{
		return mBehaviorsPtr.end();
	}

	std::vector<Light*>& GameEngine::GetLights()
	{
		return mLightsPtr;
	}

	std::vector<Light*>::iterator GameEngine::LightBegin()
	{
		return mLightsPtr.begin();
	}

	std::vector<Light*>::iterator GameEngine::LightEnd()
	{
		return mLightsPtr.end();
	}

	std::vector<MeshRenderer*>& GameEngine::GetMeshRenderers()
	{
		return mMeshRenderersPtr;
	}

	std::vector<MeshRenderer*>::iterator GameEngine::MeshRendererBegin()
	{
		return mMeshRenderersPtr.begin();
	}

	std::vector<MeshRenderer*>::iterator GameEngine::MeshRendererEnd()
	{
		return mMeshRenderersPtr.end();
	}

	std::vector<UI*>& GameEngine::GetUIs()
	{
		return mUIsPtr;
	}

	std::vector<UI*>::iterator GameEngine::UIBegin()
	{
		return mUIsPtr.begin();
	}

	std::vector<UI*>::iterator GameEngine::UIEnd()
	{
		return mUIsPtr.end();
	}

	Camera* GameEngine::GetMainCamera()
	{
		return mMainCameraPtr;
	}

	void GameEngine::AddMeshResource(const std::size_t inMeshHashKey, ID3DXMesh* const inMesh)
	{
		assert(inMesh);

		GameEngine::MeshResources[inMeshHashKey] = ComPtr<ID3DXMesh>(inMesh);
	}

	void GameEngine::AddMaterialResource(
		const std::size_t& inMtrlHashKey,
		const Material& inMtrl,
		const RenderingMode inMode,
		const size_t& inTextureHashKey)
	{
		Material source(inMtrl);
		source.SetTextureKey(inTextureHashKey);
		source.SetRenderingMode(inMode);
		GameEngine::MaterialResources[inMtrlHashKey] = std::make_unique<Material>(source);
	}

	void GameEngine::AddTextureResource(const std::size_t inTextureHashKey, const std::string& inPath)
	{
		IDirect3DTexture9* tex = nullptr;
		d3d::LoadTexture(&tex, inPath);
		assert(tex);

		GameEngine::TextureResources[inTextureHashKey] = ComPtr<IDirect3DTexture9>(std::move(tex));
	}

	InputManager& GameEngine::GetInput()
	{
		return mInput;
	}

	Timer& GameEngine::GetTimer()
	{
		return mTimer;
	}

	std::vector<std::unique_ptr<GameObject>>::iterator GameEngine::findGameObjectIter(const std::string& inName)
	{
		return std::find_if(mScene.begin(), mScene.end(),
			[&](auto& gameObject)
			{
				return gameObject.get()->GetName() == inName;
			});
	}

	void GameEngine::loadResources()
	{
		// 메쉬.
		addCubeMeshResource();
		addSphereMeshResource();
		addQuadMeshResource();

		// 머터리얼.
		AddMaterialResource(HashKey::Material::White, d3d::WHITE_MTRL, RenderingMode::Opaque, HashKey::InvalidHash);
		AddMaterialResource(HashKey::Material::Red, d3d::RED_MTRL, RenderingMode::Opaque, HashKey::InvalidHash);
		AddMaterialResource(HashKey::Material::Crate, d3d::WHITE_MTRL, RenderingMode::Opaque, HashKey::Texture::Crate);
		AddMaterialResource(HashKey::Material::Fire, d3d::WHITE_MTRL, RenderingMode::Opaque, HashKey::Texture::Fire);
		AddMaterialResource(HashKey::Material::Ice, d3d::WHITE_MTRL, RenderingMode::Opaque, HashKey::Texture::Ice);
		AddMaterialResource(HashKey::Material::CacoDoom, d3d::WHITE_MTRL, RenderingMode::Cutout, HashKey::Texture::CacoDoom);
		AddMaterialResource(HashKey::Material::DoomGuy, d3d::WHITE_MTRL, RenderingMode::Cutout, HashKey::Texture::DoomGuy);


		// 텍스쳐.
		AddTextureResource(HashKey::Texture::Crate, "../Resources/Textures/crate.jpg");
		AddTextureResource(HashKey::Texture::Ice, "../Resources/Textures/ice.jpg");
		AddTextureResource(HashKey::Texture::Fire, "../Resources/Textures/fire.jpg");
		AddTextureResource(HashKey::Texture::CacoDoom, "../Resources/Textures/cacodoom.png");
		AddTextureResource(HashKey::Texture::DoomGuy, "../Resources/Textures/doomguy.png");
	}

	void GameEngine::addCubeMeshResource()
	{
		ID3DXMesh* cubeMesh = nullptr;
		D3DXCreateBox(d3d::Var::Device, 1, 1, 1, &cubeMesh, 0);
		d3d::SetNormalFVF(cubeMesh);
		d3d::SetTexFVF(cubeMesh);

		d3d::Vertex* vertices = nullptr;
		cubeMesh->LockVertexBuffer(0, (void**)&vertices);

		DWORD dwVertices = cubeMesh->GetNumVertices();
		int cnt = 0;
		for (DWORD i = 0; i < dwVertices; i++)
		{
			if (cnt == 0)
			{
				vertices->U = 0;
				vertices->V = 0;
			}
			else if (cnt == 1)
			{
				vertices->U = 1;
				vertices->V = 0;
			}
			else if (cnt == 2)
			{
				vertices->U = 1;
				vertices->V = 1;
			}
			else
			{
				vertices->U = 0;
				vertices->V = 1;
			}

			cnt++;
			if (cnt == 4)
			{
				cnt = 0;
			}

			vertices++;
		}

		cubeMesh->UnlockVertexBuffer();

		GameEngine::MeshResources[HashKey::Mesh::Cube] = ComPtr<ID3DXMesh>(std::move(cubeMesh));
	}

	void GameEngine::addSphereMeshResource()
	{
		ID3DXMesh* sphereMesh = nullptr;
		D3DXCreateSphere(d3d::Var::Device, 0.5f, 50, 50, &sphereMesh, 0);
		d3d::SetNormalFVF(sphereMesh);
		d3d::SetTexFVF(sphereMesh);

		d3d::Vertex* vertices = nullptr;
		sphereMesh->LockVertexBuffer(0, (void**)&vertices);

		DWORD dwVertices = sphereMesh->GetNumVertices();
		for (DWORD i = 0; i < dwVertices; i++)
		{
			vertices->U = -asinf(vertices->NX) / D3DX_PI + 0.5f;
			vertices->V = -asinf(vertices->NY) / D3DX_PI + 0.5f;
			vertices++;
		}

		sphereMesh->UnlockVertexBuffer();

		GameEngine::MeshResources[HashKey::Mesh::Sphere] = ComPtr<ID3DXMesh>(std::move(sphereMesh));
	}

	void GameEngine::addQuadMeshResource()
	{
		ID3DXMesh* quadMesh = nullptr;
		D3DXCreateMeshFVF(
			4,
			8,
			D3DXMESH_MANAGED,
			d3d::Vertex::FVF,
			d3d::Var::Device,
			&quadMesh);


		// 정점 버퍼 채우기.
		d3d::Vertex* vertices = nullptr;
		quadMesh->LockVertexBuffer(0, (void**)&vertices);
		vertices[0] = d3d::Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
		vertices[1] = d3d::Vertex(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
		vertices[2] = d3d::Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
		vertices[3] = d3d::Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		vertices[4] = d3d::Vertex(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
		vertices[5] = d3d::Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
		vertices[6] = d3d::Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
		vertices[7] = d3d::Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		quadMesh->UnlockVertexBuffer();

		// 인덱스 버퍼 채우기.
		WORD* i = nullptr;
		quadMesh->LockIndexBuffer(0, (void**)&i);
		i[0] = 0; i[1] = 1;  i[2] = 2;
		i[3] = 0; i[4] = 2;  i[5] = 3;
		i[6] = 4; i[7] = 5;  i[8] = 6;
		i[9] = 4; i[10] = 6; i[11] = 7;
		quadMesh->UnlockIndexBuffer();

		GameEngine::MeshResources[HashKey::Mesh::Quad] = ComPtr<ID3DXMesh>(std::move(quadMesh));
	}

}