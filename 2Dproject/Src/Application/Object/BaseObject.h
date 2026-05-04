#pragma once

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

protected:

	KdTexture		m_tex;			// テクスチャ
	Math::Vector2	m_pos = {};	// 座標
	Math::Matrix	m_mat;			// 行列
	bool			m_aliveFlg = true;		// 生存フラグ

};