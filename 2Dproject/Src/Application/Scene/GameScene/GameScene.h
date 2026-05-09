#pragma once

#include "../BaseScene/BaseScene.h"
#include "Application/AppConst.h"
#include "../../Background/ScrollBackground.h"

class BaseObject;
class Player;
class Boss;

class GameScene : public BaseScene
{
public:
	GameScene() {}
	~GameScene() override {}

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;

private:


	std::shared_ptr<Player> m_player = nullptr;
	std::vector<std::shared_ptr<BaseObject>> m_Enemies;	// 複数対応
	std::shared_ptr<Boss> m_boss = nullptr;

	bool m_prevSpace = false;

	int  m_spawnTimer = 0;
	int m_spawnedCount = 0; // 合計出現数
	// 使用中のY座標インデックスを管理
	std::array<bool, 5> m_usedY = { false, false, false, false, false };

	int m_shooterSpawnTimer = 0;
	int m_shooterSpawnedCount = 0;
	std::array<bool, 5> m_usedY2 = { false, false, false, false, false };

	int  m_tankSpawnTimer = 0;
	int  m_tankSpawnedCount = 0;

	// 敵を出現させる
	void SpawnEnemy(); 
	void SpawnShooterEnemy();
	void SpawnTankEnemy();
	
	Math::Vector2 m_playerPos = {}; // プレイヤー位置キャッシュ

	int m_mobMax = AppConst::MOB_MAX_WAVE1; // 現在のMobEnemy最大数

};