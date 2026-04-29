#include "Player.h"

void Player::Init()
{
	m_tex.Load("Texture/Player/player.png");
	m_pos = {};
	m_aliveFlg = true;
}

void Player::Update()
{
	// ˆÚ“®
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 5;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 5;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += 5;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= 5;
	}


	m_playerMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_playerMat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
}

void Player::Release()
{
	m_tex.Release();
}
