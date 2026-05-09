#include "ShooterEnemy.h"
#include "Application/AppConst.h"

void ShooterEnemy::Init()
{
    m_tex.Load("Texture/Enemy/ShooterEnemy/D2.png");
    m_aliveFlg = false;
    m_animFrame = 0;
    m_animTimer = 0;
    m_phase = Phase::Enter;

    for (int i = 0; i < AppConst::ENEMY_BULLET_MAX; i++)
    {
        auto b = std::make_shared<EnemyBullet>();
        b->InitWithTex("Texture/Bullet/Enemy_bullet_orange.png");
        m_Bullets.push_back(b);
    }
}

void ShooterEnemy::Spawn(float _x, float _y)
{
    m_pos = { _x, _y };
    m_aliveFlg = true;
    m_animFrame = 0;
    m_animTimer = 0;
    m_phaseTimer = 0;
    m_shotTimer = AppConst::SHOOTER_SHOT_INTERVAL; // 即座に1発目を撃つ
    m_phase = Phase::Enter;
    m_yReleased = false;
    m_isFading = false;
    m_alpha = 1.0f;

    m_fromTop = (_y > 0);
    m_vertDir = m_fromTop ? -1.0f : 1.0f;

    SetHp(AppConst::SHOOTER_HP);
}

void ShooterEnemy::Update()
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
    if (m_animTimer >= AppConst::SHOOTER_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame = (m_animFrame + 1) % AppConst::SHOOTER_ANIM_MAX;
    }

    m_phaseTimer++;

    switch (m_phase)
    {
    case Phase::Enter:    UpdateEnter();    break;
    case Phase::MoveVert: UpdateMoveVert(); break;
    case Phase::Stay:     UpdateStay();     break;
    }

    m_mat = Math::Matrix::CreateScale(
        -AppConst::SHOOTER_SCALE, AppConst::SHOOTER_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void ShooterEnemy::UpdateEnter()
{
    m_pos.x -= AppConst::SHOOTER_ENTER_SPEED;

    if (m_pos.x <= AppConst::SHOOTER_ENTER_X)
    {
        m_pos.x = AppConst::SHOOTER_ENTER_X;
        m_phaseTimer = 0;
        m_phase = Phase::MoveVert;
    }
}

void ShooterEnemy::UpdateMoveVert()
{
    m_pos.y += AppConst::SHOOTER_VERT_SPEED * m_vertDir;

    // 画面端で反転
    if (m_pos.y > AppConst::SCREEN_HALF_H - AppConst::SHOOTER_SCALED_H / 2.0f)
    {
        m_pos.y = AppConst::SCREEN_HALF_H - AppConst::SHOOTER_SCALED_H / 2.0f;
        m_vertDir = -1.0f;
    }
    if (m_pos.y < -AppConst::SCREEN_HALF_H + AppConst::SHOOTER_SCALED_H / 2.0f)
    {
        m_pos.y = -AppConst::SCREEN_HALF_H + AppConst::SHOOTER_SCALED_H / 2.0f;
        m_vertDir = 1.0f;
    }

    // 2秒後に停止フェーズへ
    if (m_phaseTimer >= 120)
    {
        m_phaseTimer = 0;
        m_shotTimer = AppConst::SHOOTER_SHOT_INTERVAL; // 即座に撃つ
        m_phase = Phase::Stay;
    }
}

void ShooterEnemy::UpdateStay()
{
    // インターバルで繰り返し発射
    m_shotTimer++;
    if (m_shotTimer >= AppConst::SHOOTER_SHOT_INTERVAL)
    {
        m_shotTimer = 0;
        Shot3Way();
    }
}

void ShooterEnemy::Shot3Way()
{
    float angleRad = AppConst::SHOOTER_3WAY_ANGLE * 3.14159f / 180.0f;
    float angles[3] = { angleRad, 0.0f, -angleRad };

    int fired = 0;
    for (auto& b : m_Bullets)
    {
        if (fired >= 3) break;
        if (b && !b->IsAlive())
        {
            float velX = -cosf(angles[fired]) * AppConst::SHOOTER_BULLET_SPEED;
            float velY = sinf(angles[fired]) * AppConst::SHOOTER_BULLET_SPEED;
            b->FireVelocity(m_pos, velX, velY);
            fired++;
        }
    }
}

void ShooterEnemy::Draw()
{
    if (!m_aliveFlg) return;

    Math::Rectangle srcRect =
    {
        m_animFrame * AppConst::SHOOTER_W,
        0,
        AppConst::SHOOTER_W,
        AppConst::SHOOTER_H
    };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex, srcRect, m_alpha);
}

void ShooterEnemy::DrawBullets()
{
    for (auto& b : m_Bullets)
    {
        if (b && b->IsAlive()) b->Draw();
    }
}

void ShooterEnemy::Release()
{
    m_tex.Release();
    for (auto& b : m_Bullets)
    {
        if (b) b->Release();
    }
    m_Bullets.clear();
}

void ShooterEnemy::Damage(int _amount)
{
    m_hp -= _amount;
    if (m_hp <= 0)
    {
        m_hp = 0;
        StartFadeOut();
    }
}