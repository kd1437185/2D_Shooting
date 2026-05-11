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
#include "../../Sound/SoundManager.h"
#include "Application/PointManager.h"

void GameScene::Init()
{

	SoundManager::Instance().PlayGameBGM();

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

	PointManager::Instance().Init();

	m_bombUI.Init();

	m_bulletLevelUI.Init();

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

		int waveIndex = WaveManager::Instance().GetWaveIndex();
		if (m_player)
		{
			if (waveIndex == 3)      m_player->SetBulletLevel(2);
			else if (waveIndex == 5) m_player->SetBulletLevel(3);
			else if (waveIndex == 6) m_player->SetBulletLevel(4);
		}

		const WaveData& wave = WaveManager::Instance().GetCurrentWave();

		// スポーンカウンターをリセット
		if (wave.spawnMob)
		{
			m_spawnedCount = 0;
			m_spawnTimer = AppConst::ENEMY_SPAWN_INTERVAL;
			m_mobMax = wave.mobCount;
		}
		if (wave.spawnShooter)
		{
			m_shooterSpawnedCount = 0;
			m_shooterSpawnTimer = AppConst::ENEMY_SPAWN_INTERVAL;
		}
		if (wave.spawnTank)
		{
			m_tankSpawnedCount = 0;
			m_tankSpawnTimer = AppConst::TANK_SPAWN_INTERVAL;
		}

		m_usedY.fill(false);
		m_usedY2.fill(false);
	}

	const WaveData& wave = WaveManager::Instance().GetCurrentWave();

	// MobEnemy スポーン
	if (wave.spawnMob && m_spawnedCount < wave.mobCount)
	{
		m_spawnTimer++;
		if (m_spawnTimer >= AppConst::ENEMY_SPAWN_INTERVAL)
		{
			m_spawnTimer = 0;
			SpawnEnemy();
		}
	}

	// ShooterEnemy スポーン
	if (wave.spawnShooter && m_shooterSpawnedCount < wave.shooterCount)
	{
		m_shooterSpawnTimer++;
		if (m_shooterSpawnTimer >= AppConst::ENEMY_SPAWN_INTERVAL)
		{
			m_shooterSpawnTimer = 0;
			SpawnShooterEnemy();
		}
	}

	// TankEnemy スポーン
	if (wave.spawnTank && m_tankSpawnedCount < wave.tankCount)
	{
		m_tankSpawnTimer++;
		if (m_tankSpawnTimer >= AppConst::TANK_SPAWN_INTERVAL)
		{
			m_tankSpawnTimer = 0;
			SpawnTankEnemy();
		}
	}

	// Boss スポーン
	if (wave.spawnBoss)
	{
		if (m_boss && !m_boss->IsAlive() &&
			m_boss->GetPhase() != Boss::Phase::Death &&
			m_boss->GetPhase() != Boss::Phase::EnterFromLeft)
		{
			m_boss->Spawn();
		}
	}

	// ボス
	if (m_boss && m_boss->IsAlive())
	{
		if (m_player) m_boss->SetPlayerPos(m_player->GetPos());
		m_boss->Update();
	}

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

	// 1秒ごとにスコア加算
	/*static int scoreTimer = 0;
	scoreTimer++;
	if (scoreTimer >= 60)
	{
		scoreTimer = 0;
		ScoreManager::Instance().AddScore(100);
	}*/

	// プレイヤー
	if (m_player) m_player->Update();

	if (m_player)
	{
		PointManager::Instance().Update(m_player->GetPos());
	}

	// プレイヤー位置を更新（敵弾の目標位置として使用）
	if (m_player) m_playerPos = m_player->GetPos();

	// 敵
	for (auto& e : m_Enemies)
	{
		if (!e) continue;
		auto mob = std::dynamic_pointer_cast<MobEnemy>(e);
		if (mob)
		{
			mob->Update(); // MobEnemy は常に Update
			continue;
		}
		auto shooter = std::dynamic_pointer_cast<ShooterEnemy>(e);
		if (shooter)
		{
			shooter->Update(); // ShooterEnemy も常に Update
			continue;
		}
		auto tank = std::dynamic_pointer_cast<TankEnemy>(e);
		if (tank) 
		{
			tank->Update(); 
			continue; 
		}
		if (e->IsAlive()) e->Update();
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

	// 弾幕 vs プレイヤー
	if (m_boss && m_player)
	{
		auto& danmakuBullets = m_boss->GetDanmakuBullets();
		CollisionManager::CheckDanmakuVsPlayer(danmakuBullets, m_player);
	}

	// 被弾時にシールド発動
	if (HealthManager::Instance().WasDamaged())
	{
		HealthManager::Instance().ResetDamaged();
		if (m_player) m_player->ActivateShield();
	}

	// MobEnemy が逃げたらウェーブカウントを進める
	for (auto& e : m_Enemies)
	{
		auto mob = std::dynamic_pointer_cast<MobEnemy>(e);
		if (!mob) continue;
		if (!mob->IsEscaped()) continue;

		mob->ResetEscaped();
		WaveManager::Instance().OnEnemyDefeated(true, false, false, false);
	}

	EffectManager::Instance().Update();

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
		for (auto& e : m_Enemies)
		{
			if (e && e->IsAlive()) e->SetAlive(false);
		}
		if (m_boss && m_boss->IsAlive()) m_boss->SetAlive(false);

		m_usedY.fill(false);
		m_usedY2.fill(false);

		const WaveData& wave = WaveManager::Instance().GetCurrentWave();
		int mobLeft = wave.mobCount - WaveManager::Instance().GetMobDefeated();
		int shooterLeft = wave.shooterCount - WaveManager::Instance().GetShooterDefeated();
		int tankLeft = wave.tankCount - WaveManager::Instance().GetTankDefeated();

		for (int i = 0; i < mobLeft; i++) WaveManager::Instance().OnEnemyDefeated(true, false, false, false);
		for (int i = 0; i < shooterLeft; i++) WaveManager::Instance().OnEnemyDefeated(false, true, false, false);
		for (int i = 0; i < tankLeft; i++) WaveManager::Instance().OnEnemyDefeated(false, false, true, false);
		if (wave.spawnBoss)                   WaveManager::Instance().OnEnemyDefeated(false, false, false, true);
	}
	prevN = nowN;

	static bool prevQ = false;
	bool nowQ = GetAsyncKeyState('Q') & 0x8000;
	if (nowQ && !prevQ)
	{
		SoundManager::Instance().ToggleMute();
	}
	prevQ = nowQ;

}

