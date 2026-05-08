#include "MobEnemy.h"
#include "../../../AppConst.h"

void MobEnemy::Init()
{
	m_tex.Load("Texture/Enemy/MobEnemy/D3.png");
    m_aliveFlg = false; // 最初は非アクティブ
	m_animFrame = 0;
	m_animTimer = 0;
	m_direction = -1.0f; // 右から左に進むので左向き
    SetHp(AppConst::MOB_HP);
}

void MobEnemy::Spawn(float _x, float _y)
{
    m_pos = { _x, _y };
    m_aliveFlg = true;
    m_direction = -1.0f; // 右から出るので左向き
    m_yReleased = false; // 出現時にリセット
    SetHp(AppConst::MOB_HP);
}


void MobEnemy::Update()
{
    if (!m_aliveFlg) return;

    // アニメーション更新
    m_animTimer++;
    if (m_animTimer >= AppConst::ENEMY_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame = (m_animFrame + 1) % AppConst::ENEMY_ANIM_MAX;
    }

    // 移動
    m_pos.x += AppConst::ENEMY_SPEED * m_direction;

    // 画面端で反転
    if (m_pos.x < -AppConst::SCREEN_HALF_W + AppConst::ENEMY_SCALED_W / 2.0f)
    {
        m_pos.x = -AppConst::SCREEN_HALF_W + AppConst::ENEMY_SCALED_W / 2.0f;
        m_direction = 1.0f; // 右向きに反転
    }
    if (m_pos.x > AppConst::SCREEN_HALF_W - AppConst::ENEMY_SCALED_W / 2.0f)
    {
        m_pos.x = AppConst::SCREEN_HALF_W - AppConst::ENEMY_SCALED_W / 2.0f;
        m_direction = -1.0f; // 左向きに反転
    }

    // 拡大 + 反転を反映した行列
    m_mat = Math::Matrix::CreateScale(m_direction * AppConst::ENEMY_SCALE, AppConst::ENEMY_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void MobEnemy::Draw()
{
    if (!m_aliveFlg) return;

    Math::Rectangle srcRect =
    {
        m_animFrame * AppConst::ENEMY_W,
        0,
        AppConst::ENEMY_W,
        AppConst::ENEMY_H
    };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex, srcRect, 1.0f);
}

void MobEnemy::Release()
{
	m_tex.Release();
}
