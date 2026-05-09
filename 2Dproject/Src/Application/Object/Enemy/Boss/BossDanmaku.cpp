#include "BossDanmaku.h"
#include "Application/AppConst.h"

void BossDanmaku::Init()
{
    m_BlueTex.Load("Texture/Bullet/Enemy_bullet_blue.png");
    m_OrangeTex.Load("Texture/Bullet/Enemy_bullet_orange.png");

    for (int i = 0; i < AppConst::DANMAKU_BULLET_MAX; i++)
    {
        auto b = std::make_shared<DanmakuBullet>();
        b->Init();
        m_Bullets.push_back(b);
    }

    m_active = false;
    m_pattern = 1;
    m_timer = 0;
    m_baseAngle = 0.0f;
    m_waveTimer = 0.0f;
    m_shotCount = 0;
    m_isOrange = false;
    m_expandTimer = 0;
}

void BossDanmaku::SetPattern(int _pattern)
{
    m_pattern = _pattern;
    m_timer = 0;
    m_baseAngle = 0.0f;
    m_waveTimer = 0.0f;
    m_shotCount = 0;
    m_isOrange = false;
    m_expandTimer = 0;
}

void BossDanmaku::Start()
{
    m_active = true;
    SetPattern(m_pattern);
}

void BossDanmaku::Stop()
{
    m_active = false;
}

std::shared_ptr<DanmakuBullet> BossDanmaku::GetFreeBullet()
{
    for (auto& b : m_Bullets)
    {
        if (b && !b->IsAlive()) return b;
    }
    return nullptr;
}

void BossDanmaku::Update(Math::Vector2 _bossPos, Math::Vector2 _playerPos)
{
    for (auto& b : m_Bullets)
    {
        if (b) b->Update();
    }

    if (!m_active) return;

    m_timer++;

    switch (m_pattern)
    {
    case 1: // 円形＋回転
        if (m_timer >= AppConst::DANMAKU_INTERVAL)
        {
            m_timer = 0;
            FireCircle(_bossPos);
            m_shotCount++;
            if (m_shotCount >= AppConst::DANMAKU_COLOR_CHANGE)
            {
                m_shotCount = 0;
                m_isOrange = !m_isOrange;
            }
            m_baseAngle += AppConst::DANMAKU_ROTATE_SPEED * 3.14159f / 180.0f;
        }
        break;

    case 2: // スパイラル
        if (m_timer >= AppConst::DANMAKU_SPIRAL_INTERVAL)
        {
            m_timer = 0;
            FireSpiral(_bossPos);
            m_shotCount++;
            if (m_shotCount >= AppConst::DANMAKU_COLOR_CHANGE)
            {
                m_shotCount = 0;
                m_isOrange = !m_isOrange;
            }
            m_baseAngle += AppConst::DANMAKU_SPIRAL_ROTATE * 3.14159f / 180.0f;
        }
        break;

    case 3: // 波状
        if (m_timer >= AppConst::DANMAKU_WAVE_INTERVAL)
        {
            m_timer = 0;
            FireWave(_bossPos);
            m_shotCount++;
            if (m_shotCount >= AppConst::DANMAKU_COLOR_CHANGE)
            {
                m_shotCount = 0;
                m_isOrange = !m_isOrange;
            }
            m_waveTimer += AppConst::DANMAKU_WAVE_FREQ;
        }
        break;

    case 4: // 展開弾
        m_expandTimer++;
        if (m_expandTimer >= AppConst::DANMAKU_EXPAND_INTERVAL)
        {
            m_expandTimer = 0;
            FireExpand(_bossPos);
            m_isOrange = !m_isOrange;
        }
        break;
    }
}

void BossDanmaku::FireCircle(Math::Vector2 _pos)
{
    float angleStep = 2.0f * 3.14159f / AppConst::DANMAKU_SHOT_COUNT;
    for (int i = 0; i < AppConst::DANMAKU_SHOT_COUNT; i++)
    {
        auto b = GetFreeBullet();
        if (!b) break;
        float angle = m_baseAngle + angleStep * i;
        b->Fire(_pos, angle, m_isOrange);
        b->SetTex(&m_BlueTex, &m_OrangeTex);
    }
}

void BossDanmaku::FireSpiral(Math::Vector2 _pos)
{
    float angleStep = 2.0f * 3.14159f / AppConst::DANMAKU_SPIRAL_ARMS;
    for (int i = 0; i < AppConst::DANMAKU_SPIRAL_ARMS; i++)
    {
        auto b = GetFreeBullet();
        if (!b) break;
        float angle = m_baseAngle + angleStep * i;
        b->Fire(_pos, angle, m_isOrange);
        b->SetTex(&m_BlueTex, &m_OrangeTex);
    }
}

void BossDanmaku::FireWave(Math::Vector2 _pos)
{
    // 上下に波打ちしながら左方向に発射
     // 左から出現時は右方向、右から出現時は左方向
    float baseAngle = m_fromLeft ? 0.0f : 3.14159f;

    for (int i = 0; i < AppConst::DANMAKU_WAVE_COUNT; i++)
    {
        auto b = GetFreeBullet();
        if (!b) break;

        float waveOffset = sinf(m_waveTimer + i * 0.5f)
            * AppConst::DANMAKU_WAVE_AMPLITUDE
            * 3.14159f / 180.0f;

        float angle = baseAngle + waveOffset;

        b->Fire(_pos, angle, m_isOrange);
        b->SetTex(&m_BlueTex, &m_OrangeTex);
    }
}

void BossDanmaku::FireExpand(Math::Vector2 _pos)
{
    float angleStep = 2.0f * 3.14159f / AppConst::DANMAKU_EXPAND_COUNT;
    for (int i = 0; i < AppConst::DANMAKU_EXPAND_COUNT; i++)
    {
        auto b = GetFreeBullet();
        if (!b) break;

        float angle = angleStep * i;
        b->Fire(_pos, angle, m_isOrange);
        b->SetTex(&m_BlueTex, &m_OrangeTex);

        // 展開モードを設定
        b->SetExpandMode(
            AppConst::DANMAKU_EXPAND_RADIUS,
            AppConst::DANMAKU_EXPAND_STOP_TIME,
            AppConst::DANMAKU_EXPAND_FAST_SPEED
        );
    }
}

void BossDanmaku::Draw()
{
    for (auto& b : m_Bullets)
    {
        if (b && b->IsAlive()) b->Draw();
    }
}

void BossDanmaku::Release()
{
    m_BlueTex.Release();
    m_OrangeTex.Release();
    for (auto& b : m_Bullets)
    {
        if (b) b->Release();
    }
    m_Bullets.clear();
}