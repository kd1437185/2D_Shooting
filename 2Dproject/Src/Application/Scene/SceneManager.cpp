#include "SceneManager.h"

// 各シーンのヘッダーをインクルード
#include "TitleScene/TitleScene.h"
#include"GameScene/GameScene.h"

void SceneManager::PreUpdate()
{
	// シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}
}

void SceneManager::Update()
{
	// ポリモーフィズム
	// 同じ関数名であっても、呼び出すオブジェクトによって処理内容が変わること
	m_currentScene->Update();
}

void SceneManager::Draw()
{
	// ポリモーフィズム
	// 同じ関数名であっても、呼び出すオブジェクトによって処理内容が変わること
	m_currentScene->Draw();
}

void SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
}

void SceneManager::Release()
{
	m_currentScene->Release();
}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	// ①次のシーンを作成し、②フラグを更新する

	// ①
	switch (_sceneType)
	{
	case SceneType::Title:
		// アップキャスト
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::Game:
		// アップキャスト
		m_currentScene = std::make_shared<GameScene>();
		break;
	}

	// 初期化（コンストラクタでInitしないなら）


	// ②
	m_currentSceneType = _sceneType;
}