#include "HealthManager.h"
#include "../AppConst.h"

void HealthManager::Init()
{
    m_GreenTex.Load("Texture/UI/progressBar_green.png");
    m_WhiteTex.Load("Texture/UI/progressBar_white.png");
    m_hp = AppConst::HP_MAX;
}

void HealthManager::Release()
{
    m_GreenTex.Release();
    m_WhiteTex.Release();
}

void HealthManager::Damage()
{
    if (m_hp > 0) m_hp--;
}

void HealthManager::Draw()
{
    for (int i = 0; i < AppConst::HP_MAX; i++)
    {
        KdTexture& tex = (i < m_hp) ? m_GreenTex : m_WhiteTex;

        Math::Matrix mat = Math::Matrix::CreateScale(
            AppConst::GAUGE_SCALE, AppConst::GAUGE_SCALE, 1.0f)
            * Math::Matrix::CreateTranslation(
                -AppConst::SCREEN_HALF_W + AppConst::GAUGE_X + AppConst::GAUGE_SPACING * i + AppConst::GAUGE_SCALED_W / 2.0f,
                AppConst::SCREEN_HALF_H - AppConst::GAUGE_Y,
                0);

        SHADER.m_spriteShader.SetMatrix(mat);
        SHADER.m_spriteShader.DrawTex(&tex,
            Math::Rectangle{ 0, 0, AppConst::GAUGE_W, AppConst::GAUGE_H }, 1.0f);
    }
}