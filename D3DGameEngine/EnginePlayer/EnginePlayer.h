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

private: 
	void loadScene();

private: //���� �Լ�.
	void awake();
	void onEnable();
	void start();
	void update();
	void lateUpdate();
	void preRender();
	void render();
	void renderGUI();
	void postRender();
	void onDisable();
	void onDestroy();

private:
	void initRenderPipeline();
	void updateCameraTransform();
	void updateLights();

private:
	bool mbInit;

	engine::GameEngine mEngine;
};

