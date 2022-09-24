#include "EnginePlayer.h"
#include "WindowsPlayer.h"

EnginePlayer::EnginePlayer()
    : mbInit(false)
	, mEngine()
{
}

void EnginePlayer::Init()
{
	// �̹� �ʱ�ȭ �Ǿ��ٸ� �������� �ʴ´�.
	if (mbInit)
	{
		return;
	}

	mbInit = true;
}

void EnginePlayer::OnTick()
{
	if (!mbInit)
	{
		::MessageBox(nullptr, "EnginePlayer - OnTick() : No Init EnginePlayer", "Error", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// ���� ���� ����.
	//mEngine.GetTimer().BeginTimer();

	// Initialization
	start();

	// Input Event
	//mEngine.GetInput().Update();

	// GameLogic
	update();
	lateUpdate();

	// Scene Rendering
	preRender();
	render();
	renderGUI();
	postRender();

	// ���� ���� ����.
	//mEngine.GetTimer().EndTimer();
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
