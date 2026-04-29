#pragma once

// 全てのゲーム内オブジェクトの基底クラス
class BaseObject
{
public:

	BaseObject() { Init(); }
	virtual ~BaseObject(){}

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

protected:

	KdTexture m_tex;			// テクスチャ
	Math::Vector2 m_pos = {};	// 座標
	bool m_aliveFlg = true;		// 生存フラグ

};