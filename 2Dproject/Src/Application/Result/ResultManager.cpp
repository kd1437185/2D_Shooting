#include "ResultManager.h"
#include "../AppConst.h"
#include "../Score/ScoreManager.h"
#include "../Scene/SceneManager.h"
#include "../Sound/SoundManager.h"

void ResultManager::Init()
{
    m_isActive = false;
    m_BgTex.Load("Texture/Result/Asset_15_-_1080p.png");
    m_BackTitleTex.Load("Texture/Result/BACKTITLE.png");
}

void ResultManager::Release()
{
    m_isActive = false;
    m_BgTex.Release();
    m_BackTitleTex.Release();
}

void ResultManager::Show(int _score)
{
    m_score = _score;
    m_isActive = true;
    m_timer = 0;
    m_blinkTimer = 0;
    m_blinkVisible = true;
    m_phase = Phase::ScoreAnim;
    m_scorePosY = AppConst::RESULT_SCORE_START_Y;
    m_scoreScale = AppConst::RESULT_SCORE_START_SCALE;
    SoundManager::Instance().PlayResultSE();
}

void ResultManager::Update()
{
    if (!m_isActive) return;

    m_timer++;

    switch (m_phase)
    {
    case Phase::ScoreAnim: UpdateScoreAnim(); break;
    case Phase::SelectWait:
        if (m_timer >= AppConst::RESULT_SELECT_DELAY)
        {
            m_timer = 0;
            m_phase = Phase::Select;
        }
        break;
    case Phase::Select: UpdateSelect(); break;
    }
}

void ResultManager::UpdateScoreAnim()
{
    float t = (float)m_timer / AppConst::RESULT_ANIM_DURATION;
    if (t > 1.0f) t = 1.0f;

    m_scorePosY = AppConst::RESULT_SCORE_START_Y + (AppConst::RESULT_SCORE_END_Y - AppConst::RESULT_SCORE_START_Y) * t;
    m_scoreScale = AppConst::RESULT_SCORE_START_SCALE + (AppConst::RESULT_SCORE_END_SCALE - AppConst::RESULT_SCORE_START_SCALE) * t;

    if (m_timer >= AppConst::RESULT_ANIM_DURATION)
    {
        m_timer = 0;
        m_phase = Phase::SelectWait;
    }
}

void ResultManager::UpdateSelect()
{
    // 点滅タイマー
    m_blinkTimer++;
    if (m_blinkTimer >= AppConst::BLINK_INTERVAL)
    {
        m_blinkTimer = 0;
        m_blinkVisible = !m_blinkVisible;
    }

    // Enter で決定
    bool nowEnter = GetAsyncKeyState(VK_RETURN) & 0x8000;
    if (nowEnter && !m_prevEnter)
    {
        m_isActive = false;
        SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
    }
    m_prevEnter = nowEnter;
}

void ResultManager::Draw()
{
    if (!m_isActive) return;

    // 背景
    Math::Matrix bgMat = Math::Matrix::CreateTranslation(0, AppConst::RESULT_BG_Y, 0);
    SHADER.m_spriteShader.SetMatrix(bgMat);
    SHADER.m_spriteShader.DrawTex(&m_BgTex,
        Math::Rectangle{ 0, 0, AppConst::RESULT_BG_W, AppConst::RESULT_BG_H },
        AppConst::RESULT_BG_ALPHA);

    // スコア
    ScoreManager::Instance().DrawResult(m_scorePosY, m_scoreScale);

    // BACK TITLE（点滅）
    if (m_phase == Phase::Select)
    {
        if (m_blinkVisible)
        {
            Math::Matrix mat = Math::Matrix::CreateTranslation(
                0, AppConst::RESULT_SELECT_Y1, 0);
            SHADER.m_spriteShader.SetMatrix(mat);
            SHADER.m_spriteShader.DrawTex(&m_BackTitleTex,
                Math::Rectangle{ 0, 0, AppConst::RESULT_SELECT_W, AppConst::RESULT_SELECT_H }, 1.0f);
        }
    }
}