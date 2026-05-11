#pragma once

#include "../BaseObject.h"
#include "../../AppConst.h"
#include "../../Effect/ShieldEffect.h"

class Bullet;   // 前方宣言
class HomingBullet;

class Player : public BaseObject
{
public:

	Player() {}
	~Player() override{}

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	// GameScene から弾リストを取得して当たり判定に使う
	std::vector<std::shared_ptr<Bullet>>& GetBullets() { return m_Bullets; }

	std::vector<std::shared_ptr<HomingBullet>>& GetHomingBullets() { return m_HomingBullets; }
	void SetTargetLists(std::vector<std::shared_ptr<BaseObject>>* _enemies,
		std::shared_ptr<BaseObject>* _boss)
	{
		m_enemies = _enemies;
		m_boss = _boss;
	}

	int  GetBulletDamage() const { return m_bulletDamage; }
	void UpgradeBullet();        // 弾を強化
	int  GetBulletLevel() const { return m_bulletLevel; }

	void StartEnter(); // 入場開始
	bool IsEntering() const { return m_isEntering; }

	bool IsShieldActive() const { return m_shield.IsActive(); }
	void ActivateShield() { m_shield.Activate(); }

	int   GetBombStock() const { return m_bombStock; }
	bool  IsBombing()    const { return m_shield.IsBombing(); }
	float GetShieldRadius() const { return m_shield.GetCurrentRadius(); }

	void SetBulletLevel(int _level)
	{
		m_bulletLevel = _level;
		switch (_level)
		{
		case 2: m_bulletDamage = AppConst::BULLET_DAMAGE_LV2; break;
		case 3: m_bulletDamage = AppConst::BULLET_DAMAGE_LV3; break;
		case 4: m_bulletDamage = AppConst::BULLET_DAMAGE_LV4; break;
		default: m_bulletDamage = AppConst::BULLET_DAMAGE_LV1; break;
		}
	}

private:

	void Shot();
	void ShotLv1();
	void ShotLv2();
	void ShotLv3();
	void ShotLv4();

	std::vector<std::shared_ptr<Bullet>> m_Bullets;
	std::vector<std::shared_ptr<HomingBullet>> m_HomingBullets;

	std::vector<std::shared_ptr<BaseObject>>* m_enemies = nullptr;
	std::shared_ptr<BaseObject>* m_boss = nullptr;

	int  m_shotTimer = 0; // 連射間隔タイマー
	float m_direction = 1.0f;// 向いている方向（1.0f = 右、-1.0f = 左）
	bool  m_prevZ = false;
	int m_bulletDamage = AppConst::BULLET_DAMAGE_LV1;
	int m_bulletLevel = 1;
	int   m_animFrame = 0;
	int   m_animTimer = 0;
	bool m_isEntering = false; // 入場中フラグ
	int m_homingTimer = 0; // ホーミング弾の発射間隔タイマー
	ShieldEffect m_shield;

	int  m_bombStock = AppConst::BOMB_MAX;
	bool m_prevX = false; // Xキー入力

};