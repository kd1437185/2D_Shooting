#include "HealthManager.h"
#include "../AppConst.h"
#include "../Sound/SoundManager.h"

void HealthManager::Init()
{
    m_HeartTex.Load("Texture/UI/heart_normal_blink_full.png");
    m_hp = AppConst::HP_MAX;
}

void HealthManager::Release()
{
    m_HeartTex.Release();
}

void HealthManager::Damage()
{
    if (m_hp > 0)
    {
        m_hp--;

        if (m_hp > 0)
        {
            // HP が残っているときだけシールド発動・SE再生
            m_wasDamaged = true;
            SoundManager::Instance().PlayDamageSE();
        }
    }
}

void HealthManager::Draw()
{
    for (int i = 0; i < AppConst::HP_MAX; i++)
    {
        Math::Rectangle srcRect =
        {
            (i < m_hp) ? 0 : AppConst::GAUGE_W,
            0,
            AppConst::GAUGE_W,
            AppConst::GAUGE_H
        };

        Math::Matrix mat = Math::Matrix::CreateScale(
            AppConst::GAUGE_SCALE, AppConst::GAUGE_SCALE, 1.0f)
            * Math::Matrix::CreateTranslation(
                -AppConst::SCREEN_HALF_W + AppConst::GAUGE_X
                + AppConst::GAUGE_SPACING * i + AppConst::GAUGE_SCALED_W / 2.0f,
                AppConst::SCREEN_HALF_H - AppConst::GAUGE_Y,
                0);

        SHADER.m_spriteShader.SetMatrix(mat);
        SHADER.m_spriteShader.DrawTex(&m_HeartTex, srcRect, 1.0f);
    }
}