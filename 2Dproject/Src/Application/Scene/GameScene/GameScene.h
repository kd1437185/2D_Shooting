#pragma once

#include "../BaseScene/BaseScene.h"

class BaseObject;
class Player;

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

	// ゲーム画面背景
	KdTexture		m_BackTex;
	Math::Matrix	m_BackMat;

	std::shared_ptr<Player> m_player = nullptr;
	std::vector<std::shared_ptr<BaseObject>> m_Enemies;	// 複数対応

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
	

};