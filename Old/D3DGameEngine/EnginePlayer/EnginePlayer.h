#pragma once

#include <algorithm>
#include <vector>

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
	void setRenderPipeline();
	void sortMeshRenderer();
	void updateCamera();
	void updateLights();

private:
	bool mbInit;

	engine::GameEngine mEngine;

	std::vector<engine::MeshRenderer*>::iterator mCutoutRenderBeginIt;
};

