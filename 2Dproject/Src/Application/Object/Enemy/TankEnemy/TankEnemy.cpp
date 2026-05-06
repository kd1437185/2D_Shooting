#include "TankEnemy.h"
#include "../../../AppConst.h"

void TankEnemy::Init()
{
    m_tex.Load("Texture/Enemy/TankEnemy/D1.png");
    m_aliveFlg = false;
    m_animFrame = 0;
    m_animTimer = 0;
    m_phase = Phase::Drop;
}

void TankEnemy::Spawn(float _x, float _stopY)
{
    m_pos = { _x, AppConst::TANK_SPAWN_Y };
    m_aliveFlg = true;
    m_stopY = _stopY;
    m_phase = Phase::Drop;
    m_animFrame = 0;
    m_animTimer = 0;
}

void TankEnemy::Update()
{
    if (!m_aliveFlg) return;

    // アニメーション更新
    m_animTimer++;
    if (m_animTimer >= AppConst::TANK_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame = (m_animFrame + 1) % AppConst::TANK_ANIM_MAX;
    }

    switch (m_phase)
    {
    case Phase::Drop:
        // 上から下に落下（Y座標を減少）
        m_pos.y -= AppConst::TANK_DROP_SPEED;

        // 停止Y座標に達したら上昇フェーズへ
        if (m_pos.y <= m_stopY)
        {
            m_pos.y = m_stopY;
            m_riseStartY = m_pos.y;
            m_phase = Phase::Rise;
        }
        break;

    case Phase::Rise:
        // 少し上昇（Y座標を増加）
        m_pos.y += AppConst::TANK_RISE_SPEED;

        // 上昇量に達したら停止フェーズへ
        if (m_pos.y >= m_riseStartY + AppConst::TANK_RISE_AMOUNT)
        {
            m_pos.y = m_riseStartY + AppConst::TANK_RISE_AMOUNT;
            m_phase = Phase::Stay;
        }
        break;

    case Phase::Stay:
        // その場に留まる
        break;
    }

    m_mat = Math::Matrix::CreateScale(AppConst::TANK_SCALE, AppConst::TANK_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void TankEnemy::Draw()
{
    if (!m_aliveFlg) return;

    Math::Rectangle srcRect =
    {
        m_animFrame * AppConst::TANK_W,
        0,
        AppConst::TANK_W,
        AppConst::TANK_H
    };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex, srcRect, 1.0f);
}

void TankEnemy::Release()
{
    m_tex.Release();
}