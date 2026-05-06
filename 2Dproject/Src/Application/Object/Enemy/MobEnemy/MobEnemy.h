#pragma once

#include"Application/Object/BaseObject.h"

class MobEnemy : public BaseObject
{
public:

	MobEnemy() {}
	~MobEnemy()override {}

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;

	// 出現位置と方向を指定して初期化
	void Spawn(float _x, float _y);

	bool IsYReleased() const { return m_yReleased; }
	void SetYReleased(bool _flag) { m_yReleased = _flag; }

private:

	int   m_animFrame = 0; // 現在のコマ番号
	int   m_animTimer = 0; // アニメーションタイマー
	float m_direction = -1.0f; // 右から来るので左向き（-1.0f）
	bool  m_yReleased = false; // Y座標解放済みフラグ

};