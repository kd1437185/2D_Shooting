#include "BombStockUI.h"
#include "../AppConst.h"

void BombStockUI::Init()
{
    m_tex.Load("Texture/UI/armor_silver_blink_full.png");
}

void BombStockUI::Release()
{
    m_tex.Release();
}

void BombStockUI::Draw(int _stock)
{
    for (int i = 0; i < AppConst::BOMB_MAX; i++)
    {
        // ストックあり=左コマ(X:0)、なし=右コマ(X:16)
        Math::Rectangle srcRect =
        {
            (i < _stock) ? 0 : AppConst::BOMB_W,
            0,
            AppConst::BOMB_W,
            AppConst::BOMB_H
        };

        Math::Matrix mat = Math::Matrix::CreateScale(
            AppConst::BOMB_ICON_SCALE, AppConst::BOMB_ICON_SCALE, 1.0f)
            * Math::Matrix::CreateTranslation(
                -AppConst::SCREEN_HALF_W + AppConst::BOMB_ICON_X
                + AppConst::BOMB_ICON_SPACING * i + AppConst::BOMB_W,
                AppConst::SCREEN_HALF_H - AppConst::BOMB_ICON_Y,
                0);

        SHADER.m_spriteShader.SetMatrix(mat);
        SHADER.m_spriteShader.DrawTex(&m_tex, srcRect, 1.0f);
    }
}