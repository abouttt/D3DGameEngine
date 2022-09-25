#include "EnginePlayer.h"
#include "WindowsPlayer.h"

// GameObject
#include "Behavior.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "Transform.h"
#include "UI.h"
#include "Text.h"

// Behavior Component
#include "PerformanceText.h"

EnginePlayer::EnginePlayer()
    : mbInit(false)
	, mEngine()
{}

bool EnginePlayer::Init()
{
	// 이미 초기화 되었다면 진행하지 않는다.
	if (mbInit)
	{
		::MessageBox(nullptr, "EnginePlayer - Init() : Already Init", "Error", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// 다이렉트 디바이스 체크.
	if (!d3d::gDevice)
	{
		::MessageBox(nullptr, "EnginePlayer - Init() : DirectX device is null", "Error", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// 게임 엔진 초기화.
	if (!mEngine.Init(wndplayer::gInstance, wndplayer::gWndHandler))
	{
		::MessageBox(nullptr, "EnginePlayer - Init() : GameEngine Init Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// 씬 오브젝트 로드.
	loadScene();

	mbInit = true;
	return true;
}

void EnginePlayer::OnTick()
{
	if (!mbInit)
	{
		::MessageBox(nullptr, "EnginePlayer - OnTick() : No Init EnginePlayer", "Error", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 성능 측정 시작.
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

	// 성능 측정 종료.
	mEngine.GetTimer().EndTimer();
}

void EnginePlayer::loadScene()
{
	auto camera = mEngine.CreateCamera("MainCamera");
	camera->GetTransform()->SetPosition(D3DXVECTOR3(0.f, 0.f, 0.f));

	auto light = mEngine.CreateLight("DirectionalLight");
	light->GetTransform()->SetRotation(D3DXVECTOR3(10, -10, 10));

	auto FPStext = mEngine.CreateText("FPSText");
	FPStext->GetGameObject()->AddComponent<PerformanceText>();
}

void EnginePlayer::start()
{
	while (!mEngine.GetBehaviorStartQueue().empty())
	{
		mEngine.GetBehaviorStartQueue().front()->Start();
		mEngine.GetBehaviorStartQueue().pop();
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
	// 카메라.
	updateCameraTransform();

	// 라이트.
	updateLights();

	// 배경 지우기 / 렌더 시작.
	if (d3d::gDevice)
	{
		d3d::gDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, d3d::BLACK, 1.f, 0);
		d3d::gDevice->BeginScene();
	}
}

void EnginePlayer::render()
{
	if (d3d::gDevice)
	{

	}
}

void EnginePlayer::renderGUI()
{
	if (d3d::gDevice)
	{
		for (auto ui : mEngine.GetUIComponents())
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
	if (d3d::gDevice)
	{
		d3d::gDevice->EndScene();
		d3d::gDevice->Present(NULL, NULL, NULL, NULL);
	}
}

void EnginePlayer::initRenderPipeline()
{
	IDirect3DDevice9* d3dDevice = d3d::gDevice;

	// 기본.
	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	d3dDevice->SetRenderState(D3DRS_ZENABLE, true);
	d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	// 라이트.
	d3dDevice->SetRenderState(D3DRS_LIGHTING, true);
	d3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);	// 법선 정리.
	d3dDevice->SetRenderState(D3DRS_SPECULARENABLE, true);		// 정반사광.	

	// 텍스처 필터링.
	d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	d3dDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

	// 밉맵
	d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// 셰이드 과정에서 난반사 컬러로 알파를 계산.
	d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	// 알파 채널에서 알파를 얻는다.
	d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void EnginePlayer::updateCameraTransform()
{
	if (!mEngine.GetMainCamera())
	{
		::MessageBox(nullptr, "EnginePlayer - updateCameraTransform() : No exist main camera", "Error", MB_ICONEXCLAMATION | MB_OK);
	}

	d3d::gDevice->SetTransform(D3DTS_VIEW, &mEngine.GetMainCamera()->GetViewMatrix());
	d3d::gDevice->SetTransform(
		D3DTS_PROJECTION,
		&mEngine.GetMainCamera()->GetProjectionMatrix(wndplayer::gWidth, wndplayer::gHeight));
}

void EnginePlayer::updateLights()
{
	for (auto light : mEngine.GetLights())
	{
		auto index = light->GetIndex();
		d3d::gDevice->SetLight(index, &light->GetSource());
		d3d::gDevice->LightEnable(index, light->GetGameObject()->IsActive());
		light->UpdateTransform();
	}
}
