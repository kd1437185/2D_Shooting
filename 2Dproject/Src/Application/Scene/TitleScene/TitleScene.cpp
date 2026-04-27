#include "TitleScene.h"

#include "../SceneManager.h"

void TitleScene::Init()
{
	m_BackTex.Load("Texture/TitleScene/title.png");
}

void TitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}

	// îwåi
	m_BackMat = Math::Matrix::CreateTranslation(0, 0, 0);
}

void TitleScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);
}

void TitleScene::Release()
{
	m_BackTex.Release();
}
