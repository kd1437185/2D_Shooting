#include "ScoreManager.h"
#include "../AppConst.h"

void ScoreManager::Init()
{
    m_numTex.Load("Texture/Score/number.png");
    m_score = 0;
}

void ScoreManager::Release()
{
    m_numTex.Release();
}

void ScoreManager::AddScore(int _score)
{
    m_score += _score;

    // 9999999 を超えないようにクランプ
    if (m_score > AppConst::SCORE_MAX)
    {
        m_score = AppConst::SCORE_MAX;
    }
}

void ScoreManager::Draw()
{
    // 常に7桁で表示（先頭を0埋め）
    for (int i = 0; i < AppConst::SCORE_DIGITS; i++)
    {
        // 上の桁から1桁ずつ取り出す
        // 例：スコア123 → 0000123
        int place = 1;
        for (int j = 0; j < AppConst::SCORE_DIGITS - 1 - i; j++)
        {
            place *= 10;
        }
        int digit = (m_score / place) % 10;

        Math::Rectangle srcRect =
        {
            digit * AppConst::NUMBER_W,
            0,
            AppConst::NUMBER_W,
            AppConst::NUMBER_H
        };

        // 左上基準で i 文字分右にずらす
        Math::Matrix mat = Math::Matrix::CreateTranslation(
            AppConst::SCORE_X + i * AppConst::NUMBER_W - AppConst::SCREEN_HALF_W,
            AppConst::SCREEN_HALF_H - AppConst::SCORE_Y,
            0);

        SHADER.m_spriteShader.SetMatrix(mat);
        SHADER.m_spriteShader.DrawTex(&m_numTex, srcRect, 1.0f);
    }
}

void ScoreManager::DrawResult(float _posY, float _scale)
{
    for (int i = 0; i < AppConst::SCORE_DIGITS; i++)
    {
        int place = 1;
        for (int j = 0; j < AppConst::SCORE_DIGITS - 1 - i; j++)
            place *= 10;
        int digit = (m_score / place) % 10;

        Math::Rectangle srcRect =
        {
            digit * AppConst::NUMBER_W,
            0,
            AppConst::NUMBER_W,
            AppConst::NUMBER_H
        };

        // スケールと位置を反映
        float scaledW = AppConst::NUMBER_W * _scale;
        float totalW = scaledW * AppConst::SCORE_DIGITS;

        Math::Matrix mat = Math::Matrix::CreateScale(_scale, _scale, 1.0f)
            * Math::Matrix::CreateTranslation(
                -totalW / 2.0f + scaledW * i + scaledW / 2.0f,
                _posY,
                0);

        SHADER.m_spriteShader.SetMatrix(mat);
        SHADER.m_spriteShader.DrawTex(&m_numTex, srcRect, 1.0f);
    }
}