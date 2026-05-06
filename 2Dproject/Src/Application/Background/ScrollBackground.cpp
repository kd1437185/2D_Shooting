#include "ScrollBackground.h"
#include "../AppConst.h"

void ScrollBackground::Init()
{
    for (int i = 0; i < AppConst::BG_LAYER_COUNT; i++)
    {
        std::string path = "Texture/Background/" + std::to_string(i) + ".png";
        m_layers[i].tex.Load(path.c_str());
        m_layers[i].scrollX = 0.0f;
    }
}

void ScrollBackground::Update()
{
    for (int i = 0; i < AppConst::BG_LAYER_COUNT; i++)
    {
        // 左にスクロール（右に進んでいるように見せる）
        m_layers[i].scrollX -= AppConst::BG_SCROLL_SPEED[i];

        // 1枚分スクロールしたらリセット（シームレスループ）
        if (m_layers[i].scrollX <= -AppConst::SCREEN_W)
        {
            m_layers[i].scrollX += AppConst::SCREEN_W;
        }
    }
}

void ScrollBackground::Draw()
{
    for (int i = 0; i < AppConst::BG_LAYER_COUNT; i++)
    {
        float alpha = AppConst::BG_ALPHA[i];

        // 1枚目（現在位置）
        Math::Matrix mat1 = Math::Matrix::CreateTranslation(
            m_layers[i].scrollX,
            0, 0);
        SHADER.m_spriteShader.SetMatrix(mat1);
        SHADER.m_spriteShader.DrawTex(&m_layers[i].tex,
            Math::Rectangle{ 0, 0, AppConst::SCREEN_W, AppConst::SCREEN_H }, alpha);

        // 2枚目（1枚目の右隣に配置してループ）
        Math::Matrix mat2 = Math::Matrix::CreateTranslation(
            m_layers[i].scrollX + AppConst::SCREEN_W,
            0, 0);
        SHADER.m_spriteShader.SetMatrix(mat2);
        SHADER.m_spriteShader.DrawTex(&m_layers[i].tex,
            Math::Rectangle{ 0, 0, AppConst::SCREEN_W, AppConst::SCREEN_H }, alpha);
    }
}

void ScrollBackground::Release()
{
    for (int i = 0; i < AppConst::BG_LAYER_COUNT; i++)
    {
        m_layers[i].tex.Release();
    }
}