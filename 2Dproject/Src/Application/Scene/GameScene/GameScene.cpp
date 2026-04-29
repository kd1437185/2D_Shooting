#include "GameScene.h"
#include "../../Object/Player/Player.h"

#include "../SceneManager.h"

void GameScene::Init()
{
	m_BackTex.Load("Texture/GameScene/game.png");

	// ƒvƒŒƒCƒ„[
	m_player = std::make_shared<Player>();
	m_player->Init();
}

void GameScene::Update()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}

	m_player->Update();

	// ”wŒi
	m_BackMat = Math::Matrix::CreateTranslation(0, 0, 0);
}

void GameScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	m_player->Draw();
}

void GameScene::Release()
{
	m_BackTex.Release();
	m_player->Release();
}
