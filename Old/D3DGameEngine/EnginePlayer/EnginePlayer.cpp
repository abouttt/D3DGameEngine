#include "EnginePlayer.h"
#include "EngineUtil.h"
#include "WindowsPlayer.h"

#include "Behavior.h"
#include "Camera.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Transform.h"
#include "Light.h"
#include "Image.h"
#include "Text.h"

#include "CameraController.h"
#include "PerformanceText.h"
#include "Rotator.h"

using namespace engine;

EnginePlayer::EnginePlayer()
	: mbInit(false)
	, mEngine()
	, mCutoutRenderBeginIt()
{}

void EnginePlayer::Init()
{
	// 이미 초기화 되었다면 진행하지 않는다.
	if (mbInit)
	{
		return;
	}

	setRenderPipeline();

	mEngine.Init(wndplayer::Var::Instance, wndplayer::Var::WndHandler);

	loadScene();

	mbInit = true;
}

void EnginePlayer::OnTick()
{
	if (!mbInit)
	{
		::MessageBox(nullptr, _T("OnTick() - FAILED"), 0, 0);
		return;
	}

	// 타이머 시작.
	mEngine.GetTimer().BeginTimer();

	// Initialization
	start();

	// Input Event
	mEngine.GetInput().Update();

	// GameLogic
	update();
	lateUpdate();

	// Scene Rendering
	preRender();
	render();
	renderGUI();
	postRender();

	// 타이머 종료.
	mEngine.GetTimer().EndTimer();
}

void EnginePlayer::loadScene()
{
	auto camera = mEngine.CreateCamera("Main Camera");
	camera->GetTransform()->SetPosition(D3DXVECTOR3(0.f, 0.f, -5.0f));
	camera->AddComponent<CameraController>();

	auto light = mEngine.CreateLight("Directional Light", D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL);
	light->GetTransform()->SetRotation(D3DXVECTOR3(10, -10, 10));

	auto go = mEngine.CreateCube("Cube");
	go->GetTransform()->SetPosition(D3DXVECTOR3(0, 0, 0));
	go->GetComponent<MeshRenderer>()->SetMaterialHashKey(0, HashKey::Material::Crate);
	go->AddComponent<Rotator>();

	auto go2 = mEngine.CreateCube("Cube2");
	go2->GetTransform()->SetPosition(D3DXVECTOR3(0, 0, 5));
	go2->GetTransform()->SetParent(go->GetTransform());

	auto doomguy = mEngine.CreateQuad("Doom Guy");
	doomguy->GetTransform()->SetPosition(D3DXVECTOR3(2, 0, 5));
	doomguy->GetComponent<MeshRenderer>()->SetMaterialHashKey(0, HashKey::Material::DoomGuy);

	auto cacodoom = mEngine.CreateQuad("Caco Doom");
	cacodoom->GetTransform()->SetPosition(D3DXVECTOR3(2, 0, 0));
	cacodoom->GetComponent<MeshRenderer>()->SetMaterialHashKey(0, HashKey::Material::CacoDoom);

	auto fire = mEngine.CreateSphere("Fire");
	fire->GetTransform()->SetPosition(D3DXVECTOR3(-2, 0, 0));
	fire->GetComponent<MeshRenderer>()->SetMaterialHashKey(0, HashKey::Material::Fire);

	auto ice = mEngine.CreateSphere("Ice");
	ice->GetTransform()->SetPosition(D3DXVECTOR3(-4, 0, 0));
	ice->GetComponent<MeshRenderer>()->SetMaterialHashKey(0, HashKey::Material::Ice);

	auto sprite = mEngine.CreateImage("DoomGuy Image", HashKey::Texture::DoomGuy);
	sprite->GetTransform()->SetPosition(D3DXVECTOR3(10, 50, 0));
	sprite->GetTransform()->SetScale(D3DXVECTOR3(0.1f, 0.1f, 0.f));

	auto FPStext = mEngine.CreateText("FPS Text");
	FPStext->AddComponent<PerformanceText>();
}

void EnginePlayer::start()
{
	for (auto behavior : mEngine.GetBehaviors())
	{
		// 비활성화 건너뛰기.
		if (!behavior->GetGameObject()->IsActive())
		{
			continue;
		}

		if (!behavior->IsStart())
		{
			behavior->Start();
			behavior->SetStart(true);
		}
	}
}

void EnginePlayer::update()
{
	for (auto behavior : mEngine.GetBehaviors())
	{
		// 비활성화 건너뛰기.
		if (!behavior->GetGameObject()->IsActive())
		{
			continue;
		}

		behavior->Update();
	}
}

