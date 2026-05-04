#include "Bullet.h"
#include "../../AppConst.h"

void Bullet::Init()
{
    m_tex.Load("Texture/Bullet/bullet.png");
    m_aliveFlg = false; // 最初は非アクティブ
}

void Bullet::Fire(Math::Vector2 _startPos)
{
    m_pos = _startPos;
    m_aliveFlg = true;
}

void Bullet::Update()
{
    if (!m_aliveFlg) return;

    // 右に進む
    m_pos.x += AppConst::BULLET_SPEED;

    // 画面外に出たら非アクティブ
    if (m_pos.x > AppConst::SCREEN_HALF_W + AppConst::BULLET_SIZE)
    {
        m_aliveFlg = false;
    }

    m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void Bullet::Draw()
{
    if (!m_aliveFlg) return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex,
        Math::Rectangle{ 0, 0, AppConst::BULLET_SIZE, AppConst::BULLET_SIZE }, 1.0f);
}

void Bullet::Release()
{
    m_tex.Release();
}
