#pragma once

#include "../BaseScene/BaseScene.h"
#include "../../Background/ScrollBackground.h"

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


	// テキスト
	KdTexture    m_PressEnterTex;
	KdTexture    m_GameStartTex;

	// 点滅用
	int   m_blinkTimer = 0;
	bool  m_blinkVisible = true;

	// メニュー用点滅タイマー
	int  m_menuBlinkTimer = 0;
	bool m_menuBlinkVisible = true;

	// メニュー選択
	int  m_selectIndex = 0; // 現在選択中（今は0のみ）

	// キー入力
	bool m_prevEnter = false;
	bool m_prevUp = false;
	bool m_prevDown = false;

	Phase m_phase = Phase::Title;

	KdTexture    m_LogoTex;
	Math::Matrix m_LogoMat;
};

