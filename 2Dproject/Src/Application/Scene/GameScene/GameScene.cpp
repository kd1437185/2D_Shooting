#include "GameScene.h"

#include "../SceneManager.h"

void GameScene::Init()
{
	m_BackTex.Load("Texture/GameScene/game.png");
}

void GameScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}

	// îwåi
	m_BackMat = Math::Matrix::CreateTranslation(0, 0, 0);
}

void GameScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);
}

void GameScene::Release()
{
	m_BackTex.Release();
}
