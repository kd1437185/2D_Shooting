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
	m_currentScene->Draw();
}

void SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
}

void SceneManager::Release()
{
	if (m_currentScene)
	{
		m_currentScene->Release();
		m_currentScene = nullptr;
	}
}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	// 旧シーンを解放
	if (m_currentScene)
	{
		m_currentScene->Release();
		m_currentScene = nullptr;
	}

	// ①次のシーンを作成し、②フラグを更新する

	// ①新しいシーンを生成して初期化
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
	default:(false && "Unknown SceneType");
		return;
	}

	// 初期化（コンストラクタでInitしないなら）
	m_currentScene->Init();

	// ②フラグ更新
	m_currentSceneType = _sceneType;
	m_nextSceneType = _sceneType;
}