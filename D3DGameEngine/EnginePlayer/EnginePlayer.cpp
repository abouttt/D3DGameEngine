#include "EnginePlayer.h"
#include "WindowsPlayer.h"

#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"

EnginePlayer::EnginePlayer()
    : mbInit(false)
	, mEngine()
{}

bool EnginePlayer::Init()
{
	// �̹� �ʱ�ȭ �Ǿ��ٸ� �������� �ʴ´�.
	if (mbInit)
	{
		::MessageBox(nullptr, "EnginePlayer - Init() : Already Init", "Error", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	if (!mEngine.Init(wndplayer::gInstance, wndplayer::gWndHandler))
	{
		::MessageBox(nullptr, "EnginePlayer - Init() : GameEngine Init Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

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

	// ���� ���� ����.
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

	// ���� ���� ����.
	mEngine.GetTimer().EndTimer();
}

void EnginePlayer::loadScene()
{
	auto camera = mEngine.CreateCamera("MainCamera");
	camera->GetTransform()->SetPosition(D3DXVECTOR3(0.f, 0.f, 0.f));
}

void EnginePlayer::start()
{
}

void EnginePlayer::update()
{
}

void EnginePlayer::lateUpdate()
{
}

void EnginePlayer::preRender()
{
	// ī�޶�.
	updateCameraTransform();

	// ��� ����� / ���� ����.
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

	}
}

void EnginePlayer::postRender()
{
	// ���� ������ / �� ���� ����.
	if (d3d::gDevice)
	{
		d3d::gDevice->EndScene();
		d3d::gDevice->Present(NULL, NULL, NULL, NULL);
	}
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