void EnginePlayer::lateUpdate()
{
	for (auto behavior : mEngine.GetBehaviors())
	{
		// 비활성화 건너뛰기.
		if (!behavior->GetGameObject()->IsActive())
		{
			continue;
		}

		behavior->LateUpdate();
	}
}

void EnginePlayer::preRender()
{
	// 메쉬 정렬.
	sortMeshRenderer();

	// 카메라.
	updateCamera();

	// 라이트.
	updateLights();

	// 배경 지우기 / 렌더 시작.
	if (d3d::Var::Device)
	{
		d3d::Var::Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, d3d::GRAY, 1.f, 0);
		d3d::Var::Device->BeginScene();
	}
}

void EnginePlayer::render()
{
	if (d3d::Var::Device)
	{
		// 불투명 렌더링.
		d3d::Var::Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		for (auto it = mEngine.MeshRendererBegin(); it != mCutoutRenderBeginIt; ++it)
		{
			if (!(*it)->GetGameObject()->IsActive())
			{
				continue;
			}

			auto matWorld = (*it)->GetTransform()->GetMatrix();
			d3d::Var::Device->SetTransform(D3DTS_WORLD, &matWorld);
			(*it)->Render(d3d::Var::Device);
		}

		// 투명 렌더링.
		d3d::Var::Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		for (auto it = mCutoutRenderBeginIt; it != mEngine.MeshRendererEnd(); ++it)
		{
			if (!(*it)->GetGameObject()->IsActive())
			{
				continue;
			}

			auto matWorld = (*it)->GetTransform()->GetMatrix();
			d3d::Var::Device->SetTransform(D3DTS_WORLD, &matWorld);
			(*it)->Render(d3d::Var::Device);
		}
	}
}

void EnginePlayer::renderGUI()
{
	if (d3d::Var::Device)
	{
		for (auto ui : mEngine.GetUIs())
		{
			if (!ui->GetGameObject()->IsActive())
			{
				continue;
			}

			ui->Draw();
		}
	}
}

void EnginePlayer::postRender()
{
	// 렌더 마무리 / 백 버퍼 스왑.
	if (d3d::Var::Device)
	{
		d3d::Var::Device->EndScene();
		d3d::Var::Device->Present(NULL, NULL, NULL, NULL);
	}
}

void EnginePlayer::setRenderPipeline()
{
	IDirect3DDevice9* Device = d3d::Var::Device;

	// 기본.
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Device->SetRenderState(D3DRS_ZENABLE, true);
	Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	// 라이트.
	Device->SetRenderState(D3DRS_LIGHTING, true);
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);	// 법선 정리.
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);		// 정반사광.	

	// 텍스처 필터링.
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	Device->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

	// 밉맵
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// 셰이드 과정에서 난반사 컬러로 알파를 계산.
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	// 알파 채널에서 알파를 얻는다.
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void EnginePlayer::sortMeshRenderer()
{
	// 투명, 불투명 나누기.
	mCutoutRenderBeginIt = std::partition(mEngine.MeshRendererBegin(), mEngine.MeshRendererEnd(),
		[](MeshRenderer* mr)
		{
			bool flag = false;
			for (auto key : mr->GetMaterialHashKeys())
			{
				auto mtrl = GameEngine::MaterialResources[key].get();
				if (mtrl->GetRenderingMode() == RenderingMode::Opaque)
				{
					flag = true;
					break;
				}
			}

			return flag;
		});

	// 카메라와 거리 차이에 따라 정렬.
	auto camPos = mEngine.GetMainCamera()->GetTransform()->GetPosition();
	std::sort(mCutoutRenderBeginIt, mEngine.MeshRendererEnd(),
		[&](MeshRenderer* a, MeshRenderer* b)
		{
			auto gapA = camPos - a->GetTransform()->GetPosition();
			auto gapB = camPos - b->GetTransform()->GetPosition();
			return D3DXVec3LengthSq(&gapA) > D3DXVec3LengthSq(&gapB);
		});
}

void EnginePlayer::updateCamera()
{
	d3d::Var::Device->SetTransform(D3DTS_VIEW, &mEngine.GetMainCamera()->GetViewMatrix());
	d3d::Var::Device->SetTransform(
		D3DTS_PROJECTION,
		&mEngine.GetMainCamera()->GetProjectionMatrix(wndplayer::Var::Width, wndplayer::Var::Height));
}

void EnginePlayer::updateLights()
{
	for (auto light : mEngine.GetLights())
	{
		auto index = light->GetIndex();
		d3d::Var::Device->SetLight(index, &light->GetLight());
		d3d::Var::Device->LightEnable(index, light->GetGameObject()->IsActive());
		light->UpdateTransform();
	}
}
