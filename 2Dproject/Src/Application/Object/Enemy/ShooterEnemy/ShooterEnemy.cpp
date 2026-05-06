#include "ShooterEnemy.h"
#include "../../../AppConst.h"

void ShooterEnemy::Init()
{
    m_tex.Load("Texture/Enemy/ShooterEnemy/D2.png");
    m_aliveFlg = false;
    m_animFrame = 0;
    m_animTimer = 0;
    m_direction = -1.0f;
    m_floatTimer = 0.0f;
    m_yReleased = false;
    m_phase = Phase::Enter;
}

void ShooterEnemy::Spawn(float _x, float _y)
{
    m_pos = { _x, _y };
    m_aliveFlg = true;
    m_direction = -1.0f;
    m_floatTimer = 0.0f;
    m_baseY = _y;
    m_yReleased = false;
    m_phase = Phase::Enter;
}

void ShooterEnemy::Update()
{
    if (!m_aliveFlg) return;

    // アニメーション更新
    m_animTimer++;
    if (m_animTimer >= AppConst::SHOOTER_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame = (m_animFrame + 1) % AppConst::SHOOTER_ANIM_MAX;
    }

    switch (m_phase)
    {
    case Phase::Enter:
        m_pos.x -= AppConst::SHOOTER_SPEED;
        if (m_pos.x <= AppConst::SHOOTER_STOP_X)
        {
            m_pos.x = AppConst::SHOOTER_STOP_X;
            m_phase = Phase::Float;
        }
        break;

    case Phase::Float:
        m_floatTimer += AppConst::SHOOTER_FLOAT_SPEED;
        m_pos.y = m_baseY + sinf(m_floatTimer) * AppConst::SHOOTER_FLOAT_RANGE;
        break;
    }

    m_mat = Math::Matrix::CreateScale(m_direction * AppConst::SHOOTER_SCALE, AppConst::SHOOTER_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
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
    SHADER.m_spriteShader.DrawTex(&m_tex, srcRect, 1.0f);
}

void ShooterEnemy::Release()
{
    m_tex.Release();
}