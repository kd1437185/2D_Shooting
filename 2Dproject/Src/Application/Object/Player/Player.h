#pragma once

#include "../BaseObject.h"

class Bullet;   // 前方宣言

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

private:
	void Shot();

	std::vector<std::shared_ptr<Bullet>> m_Bullets;

	// 連射間隔タイマー
	int  m_shotTimer = 0; 

	// 向いている方向（1.0f = 右、-1.0f = 左）
	float m_direction = 1.0f;

};