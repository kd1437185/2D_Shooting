#include "DanmakuBullet.h"
#include "Application/AppConst.h"

void DanmakuBullet::Init()
{
    m_aliveFlg = false;
    m_velX = 0.0f;
    m_velY = 0.0f;
}

void DanmakuBullet::Fire(Math::Vector2 _startPos, float _angleRad, bool _isOrange)
{
    m_pos = _startPos;
    m_aliveFlg = true;
    m_isOrange = _isOrange;
    m_velX = cosf(_angleRad) * AppConst::DANMAKU_BULLET_SPEED;
    m_velY = sinf(_angleRad) * AppConst::DANMAKU_BULLET_SPEED;

    m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void DanmakuBullet::Update()
{
    if (!m_aliveFlg) return;

    if (m_isExpand)
    {
        UpdateExpand();
        return;
    }

    m_pos.x += m_velX;
    m_pos.y += m_velY;

    if (m_pos.x > AppConst::SCREEN_HALF_W + 50 ||
        m_pos.x < -AppConst::SCREEN_HALF_W - 50 ||
        m_pos.y >  AppConst::SCREEN_HALF_H + 50 ||
        m_pos.y < -AppConst::SCREEN_HALF_H - 50)
    {
        m_aliveFlg = false;
        return;
    }

    m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void DanmakuBullet::Draw()
{
    if (!m_aliveFlg || !m_tex) return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(m_tex,
        Math::Rectangle{ 0, 0, AppConst::ENEMY_BULLET_W, AppConst::ENEMY_BULLET_H },
        1.0f);
}

void DanmakuBullet::Release()
{
    m_aliveFlg = false;
}

void DanmakuBullet::SetExpandMode(float _stopRadius, int _stopTime, float _fastSpeed)
{
    m_isExpand = true;
    m_stopRadius = _stopRadius;
    m_stopTime = _stopTime;
    m_fastSpeed = _fastSpeed;
    m_expandPhase = ExpandPhase::Expand;
    m_stopTimer = 0;
    m_startPos = m_pos;
}

void DanmakuBullet::UpdateExpand()
{
    switch (m_expandPhase)
    {
    case ExpandPhase::Expand:
    {
        m_pos.x += m_velX;
        m_pos.y += m_velY;

        // 中心からの距離を計算
        float dx = m_pos.x - m_startPos.x;
        float dy = m_pos.y - m_startPos.y;
        float dist = sqrtf(dx * dx + dy * dy);

        if (dist >= m_stopRadius)
        {
            m_expandPhase = ExpandPhase::Stop;
            m_stopTimer = 0;
        }
        break;
    }
    case ExpandPhase::Stop:
        m_stopTimer++;
        if (m_stopTimer >= m_stopTime)
        {
            // 高速で発射（元の方向に）
            float len = sqrtf(m_velX * m_velX + m_velY * m_velY);
            if (len > 0.0f)
            {
                m_velX = (m_velX / len) * m_fastSpeed;
                m_velY = (m_velY / len) * m_fastSpeed;
            }
            m_expandPhase = ExpandPhase::Launch;
        }
        break;

    case ExpandPhase::Launch:
        m_pos.x += m_velX;
        m_pos.y += m_velY;

        if (m_pos.x > AppConst::SCREEN_HALF_W + 50 ||
            m_pos.x < -AppConst::SCREEN_HALF_W - 50 ||
            m_pos.y >  AppConst::SCREEN_HALF_H + 50 ||
            m_pos.y < -AppConst::SCREEN_HALF_H - 50)
        {
            m_aliveFlg = false;
        }
        break;
    }

    m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}
