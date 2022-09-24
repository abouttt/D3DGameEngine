#pragma once

#include "GameEngine.h"

class EnginePlayer
{
public:
	EnginePlayer();

public:
	void Init();

	// 윈도우 이벤트 처리.
	void OnTick();

private: //루프 함수.
	void loadScene();
	void start();
	void update();
	void lateUpdate();
	void preRender();
	void render();
	void renderGUI();
	void postRender();

private:
	bool mbInit;

	engine::GameEngine mEngine;
};

