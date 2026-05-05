#include "TitleScene.h"

#include "../SceneManager.h"
#include "../../AppConst.h"

void TitleScene::Init()
{
	m_BackTex.Load("Texture/TitleScene/title.png");

	m_PressEnterTex.Load("Texture/TitleScene/press_enter.png");
	m_GameStartTex.Load("Texture/TitleScene/game_start.png");

	// 背景
	m_BackMat = Math::Matrix::CreateTranslation(0, 0, 0);

	m_phase = Phase::Title;
	m_blinkTimer = 0;
	m_blinkVisible = true;
	m_selectIndex = 0;

}

void TitleScene::Update()
{
	
	switch (m_phase)
	{
	case Phase::Title: UpdateTitle(); break;
	case Phase::Menu:  UpdateMenu();  break;
	}

}

void TitleScene::UpdateTitle()
{
	// 点滅タイマー
	m_blinkTimer++;
	if (m_blinkTimer >= AppConst::BLINK_INTERVAL)
	{
		m_blinkTimer = 0;
		m_blinkVisible = !m_blinkVisible;
	}

	// Enter で メニューへ
	bool nowEnter = GetAsyncKeyState(VK_RETURN) & 0x8000;
	if (nowEnter && !m_prevEnter)
	{
		m_phase = Phase::Menu;
		m_blinkVisible = false; // 点滅を消す
	}
	m_prevEnter = nowEnter;
}

void TitleScene::UpdateMenu()
{
	// メニュー項目の点滅タイマー
	m_menuBlinkTimer++;
	if (m_menuBlinkTimer >= AppConst::BLINK_INTERVAL)
	{
		m_menuBlinkTimer = 0;
		m_menuBlinkVisible = !m_menuBlinkVisible;
	}

	// 上下キーで選択（今は1項目のみなので将来用）
	bool nowUp = GetAsyncKeyState(VK_UP) & 0x8000;
	bool nowDown = GetAsyncKeyState(VK_DOWN) & 0x8000;

	if (nowUp && !m_prevUp)
	{
		m_selectIndex--;
		if (m_selectIndex < 0) m_selectIndex = 0; // 項目が1つなので上限
	}
	if (nowDown && !m_prevDown)
	{
		m_selectIndex++;
		if (m_selectIndex > 0) m_selectIndex = 0; // 項目が1つなので上限
	}

	m_prevUp = nowUp;
	m_prevDown = nowDown;

	// Zキーで決定
	bool nowZ = GetAsyncKeyState('Z') & 0x8000;
	if (nowZ && !m_prevZ)
	{
		switch (m_selectIndex)
		{
		case 0: // GAME START
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
			break;
		}
	}
	m_prevZ = nowZ;
}

void TitleScene::Draw()
{
	// 背景（常に描画）
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex,
		Math::Rectangle{ 0, 0, AppConst::SCREEN_W, AppConst::SCREEN_H }, 1.0f);

	switch (m_phase)
	{
	case Phase::Title: DrawTitle(); break;
	case Phase::Menu:  DrawMenu();  break;
	}

}

void TitleScene::DrawTitle()
{
	// 点滅中のみ描画
	if (!m_blinkVisible) return;

	Math::Matrix mat = Math::Matrix::CreateTranslation(
		0,
		-AppConst::SCREEN_HALF_H + AppConst::PRESS_ENTER_Y,
		0);

	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(&m_PressEnterTex,
		Math::Rectangle{ 0, 0, AppConst::TEXT_W, AppConst::TEXT_H }, 1.0f);
}

void TitleScene::DrawMenu()
{
	// 選択中は点滅、非選択は暗く表示
	// 今は GAME START のみ
	if (m_selectIndex == 0 && !m_menuBlinkVisible) return;

	float alpha = (m_selectIndex == 0) ? 1.0f : 0.4f;

	Math::Matrix mat = Math::Matrix::CreateTranslation(
		0,
		-AppConst::SCREEN_HALF_H + AppConst::MENU_START_Y,
		0);

	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(&m_GameStartTex,
		Math::Rectangle{ 0, 0, AppConst::TEXT_W, AppConst::TEXT_H }, alpha);
}

void TitleScene::Release()
{
	m_BackTex.Release();
	m_PressEnterTex.Release();
	m_GameStartTex.Release();

}
