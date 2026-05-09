#include "TankEnemy.h"
#include "../../../AppConst.h"

void TankEnemy::Init()
{
    m_tex.Load("Texture/Enemy/TankEnemy/D1.png");
    m_aliveFlg = false;
    m_animFrame = 0;
    m_animTimer = 0;
    m_phase = Phase::Drop;

    for (int i = 0; i < AppConst::TANK_BULLET_MAX; i++)
    {
        auto b = std::make_shared<EnemyBullet>();
        b->InitWithTex("Texture/Bullet/Enemy_bigbullet_red.png");
        b->SetTexSize(AppConst::TANK_BULLET_W, AppConst::TANK_BULLET_H);
        m_Bullets.push_back(b);
    }
}

void TankEnemy::Spawn(float _x, float _stopY)
{
    m_pos = { _x, AppConst::TANK_SPAWN_Y };
    m_aliveFlg = true;
    m_stopY = _stopY;
    m_phase = Phase::Drop;
    m_animFrame = 0;
    m_animTimer = 0;
    m_shotTimer = AppConst::TANK_SHOT_INTERVAL; // すぐ撃てるように
    SetHp(AppConst::TANK_HP);
    m_isFading = false;
    m_alpha = 1.0f;
}

void TankEnemy::Update()
{
    // 弾は常に更新
    for (auto& b : m_Bullets)
    {
        if (b) b->Update();
    }

    if (m_isFading)
    {
        UpdateFade();
        return;
    }

    if (!m_aliveFlg) return;

    // アニメーション更新
    m_animTimer++;
    if (m_animTimer >= AppConst::TANK_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame = (m_animFrame + 1) % AppConst::TANK_ANIM_MAX;
    }

    switch (m_phase)
    {
    case Phase::Drop: UpdateDrop(); break;
    case Phase::Rise: UpdateRise(); break;
    case Phase::Stay: UpdateStay(); break;
    }

    m_mat = Math::Matrix::CreateScale(
        AppConst::TANK_SCALE, AppConst::TANK_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void TankEnemy::UpdateDrop()
{
    m_pos.y -= AppConst::TANK_DROP_SPEED;

    if (m_pos.y <= m_stopY)
    {
        m_pos.y = m_stopY;
        m_riseStartY = m_pos.y;
        m_phase = Phase::Rise;
    }
}

void TankEnemy::UpdateRise()
{
    m_pos.y += AppConst::TANK_RISE_SPEED;

    if (m_pos.y >= m_riseStartY + AppConst::TANK_RISE_AMOUNT)
    {
        m_pos.y = m_riseStartY + AppConst::TANK_RISE_AMOUNT;
        m_phase = Phase::Stay;
    }
}

void TankEnemy::UpdateStay()
{
    m_shotTimer++;
    if (m_shotTimer >= AppConst::TANK_SHOT_INTERVAL)
    {
        m_shotTimer = 0;
        Shot();
    }
}

void TankEnemy::Shot()
{
    for (auto& b : m_Bullets)
    {
        if (b && !b->IsAlive())
        {
            // 左に向かって低速で、少しずつ下に落ちる
            b->FireWithGravity(
                m_pos,
                -AppConst::TANK_BULLET_SPEED,  // 左に進む
                0.0f,                           // 初期Y速度
                AppConst::TANK_BULLET_FALL      // 重力
            );
            return;
        }
    }
}

void TankEnemy::Draw()
{
    if (!m_aliveFlg) return;

    Math::Rectangle srcRect =
    {
        m_animFrame * AppConst::TANK_W,
        0,
        AppConst::TANK_W,
        AppConst::TANK_H
    };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex, srcRect, m_alpha);
}

void TankEnemy::DrawBullets()
{
    for (auto& b : m_Bullets)
    {
        if (b && b->IsAlive()) b->Draw();
    }
}

void TankEnemy::Release()
{
    m_tex.Release();
    for (auto& b : m_Bullets)
    {
        if (b) b->Release();
    }
    m_Bullets.clear();
}

void TankEnemy::Damage(int _amount)
{
    m_hp -= _amount;
    if (m_hp <= 0)
    {
        m_hp = 0;
        StartFadeOut();
    }
}