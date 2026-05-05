#include "GameScene.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/MobEnemy/MobEnemy.h"
#include "../../Collision/CollisionManager.h"
#include "../../Object/Bullet/Bullet.h"
#include "../SceneManager.h"
#include "../../Score/ScoreManager.h"
#include "../../AppConst.h"

void GameScene::Init()
{
	// 背景
	m_BackTex.Load("Texture/GameScene/game.png");
	m_BackMat = Math::Matrix::CreateTranslation(0, 0, 0);

	// スコア
	ScoreManager::Instance().Init();

	// プレイヤー
	m_player = std::make_shared<Player>();
	m_player->Init();

	// 敵を縦一列に複数生成
	// 画面中央に揃えるためにオフセットを計算
	float totalHeight = AppConst::ENEMY_SPACE * (AppConst::ENEMY_COUNT - 1);
	float startY = totalHeight / 2.0f;	//上端のY座標

	for (int i = 0; i < AppConst::ENEMY_COUNT; ++i)
	{
		auto enemy = std::make_shared<MobEnemy>();
		enemy->Init();

		// 初期位置を設定(右端から少し外側、縦に均等配置)
		enemy->SetPos({ AppConst::SCREEN_HALF_W + AppConst::ENEMY_SIZE,startY - AppConst::ENEMY_SPACE * i });

		m_Enemies.push_back(enemy);
	}
}

void GameScene::Update()
{
	bool nowSpace = GetAsyncKeyState(VK_SPACE) & 0x8000;
	if (nowSpace && !m_prevSpace)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
	m_prevSpace = nowSpace;

	// プレイヤー
	if (m_player)
	{
		m_player->Update();
	}

	// モブエネミー
	for (auto& e : m_Enemies)
	{
		{
			if (e && e->IsAlive()) e->Update(); // IsAlive() チェック追加
		}
	}

	// 当たり判定
	if (m_player)
	{
		auto& bullets = m_player->GetBullets();
		CollisionManager::CheckBulletsVsEnemies(bullets, m_Enemies);
	}

}

void GameScene::Draw()
{
	// 背景
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	// プレイヤー
	if (m_player)
	{
		m_player->Draw();
	}

	// モブエネミー
	for (auto& e : m_Enemies)
	{
		if (e && e->IsAlive()) e->Draw(); // IsAlive() チェック追加
	}

	// スコア
	ScoreManager::Instance().Draw();

}

void GameScene::Release()
{
	m_BackTex.Release();

	// スコア
	ScoreManager::Instance().Release();

	if (m_player)
	{
		m_player->Release();
		m_player = nullptr;
	}

	for (auto& e : m_Enemies)
	{
		if (e)
		{
			e->Release();
		}
	}
	m_Enemies.clear();

}
