#include "HitEffect.h"
#include "../AppConst.h"

void HitEffect::Init()
{
    m_tex.Load("Texture/Effect/Effect_Explosion2_1_355x365.png");
    m_isPlaying = false;
    m_animFrame = 0;
    m_animTimer = 0;
}

void HitEffect::Play(Math::Vector2 _pos)
{
    m_pos = _pos;
    m_isPlaying = true;
    m_animFrame = 0;
    m_animTimer = 0;
}

void HitEffect::Update()
{
    if (!m_isPlaying) return;

    m_animTimer++;
    if (m_animTimer >= AppConst::HIT_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame++;

        if (m_animFrame >= AppConst::HIT_ANIM_MAX)
        {
            m_animFrame = 0;
            m_isPlaying = false;
        }
    }

    m_mat = Math::Matrix::CreateScale(
        AppConst::HIT_SCALE, AppConst::HIT_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void HitEffect::Draw()
{
    if (!m_isPlaying) return;

    // 横10コマ・縦6行から切り抜き
    int col = m_animFrame % AppConst::HIT_ANIM_COLS;
    int row = m_animFrame / AppConst::HIT_ANIM_COLS;

    Math::Rectangle srcRect =
    {
        col * AppConst::HIT_W,
        row * AppConst::HIT_H,
        AppConst::HIT_W,
        AppConst::HIT_H
    };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex, srcRect, AppConst::HIT_ALPHA);
}

void HitEffect::Release()
{
    m_tex.Release();
    m_isPlaying = false;
}