#include "EnginePlayer.h"
#include "WindowsPlayer.h"

EnginePlayer::EnginePlayer()
    : mbInit(false)
	, mEngine()
{
}

bool EnginePlayer::Init()
{
	// 이미 초기화 되었다면 진행하지 않는다.
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
}

void EnginePlayer::render()
{
}

void EnginePlayer::renderGUI()
{
}

void EnginePlayer::postRender()
{
}
