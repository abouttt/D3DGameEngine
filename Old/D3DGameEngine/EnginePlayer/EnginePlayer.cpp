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
	// �̹� �ʱ�ȭ �Ǿ��ٸ� �������� �ʴ´�.
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

	// Ÿ�̸� ����.
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

	// Ÿ�̸� ����.
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
		// ��Ȱ��ȭ �ǳʶٱ�.
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
		// ��Ȱ��ȭ �ǳʶٱ�.
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
		// ��Ȱ��ȭ �ǳʶٱ�.
		if (!behavior->GetGameObject()->IsActive())
		{
			continue;
		}

		behavior->LateUpdate();
	}
}

void EnginePlayer::preRender()
{
	// �޽� ����.
	sortMeshRenderer();

	// ī�޶�.
	updateCamera();

	// ����Ʈ.
	updateLights();

	// ��� ����� / ���� ����.
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
		// ������ ������.
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

		// ���� ������.
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
	// ���� ������ / �� ���� ����.
	if (d3d::Var::Device)
	{
		d3d::Var::Device->EndScene();
		d3d::Var::Device->Present(NULL, NULL, NULL, NULL);
	}
}

void EnginePlayer::setRenderPipeline()
{
	IDirect3DDevice9* Device = d3d::Var::Device;

	// �⺻.
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Device->SetRenderState(D3DRS_ZENABLE, true);
	Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	// ����Ʈ.
	Device->SetRenderState(D3DRS_LIGHTING, true);
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);	// ���� ����.
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);		// ���ݻ籤.	

	// �ؽ�ó ���͸�.
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	Device->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

	// �Ӹ�
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// ���̵� �������� ���ݻ� �÷��� ���ĸ� ���.
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	// ���� ä�ο��� ���ĸ� ��´�.
	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void EnginePlayer::sortMeshRenderer()
{
	// ����, ������ ������.
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

	// ī�޶�� �Ÿ� ���̿� ���� ����.
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
