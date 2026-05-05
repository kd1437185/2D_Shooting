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

	// 弾を撃つ(Zキー)瞬間判定用
	bool m_prevZ = false;

};