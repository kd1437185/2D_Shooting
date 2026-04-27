#pragma once

class BaseScene;

// 全てのシーンを管理するクラス
class SceneManager
{
public:

	enum SceneType
	{
		Title,
		Game
	};

	// Updateの前に実行するUpdate
	void PreUpdate();

	void Update();
	void Draw();

	// 外部から次のシーンをセットする関数
	// ※この関数ではシーンは切り替わらない。
	void SetNextScene(SceneType _nextScene)
	{
		m_nextSceneType = _nextScene;
	}

	// 現在のシーンを取得する関数
	SceneType GetCurrentScene() const
	{
		return m_currentSceneType;
	}

private:

	// 初期化や解放は自分でする
	void Init();
	void Release();

	// シーン切替の関数
	void ChangeScene(SceneType _sceneType);

	// 現在のシーンを管理するポインタ変数
	std::shared_ptr<BaseScene> m_currentScene;

	// 現在のシーンを管理するフラグ変数
	SceneType m_currentSceneType = SceneType::Title;

	// 次のシーンを管理するフラグ変数
	SceneType m_nextSceneType = m_currentSceneType;

// シングルトンパターン
private:

	// 外で変数宣言できない
	SceneManager() { Init(); }
	~SceneManager() { Release(); }

public:

	static SceneManager& Instance()
	{
		// 自分で自分を作る
		static SceneManager instance;
		return instance;
	}
};