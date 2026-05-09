#include "EnemyBullet.h"
#include "Application/AppConst.h"

void EnemyBullet::Init()
{
    m_tex.Load("Texture/Bullet/Enemy_bullet_blue.png");
    m_aliveFlg = false;
    m_velX = 0.0f;
    m_velY = 0.0f;
}

void EnemyBullet::Fire(Math::Vector2 _startPos, Math::Vector2 _targetPos)
{
    m_pos = _startPos;
    m_aliveFlg = true;

    // 目標方向のベクトルを計算
    float dx = _targetPos.x - _startPos.x;
    float dy = _targetPos.y - _startPos.y;
    float len = sqrtf(dx * dx + dy * dy);
    if (len > 0.0f)
    {
        m_velX = (dx / len) * AppConst::ENEMY_BULLET_SPEED;
        m_velY = (dy / len) * AppConst::ENEMY_BULLET_SPEED;
    }
}

void EnemyBullet::Update()
{
    if (!m_aliveFlg) return;

    m_pos.x += m_velX;
    m_pos.y += m_velY;

    // 画面外に出たら消える
    if (m_pos.x > AppConst::SCREEN_HALF_W + 50 ||
        m_pos.x < -AppConst::SCREEN_HALF_W - 50 ||
        m_pos.y >  AppConst::SCREEN_HALF_H + 50 ||
        m_pos.y < -AppConst::SCREEN_HALF_H - 50)
    {
        m_aliveFlg = false;
    }

    m_mat = Math::Matrix::CreateScale(
        AppConst::ENEMY_BULLET_SCALE, AppConst::ENEMY_BULLET_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void EnemyBullet::Draw()
{
    if (!m_aliveFlg) return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex,
        Math::Rectangle{ 0, 0, AppConst::ENEMY_BULLET_W, AppConst::ENEMY_BULLET_H },
        AppConst::ENEMY_BULLET_ALPHA);
}

void EnemyBullet::Release()
{
    m_tex.Release();
    m_aliveFlg = false;
}