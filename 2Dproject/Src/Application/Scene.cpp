#include "main.h"
#include "Scene.h"

void Scene::Draw2D()
{
	m_sceneManager.Draw();
}

void Scene::Update()
{
	m_sceneManager.Update();
}

void Scene::Init()
{
	m_sceneManager.Init();
}

void Scene::Release()
{
	m_sceneManager.Release();
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);

		m_sceneManager.ImGuiUpdate();
	}
	ImGui::End();
}