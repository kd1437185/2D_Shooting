#include "Player.h"
#include "../Bullet/Bullet.h"
#include "Application/AppConst.h"

void Player::Init()
{
	m_tex.Load("Texture/Player/player.png");
	m_pos = {};
	m_aliveFlg = true;

	for (int i = 0; i < AppConst::BULLET_MAX; i++)
	{
		auto bullet = std::make_shared<Bullet>();
		bullet->Init();
		m_Bullets.push_back(bullet);
	}
}

void Player::Update()
{
	// 移動
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) m_pos.x -= AppConst::PLAYER_SPEED;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) m_pos.x += AppConst::PLAYER_SPEED;
	if (GetAsyncKeyState(VK_UP) & 0x8000) m_pos.y += AppConst::PLAYER_SPEED;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) m_pos.y -= AppConst::PLAYER_SPEED;

	// Zキーで発射（押した瞬間）
	bool nowZ = GetAsyncKeyState('Z') & 0x8000;
	if (nowZ && !m_prevZ)
	{
		Shot();
	}
	m_prevZ = nowZ;

	// 弾の更新
	for (auto& b : m_Bullets)
	{
		if (b) b->Update();
	}

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle{ 0,0,AppConst::PLAYER_SIZE,AppConst::PLAYER_SIZE }, 1.0f);

	// 弾の描画
	for (auto& b : m_Bullets)
	{
		if (b) b->Draw();
	}

}

void Player::Release()
{
	m_tex.Release();

	for (auto& b : m_Bullets)
	{
		if (b) b->Release();
	}
	m_Bullets.clear();

}

void Player::Shot()
{
	// 非アクティブな弾を探して発射
	for (auto& b : m_Bullets)
	{
		if (b && !b->IsAlive())
		{
			b->Fire(m_pos); // プレイヤーの現在位置から発射
			return; // 1発だけ
		}
	}
	// 全弾アクティブなら発射しない

}
