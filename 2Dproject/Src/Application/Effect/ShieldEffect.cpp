#include "ShieldEffect.h"
#include "../AppConst.h"

void ShieldEffect::Init()
{
    m_tex.Load("Texture/Effect/Effect_ElectricShield_1_265x265.png");
    m_isActive = false;
    m_isBombing = false;
    m_animFrame = 0;
    m_animTimer = 0;
    m_duration = 0;
    m_currentScale = 1.0f;
    m_currentRadius = 0.0f;
    m_bombTimer = 0;
}

void ShieldEffect::Activate()
{
    m_isActive = true;
    m_isBombing = false;
    m_animFrame = 0;
    m_animTimer = 0;
    m_duration = AppConst::SHIELD_DURATION;
    m_currentScale = AppConst::SHIELD_SCALE;
    m_currentRadius = AppConst::SHIELD_RADIUS;
}

void ShieldEffect::ActivateBomb()
{
    m_isActive = true;
    m_isBombing = true;
    m_animFrame = 0;
    m_animTimer = 0;
    m_bombTimer = 0;
    m_currentScale = AppConst::SHIELD_SCALE;
    m_currentRadius = AppConst::SHIELD_RADIUS;
}

void ShieldEffect::Update(Math::Vector2 _playerPos)
{
    m_pos = _playerPos;

    if (!m_isActive) return;

    // アニメーション更新
    m_animTimer++;
    if (m_animTimer >= AppConst::SHIELD_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame++;
        if (m_animFrame >= AppConst::SHIELD_ANIM_MAX)
            m_animFrame = 0;
    }

    if (m_isBombing)
    {
        // ボム：拡大演出
        m_bombTimer++;
        float t = (float)m_bombTimer / AppConst::BOMB_EXPAND_FRAMES;
        if (t > 1.0f) t = 1.0f;

        m_currentScale = AppConst::SHIELD_SCALE + (AppConst::BOMB_SCALE_MAX - AppConst::SHIELD_SCALE) * t;
        m_currentRadius = AppConst::SHIELD_RADIUS + (AppConst::BOMB_MAX_RADIUS - AppConst::SHIELD_RADIUS) * t;

        if (m_bombTimer >= AppConst::BOMB_EXPAND_FRAMES)
        {
            m_isActive = false;
            m_isBombing = false;
            m_currentScale = AppConst::SHIELD_SCALE;
            m_currentRadius = 0.0f;
        }
    }
    else
    {
        // 通常シールド
        m_duration--;
        if (m_duration <= 0)
        {
            m_isActive = false;
            m_currentRadius = 0.0f;
        }
    }

    m_mat = Math::Matrix::CreateScale(
        m_currentScale, m_currentScale, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void ShieldEffect::Draw()
{
    if (!m_isActive) return;

    int col = m_animFrame % AppConst::SHIELD_ANIM_COLS;
    int row = m_animFrame / AppConst::SHIELD_ANIM_COLS;

    Math::Rectangle srcRect =
    {
        col * AppConst::SHIELD_W,
        row * AppConst::SHIELD_H,
        AppConst::SHIELD_W,
        AppConst::SHIELD_H
    };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex, srcRect, AppConst::SHIELD_ALPHA);
}

void ShieldEffect::Release()
{
    m_tex.Release();
    m_isActive = false;
    m_isBombing = false;
}