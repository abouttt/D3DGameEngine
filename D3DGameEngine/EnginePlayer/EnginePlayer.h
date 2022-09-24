#pragma once

#include "GameEngine.h"

class EnginePlayer
{
public:
	EnginePlayer();

public:
	void Init();

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

private:
	bool mbInit;

	engine::GameEngine mEngine;
};

