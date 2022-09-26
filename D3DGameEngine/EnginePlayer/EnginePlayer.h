#pragma once

#include "GameEngine.h"

class EnginePlayer
{
public:
	EnginePlayer();

public:
	bool Init();

	// ������ �̺�Ʈ ó��.
	void OnTick();

private: //���� �Լ�.
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