void GameScene::SpawnEnemy()
{
	std::shared_ptr<MobEnemy> target = nullptr;
	for (auto& e : m_Enemies)
	{
		if (e && !e->IsAlive() && !e->IsFading())
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
		if (e && !e->IsAlive() && !e->IsFading())
		{
			target = std::dynamic_pointer_cast<ShooterEnemy>(e);
			if (target) break;
		}
	}
	if (!target) return;

	float spawnX = AppConst::SCREEN_HALF_W + AppConst::SHOOTER_SCALED_W;

	// 1体目は上、2体目は下から出す
	float spawnY = (m_shooterSpawnedCount % 2 == 0)
		? AppConst::SCREEN_HALF_H + AppConst::SHOOTER_SCALED_H   // 上
		: -(AppConst::SCREEN_HALF_H + AppConst::SHOOTER_SCALED_H); // 下

	target->Spawn(spawnX, spawnY);
	m_shooterSpawnedCount++;
}

void GameScene::SpawnTankEnemy()
{
	// 非アクティブな TankEnemy を探す
	std::shared_ptr<TankEnemy> target = nullptr;
	for (auto& e : m_Enemies)
	{
		if (e && !e->IsAlive() && !e->IsFading())
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

	// ボス名前
	if (m_boss) m_boss->DrawName();

	// モブエネミー
	for (auto& e : m_Enemies)
	{
		if(e && (e->IsAlive() || e->IsFading())) e->Draw();
	}

	PointManager::Instance().Draw();

	// プレイヤー
	if (m_player)
	{
		m_player->Draw();
	}

	// 敵弾（プレイヤーより上に描画）
	for (auto& e : m_Enemies)
	{
		auto tank = std::dynamic_pointer_cast<TankEnemy>(e);
		if (tank) tank->DrawBullets();

		auto mob = std::dynamic_pointer_cast<MobEnemy>(e);
		if (mob) mob->DrawBullets();

		auto shooter = std::dynamic_pointer_cast<ShooterEnemy>(e);
		if (shooter) shooter->DrawBullets();
	}

	// ボス弾幕（プレイヤーより上に描画）
	if (m_boss) m_boss->DrawDanmaku();

	EffectManager::Instance().Draw();

	// スコア
	ScoreManager::Instance().Draw();

	m_bulletLevelUI.Draw(m_player ? m_player->GetBulletLevel() : 1);

	// 体力バー
	HealthManager::Instance().Draw();

	m_bombUI.Draw(m_player ? m_player->GetBombStock() : 0);

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

	m_bombUI.Release();

	m_bulletLevelUI.Release();

	PointManager::Instance().Release();

}
