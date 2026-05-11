#include "PointItem.h"
#include "Application/AppConst.h"

void PointItem::Init()
{
    m_tex.Load("Texture/Item/score.png");
    m_aliveFlg = false;
    m_collected = false;
    m_value = 0;
    m_autoTimer = 0;
    m_attracting = false;
}

void PointItem::Spawn(Math::Vector2 _pos, int _value)
{
    m_pos = _pos;
    m_aliveFlg = true;
    m_collected = false;
    m_value = _value;
    m_autoTimer = 0;
    m_attracting = false;
    m_playerPos = {};

    m_mat = Math::Matrix::CreateScale(
        AppConst::POINT_SCALE, AppConst::POINT_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}


void PointItem::Collect()
{
    m_collected = false; // フラグリセット
    m_aliveFlg = false;
}

bool PointItem::CheckCollect(Math::Vector2 _playerPos)
{
    if (!m_aliveFlg) return false;

    m_playerPos = _playerPos;

    float dx = _playerPos.x - m_pos.x;
    float dy = _playerPos.y - m_pos.y;
    float dist = sqrtf(dx * dx + dy * dy);

    // 50px以内に入ったら吸い寄せ開始
    if (dist <= AppConst::POINT_COLLECT_DIST)
    {
        m_attracting = true;
    }

    // 自動回収タイマー
    m_autoTimer++;
    if (m_autoTimer >= AppConst::POINT_AUTO_COLLECT)
    {
        m_attracting = true;
    }

    return false; // 回収判定はUpdateに任せる
}

void PointItem::Update()
{
    if (!m_aliveFlg) return;

    if (m_attracting)
    {
        // 吸い寄せ中はプレイヤーに向かう
        float dx = m_playerPos.x - m_pos.x;
        float dy = m_playerPos.y - m_pos.y;
        float dist = sqrtf(dx * dx + dy * dy);

        if (dist < 1.0f)
        {
            m_aliveFlg = false;
            m_collected = true;
            return;
        }

        if (dist > 0.0f)
        {
            // 速度が距離を超えないようにする
            float speed = AppConst::POINT_ATTRACT_SPEED;
            if (speed > dist) speed = dist;

            m_pos.x += (dx / dist) * speed;
            m_pos.y += (dy / dist) * speed;
        }
    }
    else
    {
        // 落下
        m_pos.y -= AppConst::POINT_FALL_SPEED;
        if (m_pos.y < AppConst::POINT_MIN_Y)
        {
            m_pos.y = AppConst::POINT_MIN_Y;
        }
    }

    m_mat = Math::Matrix::CreateScale(
        AppConst::POINT_SCALE, AppConst::POINT_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void PointItem::Draw()
{
    if (!m_aliveFlg) return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex,
        Math::Rectangle{ 0, 0, AppConst::POINT_W, AppConst::POINT_H }, AppConst::POINT_ALPHA);
}

void PointItem::Release()
{
    m_tex.Release();
    m_aliveFlg = false;
}