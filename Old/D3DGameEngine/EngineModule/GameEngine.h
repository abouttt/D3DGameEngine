#pragma once

#include <assert.h>
#include <memory>
#include <vector>
#include <wrl.h>
#include <string>
#include <unordered_map>

#include "D3DUtil.h"
#include "EngineUtil.h"
#include "InputManager.h"
#include "Timer.h"

using namespace Microsoft::WRL;

namespace engine
{
	class Behavior;
	class Camera;
	class GameObject;
	class Light;
	class MeshRenderer;
	class UI;
	struct Material;

	class GameEngine
	{
	public:
		static std::unordered_map<std::size_t, ComPtr<ID3DXMesh>> MeshResources;
		static std::unordered_map<std::size_t, std::unique_ptr<Material>> MaterialResources;
		static std::unordered_map<std::size_t, ComPtr<IDirect3DTexture9>> TextureResources;

	public:
		GameEngine();
		~GameEngine();

	public:
		bool Init(const HINSTANCE inHINSTANCE, const HWND inHWND);

	public: // 게임 오브젝트 관련.
		GameObject* CreateGameObject(const std::string& inName);
		GameObject* CreateCube(const std::string& inName);
		GameObject* CreateSphere(const std::string& inName);
		GameObject* CreateQuad(const std::string& inName);

		GameObject* CreateCamera(const std::string& inName);
		GameObject* CreateLight(const std::string& inName, const D3DLIGHTTYPE inType);

		GameObject* CreateImage(const std::string& inName, const std::size_t inTextureHashKey = HashKey::InvalidHash);
		GameObject* CreateText(const std::string& inName);

		GameObject* FindGameObject(const std::string& inName);
		bool RemoveGameObject(const std::string& inName);

	public: // 동적 오브젝트 관련.
		const std::vector<std::unique_ptr<GameObject>>& GetScene() const;
		std::vector<std::unique_ptr<GameObject>>::const_iterator SceneBegin() const;
		std::vector<std::unique_ptr<GameObject>>::const_iterator SceneEnd() const;

		std::vector<Behavior*>& GetBehaviors();
		std::vector<Behavior*>::iterator BehaviorBegin();
		std::vector<Behavior*>::iterator BehaviorEnd();

		std::vector<Light*>& GetLights();
		std::vector<Light*>::iterator LightBegin();
		std::vector<Light*>::iterator LightEnd();

		std::vector<MeshRenderer*>& GetMeshRenderers();
		std::vector<MeshRenderer*>::iterator MeshRendererBegin();
		std::vector<MeshRenderer*>::iterator MeshRendererEnd();

		std::vector<UI*>& GetUIs();
		std::vector<UI*>::iterator UIBegin();
		std::vector<UI*>::iterator UIEnd();

		Camera* GetMainCamera();

	public: // 리소스 관련
		void AddMeshResource(const std::size_t inMeshHashKey, ID3DXMesh* const inMesh);
		void AddMaterialResource(
			const std::size_t& inMtrlHashKey,
			const Material& inMtrl,
			const RenderingMode inMode,
			const size_t& inTextureHashKey);
		void AddTextureResource(const std::size_t inTextureHashKey, const std::string& inPath);

	public:
		InputManager& GetInput();
		Timer& GetTimer();

	private:
		std::vector<std::unique_ptr<GameObject>>::iterator findGameObjectIter(const std::string& inName);

		void loadResources();
		void addCubeMeshResource();
		void addSphereMeshResource();
		void addQuadMeshResource();

	private:
		bool mbInit;
		DWORD mLightCount;

		InputManager mInput;
		Timer mTimer;

		Camera* mMainCameraPtr;

		std::vector<std::unique_ptr<GameObject>> mScene;

		std::vector<Behavior*> mBehaviorsPtr;
		std::vector<Light*> mLightsPtr;
		std::vector<MeshRenderer*> mMeshRenderersPtr;
		std::vector<UI*> mUIsPtr;
	};
}
