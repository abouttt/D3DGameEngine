#pragma once

#include "GameEngine.h"

class EnginePlayer
{
public:
	EnginePlayer();

public:
	bool Init();

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
	void onDestroy();

private:
	void initRenderPipeline();
	void updateCameraTransform();
	void updateLights();

private:
	bool mbInit;

	engine::GameEngine mEngine;
};

