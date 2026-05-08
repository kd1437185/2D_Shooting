#include "Bullet.h"
#include "../../AppConst.h"

void Bullet::Init()
{
    m_tex.Load("Texture/Bullet/2_100x100px.png");
    m_aliveFlg = false; // 最初は非アクティブ
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

    // アニメーション更新
    m_animTimer++;
    if (m_animTimer >= AppConst::BULLET_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame = (m_animFrame + 1) % AppConst::BULLET_ANIM_MAX;
    }

    // 移動
    m_pos.x += AppConst::BULLET_SPEED * m_direction;

    // 画面外に出たら非アクティブ
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

    // 横8コマ・縦複数行のスプライトシートから切り抜き
    int col = m_animFrame % AppConst::BULLET_ANIM_COLS;
    int row = m_animFrame / AppConst::BULLET_ANIM_COLS;

    Math::Rectangle srcRect =
    {
        col * AppConst::BULLET_W,
        row * AppConst::BULLET_H,
        AppConst::BULLET_W,
        AppConst::BULLET_H
    };

    // 縮小 + 向きを反映した行列
    Math::Matrix mat = Math::Matrix::CreateScale(
        -AppConst::BULLET_SCALE * m_direction,
        AppConst::BULLET_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

    SHADER.m_spriteShader.SetMatrix(mat);
    SHADER.m_spriteShader.DrawTex(&m_tex, srcRect, 1.0f);
}

void Bullet::Release()
{
    m_tex.Release();
}
