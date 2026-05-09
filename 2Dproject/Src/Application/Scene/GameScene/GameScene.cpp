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
#include "../../Result/ResultManager.h"
#include "../../Effect/EffectManager.h"

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

	// 敵プールをクリアしてから再生成
	m_Enemies.clear();

	// MobEnemyをあらかじめ ENEMY_MAX 体プールとして生成
	for (int i = 0; i < AppConst::MOB_MAX_WAVE4; i++)
	{
		auto enemy = std::make_shared<MobEnemy>();
		enemy->Init();
		m_Enemies.push_back(enemy);
	}
	m_spawnTimer = AppConst::ENEMY_SPAWN_INTERVAL;
	m_spawnedCount = 0;
	m_mobMax = AppConst::MOB_MAX_WAVE1; // フェーズ1は8体

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

	ResultManager::Instance().Init();

	EffectManager::Instance().Init();

	// プレイヤーにターゲットリストを渡す
	m_player->SetTargetLists(&m_Enemies, reinterpret_cast<std::shared_ptr<BaseObject>*>(&m_boss));
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

		m_spawnedCount = 0;
		m_spawnTimer = AppConst::ENEMY_SPAWN_INTERVAL;
		m_shooterSpawnedCount = 0;
		m_shooterSpawnTimer = AppConst::ENEMY_SPAWN_INTERVAL;
		m_tankSpawnedCount = 0;
		m_tankSpawnTimer = AppConst::TANK_SPAWN_INTERVAL;
		m_usedY.fill(false);
		m_usedY2.fill(false);

		// ウェーブに応じてMobEnemyの数を変更
		int waveIndex = WaveManager::Instance().GetWaveIndex();
		if (waveIndex == 3) // 4周目のMobEnemy
		{
			m_mobMax = AppConst::MOB_MAX_WAVE4;
		}
	}

	// MobEnemy ウェーブのときだけスポーン
	if (WaveManager::Instance().GetCurrentWave() == WaveType::MobEnemy)
	{
		if (m_spawnedCount < m_mobMax)
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

	// 左から来たボスの死亡アニメ完了でリザルト表示
	if (m_boss && m_boss->IsDeathFinished() && m_boss->IsFromLeft())
	{
		if (m_player)
		{
			for (auto& b : m_player->GetBullets())
			{
				if (b) b->SetAlive(false);
			}
		}
		ResultManager::Instance().Show(ScoreManager::Instance().GetScore());
		m_boss->ResetDeathFinished();
	}

	// リザルト表示中はゲーム更新を止める（プレイヤー操作・スコア加算も止まる）
	if (ResultManager::Instance().IsActive())
	{
		ResultManager::Instance().Update();
		return;
	}

	// プレイヤー
	if (m_player) m_player->Update();

	// プレイヤー位置を更新（敵弾の目標位置として使用）
	if (m_player) m_playerPos = m_player->GetPos();

	// 敵
	for (auto& e : m_Enemies)
	{
		if (!e) continue;
		auto mob = std::dynamic_pointer_cast<MobEnemy>(e);
		if (mob)
		{
			mob->Update(); // MobEnemy は aliveFlg に関係なく Update を呼ぶ
		}
		else if (e->IsAlive())
		{
			e->Update();
		}
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

	// 当たり判定（ホーミング弾 vs 敵）
	if (m_player)
	{
		auto& homings = m_player->GetHomingBullets();
		CollisionManager::CheckHomingVsEnemies(homings, m_Enemies);
	}

	// 当たり判定（ホーミング弾 vs ボス）
	if (m_player && m_boss)
	{
		auto& homings = m_player->GetHomingBullets();
		CollisionManager::CheckHomingVsBoss(homings, m_boss);
	}

	// 敵弾 vs プレイヤー
	CollisionManager::CheckEnemyBulletsVsPlayer(m_Enemies, m_player);

	// MobEnemy が逃げたらウェーブカウントを進める
	for (auto& e : m_Enemies)
	{
		auto mob = std::dynamic_pointer_cast<MobEnemy>(e);
		if (!mob) continue;
		if (!mob->IsEscaped()) continue;

		mob->ResetEscaped();
		WaveManager::Instance().OnEnemyDefeated();
	}

	EffectManager::Instance().Update();

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

	// Nキーで次のウェーブに強制進行（デバッグ用）
	static bool prevN = false;
	bool nowN = GetAsyncKeyState('N') & 0x8000;
	if (nowN && !prevN)
	{
		// 現在の全敵を消す
		for (auto& e : m_Enemies)
		{
			if (e && e->IsAlive()) e->SetAlive(false);
		}
		if (m_boss && m_boss->IsAlive())
		{
			m_boss->SetAlive(false);
		}

		// Y座標管理をリセット
		m_usedY.fill(false);
		m_usedY2.fill(false);

		// スポーンカウンターを最大値にして次のウェーブへ
		int killCount = 0;
		switch (WaveManager::Instance().GetCurrentWave())
		{
		case WaveType::MobEnemy:
			killCount = AppConst::ENEMY_MAX - WaveManager::Instance().GetDefeatedCount();
			break;
		case WaveType::Enemy2:
			killCount = AppConst::SHOOTER_MAX - WaveManager::Instance().GetDefeatedCount();
			break;
		case WaveType::Enemy3:
			killCount = AppConst::TANK_MAX - WaveManager::Instance().GetDefeatedCount();
			break;
		case WaveType::Boss:
			killCount = 1 - WaveManager::Instance().GetDefeatedCount();
			break;
		default:
			break;
		}

		for (int i = 0; i < killCount; i++)
		{
			WaveManager::Instance().OnEnemyDefeated();
		}
	}
	prevN = nowN;

}

void GameScene::SpawnEnemy()
{
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

	// フェーズ1（waveIndex==0）は右からのみ、それ以降はランダム
	bool fromRight = true;
	if (WaveManager::Instance().GetWaveIndex() >= 3)
	{
		fromRight = (rand() % 2 == 0);
	}

	if (m_player) m_playerPos = m_player->GetPos();
	target->Spawn(fromRight, &m_playerPos);
	m_spawnedCount++;
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

	// 敵弾（プレイヤーより上に描画）
	for (auto& e : m_Enemies)
	{
		auto mob = std::dynamic_pointer_cast<MobEnemy>(e);
		if (mob) mob->DrawBullets();
	}

	EffectManager::Instance().Draw();

	// スコア
	ScoreManager::Instance().Draw();

	// 体力バー
	HealthManager::Instance().Draw();

	// リザルトは最前面に描画
	ResultManager::Instance().Draw();

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

	ResultManager::Instance().Release();

	EffectManager::Instance().Release();

}
