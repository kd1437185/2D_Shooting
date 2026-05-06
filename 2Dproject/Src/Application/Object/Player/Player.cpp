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
    // 移動ベクトルを計算
    Math::Vector2 move = { 0.0f, 0.0f };

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        move.x -= 1.0f;
        m_direction = -1.0f; // 左向き
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        move.x += 1.0f;
        m_direction = 1.0f;  // 右向き
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000) move.y += 1.0f;
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) move.y -= 1.0f;

    // 斜め移動を正規化
    float length = sqrtf(move.x * move.x + move.y * move.y);
    if (length > 0.0f)
    {
        move.x = (move.x / length) * AppConst::PLAYER_SPEED;
        move.y = (move.y / length) * AppConst::PLAYER_SPEED;
    }


    m_pos.x += move.x;
    m_pos.y += move.y;

    // 画面外に出ないようにクランプ
    float halfSize = AppConst::PLAYER_SIZE / 2.0f;
    if (m_pos.x < -AppConst::SCREEN_HALF_W + halfSize) m_pos.x = -AppConst::SCREEN_HALF_W + halfSize;
    if (m_pos.x > AppConst::SCREEN_HALF_W - halfSize) m_pos.x = AppConst::SCREEN_HALF_W - halfSize;
    if (m_pos.y < -AppConst::SCREEN_HALF_H + halfSize) m_pos.y = -AppConst::SCREEN_HALF_H + halfSize;
    if (m_pos.y > AppConst::SCREEN_HALF_H - halfSize) m_pos.y = AppConst::SCREEN_HALF_H - halfSize;

    // Zキー連射
    if (GetAsyncKeyState('Z') & 0x8000)
    {
        m_shotTimer++;
        if (m_shotTimer >= AppConst::SHOT_INTERVAL)
        {
            Shot();
            m_shotTimer = 0;
        }
    }
    else
    {
        m_shotTimer = AppConst::SHOT_INTERVAL;
    }

    // 弾の更新
    for (auto& b : m_Bullets)
    {
        if (b) b->Update();
    }

    // 向きを反映した行列（X方向にスケール -1 で反転）
    m_mat = Math::Matrix::CreateScale(m_direction, 1.0f, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
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
    for (auto& b : m_Bullets)
    {
        if (b && !b->IsAlive())
        {
            b->Fire(m_pos, m_direction); // 向きを渡す
            return;
        }
    }

}
