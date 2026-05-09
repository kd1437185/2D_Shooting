#pragma once

#include "Application/AppConst.h"

// 全てのゲーム内オブジェクトの基底クラス
class BaseObject
{
public:

	BaseObject() { Init(); }
	virtual ~BaseObject(){}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

	// 外部から座標をセットする
	void SetPos(Math::Vector2 _pos) { m_pos = _pos; }
	Math::Vector2 GetPos()     const { return m_pos; }
	bool IsAlive()             const { return m_aliveFlg; }
	void SetAlive(bool _alive) { m_aliveFlg = _alive; }

	void SetHp(int _hp) { m_hp = _hp; m_maxHp = _hp; }
	virtual void Damage(int _amount) { m_hp -= _amount; if (m_hp <= 0) { m_hp = 0; m_aliveFlg = false; } }
	int  GetHp()       const { return m_hp; }
	int  GetMaxHp()    const { return m_maxHp; }
	bool IsDead()      const { return m_hp <= 0; }

	void StartFadeOut() { m_isFading = true; m_alpha = 1.0f; }
	bool IsFading()  const { return m_isFading; }
	float GetAlpha() const { return m_alpha; }

	void UpdateFade()
	{
		if (!m_isFading) return;
		m_alpha -= AppConst::FADE_SPEED;
		if (m_alpha <= 0.0f)
		{
			m_alpha = 0.0f;
			m_isFading = false;
			m_aliveFlg = false;
		}
	}

protected:

	KdTexture		m_tex;			// テクスチャ
	Math::Vector2	m_pos = {};	// 座標
	Math::Matrix	m_mat;			// 行列
	bool			m_aliveFlg = true;		// 生存フラグ

	int m_hp = 1;
	int m_maxHp = 1;

	bool  m_isFading = false;
	float m_alpha = 1.0f;
};