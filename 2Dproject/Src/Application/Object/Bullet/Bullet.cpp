#include "Bullet.h"
#include "../../AppConst.h"

void Bullet::Init()
{
    m_tex.Load("Texture/Bullet/15.png");
    m_aliveFlg = false;
    m_animFrame = 0;
    m_animTimer = 0;
}

void Bullet::Fire(Math::Vector2 _startPos, float _direction, int _damage)
{
    m_pos = _startPos;
    m_direction = _direction;
    m_aliveFlg = true;
    m_damage = _damage;
    m_animFrame = 0;
    m_animTimer = 0;
}

void Bullet::Update()
{
    if (!m_aliveFlg) return;

    m_pos.x += AppConst::BULLET_SPEED * m_direction;

    if (m_pos.x > AppConst::SCREEN_HALF_W + AppConst::BULLET_SCALED_W ||
        m_pos.x < -AppConst::SCREEN_HALF_W - AppConst::BULLET_SCALED_W)
    {
        m_aliveFlg = false;
    }

    m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void Bullet::Draw()
{
    if (!m_aliveFlg) return;

    Math::Matrix mat = Math::Matrix::CreateScale(
        AppConst::BULLET_SCALE * m_direction,
        AppConst::BULLET_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

    SHADER.m_spriteShader.SetMatrix(mat);
    SHADER.m_spriteShader.DrawTex(&m_tex,
        Math::Rectangle{ 0, 0, AppConst::BULLET_W, AppConst::BULLET_H }, AppConst::BULLET_ALPHA);
}

void Bullet::Release()
{
    m_tex.Release();
}
