#include "GameScene.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/MobEnemy/MobEnemy.h"
#include "../../Object/Enemy/ShooterEnemy/ShooterEnemy.h"
#include "../../Object/Enemy/TankEnemy/TankEnemy.h"
#include "../../Object/Enemy/Boss/Boss.h"
#include "../../Collision/CollisionManager.h"
#include "../../Object/Bullet/Bullet.h"
#include "../SceneManager.h"
#include "../../Score/ScoreManager.h"
#include "../../AppConst.h"
#include "../../Wave/WaveManager.h"
#include "../../Health/HealthManager.h"

void GameScene::Init()
{
	// 背景
	ScrollBackground::Instance().Init();

	// スコア
	ScoreManager::Instance().Init();

	// ウェーブ
	WaveManager::Instance().Init();

	// プレイヤー（入場演出から開始）
	m_player = std::make_shared<Player>();
	m_player->Init();
	m_player->StartEnter(); // 入場開始

	// MobEnemyをあらかじめ ENEMY_MAX 体プールとして生成
	for (int i = 0; i < AppConst::ENEMY_MAX; i++)
	{
		auto enemy = std::make_shared<MobEnemy>();
		enemy->Init();
		m_Enemies.push_back(enemy);
	}

	// タイマーをすぐ1体出るようにする
	m_spawnTimer = AppConst::ENEMY_SPAWN_INTERVAL;
	m_spawnedCount = 0; // 追加
	m_usedY.fill(false);

	// ShooterEnemy もプールとして生成
	for (int i = 0; i < AppConst::SHOOTER_MAX; i++)
	{
		auto enemy = std::make_shared<ShooterEnemy>();
		enemy->Init();
		m_Enemies.push_back(enemy);
	}

	m_shooterSpawnTimer = AppConst::ENEMY_SPAWN_INTERVAL;
	m_shooterSpawnedCount = 0;
	m_usedY2.fill(false);

	// TankEnemy をプールとして生成
	for (int i = 0; i < AppConst::TANK_MAX; i++)
	{
		auto enemy = std::make_shared<TankEnemy>();
		enemy->Init();
		m_Enemies.push_back(enemy);
	}

	m_tankSpawnTimer = AppConst::TANK_SPAWN_INTERVAL;
	m_tankSpawnedCount = 0;

	// Boss を生成（非アクティブ状態）
	m_boss = std::make_shared<Boss>();
	m_boss->Init();

	HealthManager::Instance().Init();

}

void GameScene::Update()
{
	bool nowSpace = GetAsyncKeyState(VK_SPACE) & 0x8000;
	if (nowSpace && !m_prevSpace)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
	m_prevSpace = nowSpace;

	// 背景
	ScrollBackground::Instance().Update();

	// 入場中は敵スポーン・当たり判定をしない
	if (m_player && m_player->IsEntering())
	{
		m_player->Update();
		return;
	}

	// ウェーブクリア確認
	if (WaveManager::Instance().IsWaveClear())
	{
		WaveManager::Instance().ResetWaveClear();

		// 次のウェーブ用にカウンターをリセット
		m_spawnedCount = 0;
		m_spawnTimer = AppConst::ENEMY_SPAWN_INTERVAL;
		m_shooterSpawnedCount = 0;
		m_shooterSpawnTimer = AppConst::ENEMY_SPAWN_INTERVAL;
		m_tankSpawnedCount = 0;
		m_tankSpawnTimer = AppConst::TANK_SPAWN_INTERVAL;
		m_usedY.fill(false);
		m_usedY2.fill(false);
	}

	// MobEnemy ウェーブのときだけスポーン
	if (WaveManager::Instance().GetCurrentWave() == WaveType::MobEnemy)
	{
		// 合計 ENEMY_MAX 体出し切ったらスポーンしない
		if (m_spawnedCount < AppConst::ENEMY_MAX)
		{
			m_spawnTimer++;
			if (m_spawnTimer >= AppConst::ENEMY_SPAWN_INTERVAL)
			{
				m_spawnTimer = 0;
				SpawnEnemy();
			}
		}
	}

	// ShooterEnemy ウェーブのときだけスポーン
	if (WaveManager::Instance().GetCurrentWave() == WaveType::Enemy2)
	{
		if (m_shooterSpawnedCount < AppConst::SHOOTER_MAX)
		{
			m_shooterSpawnTimer++;
			if (m_shooterSpawnTimer >= AppConst::ENEMY_SPAWN_INTERVAL)
			{
				m_shooterSpawnTimer = 0;
				SpawnShooterEnemy();
			}
		}
	}

	// TankEnemy ウェーブのときだけスポーン
	if (WaveManager::Instance().GetCurrentWave() == WaveType::Enemy3)
	{
		if (m_tankSpawnedCount < AppConst::TANK_MAX)
		{
			m_tankSpawnTimer++;
			if (m_tankSpawnTimer >= AppConst::TANK_SPAWN_INTERVAL)
			{
				m_tankSpawnTimer = 0;
				SpawnTankEnemy();
			}
		}
	}

	// Boss ウェーブのときスポーン（最初の1回だけ）
	if (WaveManager::Instance().GetCurrentWave() == WaveType::Boss)
	{
		if (m_boss && !m_boss->IsAlive() && m_boss->GetPhase() != Boss::Phase::Death
			&& m_boss->GetPhase() != Boss::Phase::EnterFromLeft)
		{
			m_boss->Spawn();
		}
	}

	if (m_boss && m_boss->IsAlive()) m_boss->Update();

	

	// プレイヤー
	if (m_player) m_player->Update();

	// 敵
	for (auto& e : m_Enemies)
	{
		if (e && e->IsAlive()) e->Update();
	}

	// 当たり判定
	if (m_player)
	{
		auto& bullets = m_player->GetBullets();
		CollisionManager::CheckBulletsVsEnemies(bullets, m_Enemies);
	}

	// 当たり判定（弾 vs ボス）
	if (m_player && m_boss)
	{
		auto& bullets = m_player->GetBullets();
		CollisionManager::CheckBulletsVsBoss(bullets, m_boss);
	}

	// 倒されたMobEnemyのY座標を解放
	for (int i = 0; i < (int)m_Enemies.size(); i++)
	{
		auto mob = std::dynamic_pointer_cast<MobEnemy>(m_Enemies[i]);
		if (!mob) continue;
		if (mob->IsAlive()) continue;
		if (mob->IsYReleased()) continue; // 解放済みならスキップ

		for (int j = 0; j < 5; j++)
		{
			if (m_usedY[j] &&
				fabsf(mob->GetPos().y - AppConst::ENEMY_Y_LIST[j]) < 1.0f)
			{
				m_usedY[j] = false;
				mob->SetYReleased(true); // 解放済みにする
				break;
			}
		}
	}

	// 倒された ShooterEnemy のY座標を解放
	for (int i = 0; i < (int)m_Enemies.size(); i++)
	{
		auto shooter = std::dynamic_pointer_cast<ShooterEnemy>(m_Enemies[i]);
		if (!shooter) continue;
		if (shooter->IsAlive()) continue;
		if (shooter->IsYReleased()) continue;

		for (int j = 0; j < 5; j++)
		{
			if (m_usedY2[j] &&
				fabsf(shooter->GetPos().y - AppConst::ENEMY_Y_LIST[j]) < 1.0f)
			{
				m_usedY2[j] = false;
				shooter->SetYReleased(true);
				break;
			}
		}
	}

	// Uキーで弾を強化（テスト用）
	static bool prevU = false;
	bool nowU = GetAsyncKeyState('U') & 0x8000;
	if (nowU && !prevU)
	{
		m_player->UpgradeBullet();
	}
	prevU = nowU;

}

