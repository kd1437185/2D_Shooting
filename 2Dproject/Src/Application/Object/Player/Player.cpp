#include "Player.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/HomingBullet.h"
#include "Application/AppConst.h"

void Player::Init()
{
    m_tex.Load("Texture/Player/Fairy_3.png");
    m_pos = {};
    m_aliveFlg = true;
    m_animFrame = 0;
    m_animTimer = 0;

	for (int i = 0; i < AppConst::BULLET_MAX; i++)
	{
		auto bullet = std::make_shared<Bullet>();
		bullet->Init();
		m_Bullets.push_back(bullet);
	}

    // ホーミング弾プール
    for (int i = 0; i < AppConst::HOMING_MAX; i++)
    {
        auto hb = std::make_shared<HomingBullet>();
        hb->Init();
        m_HomingBullets.push_back(hb);
    }

    m_shield.Init();

    m_bombStock = AppConst::BOMB_MAX;
    m_prevX = false;
}

void Player::Update()
{
    // アニメーション更新
    m_animTimer++;
    if (m_animTimer >= AppConst::PLAYER_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame = (m_animFrame + 1) % AppConst::PLAYER_ANIM_MAX;
    }

    if (m_isEntering)
    {
        // 入場中は右に進むだけ（操作不可）
        m_pos.x += AppConst::PLAYER_ENTER_SPEED;
        m_direction = 1.0f; // 右向き

        // 停止位置に達したら入場完了
        if (m_pos.x >= AppConst::PLAYER_ENTER_STOP_X)
        {
            m_pos.x = AppConst::PLAYER_ENTER_STOP_X;
            m_isEntering = false;
        }

        // 弾の更新
        for (auto& b : m_Bullets)
        {
            if (b) b->Update();
        }

        m_mat = Math::Matrix::CreateScale(
            m_direction * AppConst::PLAYER_SCALE,
            AppConst::PLAYER_SCALE, 1.0f)
            * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
        return; // 入場中はここで終了
    }

    // 以降は通常操作
   // 移動ベクトルを計算
    Math::Vector2 move = { 0.0f, 0.0f };

    bool isShooting = GetAsyncKeyState('Z') & 0x8000;

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        move.x -= 1.0f;
        if (!isShooting) m_direction = -1.0f; // 撃っていないときだけ向き変更
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        move.x += 1.0f;
        if (!isShooting) m_direction = 1.0f;  // 撃っていないときだけ向き変更
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000) move.y += 1.0f;
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) move.y -= 1.0f;

    float length = sqrtf(move.x * move.x + move.y * move.y);
    if (length > 0.0f)
    {
        move.x = (move.x / length) * AppConst::PLAYER_SPEED;
        move.y = (move.y / length) * AppConst::PLAYER_SPEED;
    }

    m_pos.x += move.x;
    m_pos.y += move.y;

    float halfSize = AppConst::PLAYER_SCALED_W / 2.0f;
    if (m_pos.x < -AppConst::SCREEN_HALF_W + halfSize) m_pos.x = -AppConst::SCREEN_HALF_W + halfSize;
    if (m_pos.x > AppConst::SCREEN_HALF_W - halfSize) m_pos.x = AppConst::SCREEN_HALF_W - halfSize;
    if (m_pos.y < -AppConst::SCREEN_HALF_H + halfSize) m_pos.y = -AppConst::SCREEN_HALF_H + halfSize;
    if (m_pos.y > AppConst::SCREEN_HALF_H - halfSize) m_pos.y = AppConst::SCREEN_HALF_H - halfSize;

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

    // Xキーでボム発動
    bool nowX = GetAsyncKeyState('X') & 0x8000;
    if (nowX && !m_prevX && m_bombStock > 0 && !m_shield.IsBombing())
    {
        m_bombStock--;
        m_shield.ActivateBomb();
    }
    m_prevX = nowX;

    for (auto& b : m_Bullets)
    {
        if (b) b->Update();
    }

    for (auto& hb : m_HomingBullets)
    {
        if (hb) hb->Update();
    }

    m_shield.Update(m_pos);

    m_mat = Math::Matrix::CreateScale(
        m_direction * AppConst::PLAYER_SCALE,
        AppConst::PLAYER_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void Player::Draw()
{
    Math::Rectangle srcRect =
    {
        m_animFrame * AppConst::PLAYER_W,
        0,
        AppConst::PLAYER_W,
        AppConst::PLAYER_H
    };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex, srcRect, 1.0f);

    m_shield.Draw();

	// 弾の描画
	for (auto& b : m_Bullets)
	{
		if (b) b->Draw();
	}

    for (auto& hb : m_HomingBullets)
    {
        if (hb) hb->Draw();
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

    for (auto& hb : m_HomingBullets)
    {
        if (hb) hb->Release();
    }
    m_HomingBullets.clear();

    m_shield.Release();

}

void Player::Shot()
{
    switch (m_bulletLevel)
    {
    case 1: ShotLv1(); break;
    case 2: ShotLv2(); break;
    case 3: ShotLv3(); break;
    case 4: ShotLv4(); break;
    }

}

void Player::ShotLv1()
{
    for (auto& b : m_Bullets)
    {
        if (b && !b->IsAlive())
        {
            b->Fire(m_pos, m_direction, m_bulletDamage);
            return;
        }
    }
}

void Player::ShotLv2()
{
    // 上下2発並行
    int fired = 0;
    for (auto& b : m_Bullets)
    {
        if (b && !b->IsAlive())
        {
            Math::Vector2 pos = m_pos;
            pos.y += (fired == 0) ? AppConst::BULLET_LV2_OFFSET_Y : -AppConst::BULLET_LV2_OFFSET_Y;
            b->Fire(pos, m_direction, m_bulletDamage);
            fired++;
            if (fired >= 2) return;
        }
    }
}

void Player::ShotLv3()
{
    // 3WAY（上・真中・下）
    float angles[3] = {
         AppConst::BULLET_LV3_ANGLE,  // 上
         0.0f,                         // 真中
        -AppConst::BULLET_LV3_ANGLE   // 下
    };

    int fired = 0;
    for (auto& b : m_Bullets)
    {
        if (b && !b->IsAlive())
        {
            float rad = angles[fired] * 3.14159f / 180.0f;
            float dirX = m_direction;
            float velX = cosf(rad) * dirX;
            float velY = sinf(rad);

            // 角度情報をBulletに渡すためFireを拡張
            b->FireAngle(m_pos, velX, velY, m_bulletDamage);
            fired++;
            if (fired >= 3) return;
        }
    }
}

void Player::ShotLv4()
{
    // Lv3の3WAY
    ShotLv3();

    // ホーミング弾は独自の発射間隔で制御
    m_homingTimer++;
    if (m_homingTimer >= AppConst::HOMING_INTERVAL)
    {
        m_homingTimer = 0;
        int fired = 0;
        for (auto& hb : m_HomingBullets)
        {
            if (hb && !hb->IsAlive())
            {
                Math::Vector2 pos = m_pos;
                // 1発目は上、2発目は下にオフセット
                pos.y += (fired == 0) ? AppConst::BULLET_LV2_OFFSET_Y : -AppConst::BULLET_LV2_OFFSET_Y;
                hb->Fire(pos, m_direction, m_bulletDamage, m_enemies, m_boss);
                fired++;
                if (fired >= 2) return;
            }
        }
    }
}

void Player::UpgradeBullet()
{
    if (m_bulletLevel >= 4) return; // 最大レベル

    m_bulletLevel++;
    switch (m_bulletLevel)
    {
    case 2: m_bulletDamage = AppConst::BULLET_DAMAGE_LV2; break;
    case 3: m_bulletDamage = AppConst::BULLET_DAMAGE_LV3; break;
    case 4: m_bulletDamage = AppConst::BULLET_DAMAGE_LV4; break;
    }
}

void Player::StartEnter()
{
    m_pos = { AppConst::PLAYER_ENTER_START_X, 0.0f };
    m_isEntering = true;
}