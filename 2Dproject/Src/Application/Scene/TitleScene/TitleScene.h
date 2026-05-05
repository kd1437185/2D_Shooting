#pragma once

#include "../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:
	TitleScene() {}
	~TitleScene() override{}

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;

private:

	// フェーズ管理
	enum class Phase
	{
		Title,  // PRESS ENTER 点滅
		Menu    // メニュー選択
	};

	void UpdateTitle();
	void UpdateMenu();
	void DrawTitle();
	void DrawMenu();

	// タイトル背景
	KdTexture		m_BackTex;
	Math::Matrix	m_BackMat;

	// テキスト
	KdTexture    m_PressEnterTex;
	KdTexture    m_GameStartTex;

	// 点滅用
	int   m_blinkTimer = 0;
	bool  m_blinkVisible = true;

	// メニュー用点滅タイマー（Title の m_blinkTimer と共用してもOKですが分けた方が安全）
	int  m_menuBlinkTimer = 0;
	bool m_menuBlinkVisible = true;

	// メニュー選択
	int  m_selectIndex = 0; // 現在選択中（今は0のみ）

	// キー入力
	bool m_prevEnter = false;
	bool m_prevZ = false;
	bool m_prevUp = false;
	bool m_prevDown = false;

	Phase m_phase = Phase::Title;
};