void GameScene::SpawnEnemy()
{
	// 非アクティブな敵を探す
	std::shared_ptr<MobEnemy> target = nullptr;
	for (auto& e : m_Enemies)
	{
		if (e && !e->IsAlive())
		{
			target = std::dynamic_pointer_cast<MobEnemy>(e);
			if (target) break;
		}
	}
	if (!target) return;

	// 使われていないY座標インデックスをランダムに選ぶ
	std::vector<int> availableY;
	for (int i = 0; i < 5; i++)
	{
		if (!m_usedY[i]) availableY.push_back(i);
	}
	if (availableY.empty()) return;

	int randIdx = availableY[rand() % availableY.size()];
	m_usedY[randIdx] = true;

	float spawnX = AppConst::SCREEN_HALF_W + AppConst::ENEMY_SCALED_W;
	float spawnY = AppConst::ENEMY_Y_LIST[randIdx];
	target->Spawn(spawnX, spawnY);

	m_spawnedCount++; // 出現数をカウント
}

void GameScene::SpawnShooterEnemy()
{
	std::shared_ptr<ShooterEnemy> target = nullptr;
	for (auto& e : m_Enemies)
	{
		if (e && !e->IsAlive())
		{
			target = std::dynamic_pointer_cast<ShooterEnemy>(e);
			if (target) break;
		}
	}
	if (!target) return;

	std::vector<int> availableY;
	for (int i = 0; i < 5; i++)
	{
		if (!m_usedY2[i]) availableY.push_back(i);
	}
	if (availableY.empty()) return;

	int randIdx = availableY[rand() % availableY.size()];
	m_usedY2[randIdx] = true;

	float spawnX = AppConst::SCREEN_HALF_W + AppConst::SHOOTER_SCALED_W;
	float spawnY = AppConst::ENEMY_Y_LIST[randIdx];
	target->Spawn(spawnX, spawnY);

	m_shooterSpawnedCount++;
}

void GameScene::SpawnTankEnemy()
{
	// 非アクティブな TankEnemy を探す
	std::shared_ptr<TankEnemy> target = nullptr;
	for (auto& e : m_Enemies)
	{
		if (e && !e->IsAlive())
		{
			target = std::dynamic_pointer_cast<TankEnemy>(e);
			if (target) break;
		}
	}
	if (!target) return;

	// 順番に固定X・Y座標で出現
	float spawnX = AppConst::TANK_X_LIST[m_tankSpawnedCount];
	float stopY = AppConst::TANK_STOP_Y_LIST[m_tankSpawnedCount];
	target->Spawn(spawnX, stopY);

	m_tankSpawnedCount++;
}

void GameScene::Draw()
{
	// 背景
	ScrollBackground::Instance().Draw();

	// ボス
	if (m_boss && m_boss->IsAlive()) m_boss->Draw();

	// モブエネミー
	for (auto& e : m_Enemies)
	{
		if (e && e->IsAlive()) e->Draw(); // IsAlive() チェック追加
	}

	// プレイヤー
	if (m_player)
	{
		m_player->Draw();
	}

	// スコア
	ScoreManager::Instance().Draw();

	// 体力バー
	HealthManager::Instance().Draw();

}

void GameScene::Release()
{

	// スコア
	ScoreManager::Instance().Release();

	// 体力バー
	HealthManager::Instance().Release();

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

	if (m_boss)
	{
		m_boss->Release();
		m_boss = nullptr;
	}

}
