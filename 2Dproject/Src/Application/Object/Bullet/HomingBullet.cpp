#include "HomingBullet.h"
#include "../../AppConst.h"

void HomingBullet::Init()
{
    m_tex.Load("Texture/Bullet/Bullet_Homing.png");
    m_aliveFlg = false;
    m_velX = 0.0f;
    m_velY = 0.0f;
    m_lifetime = 0;
    m_animFrame = 0;
    m_animTimer = 0;
}

void HomingBullet::Fire(Math::Vector2 _startPos, float _direction, int _damage,
    std::vector<std::shared_ptr<BaseObject>>* _enemies,
    std::shared_ptr<BaseObject>* _boss)
{
    m_pos = _startPos;
    m_aliveFlg = true;
    m_damage = _damage;
    m_enemies = _enemies;
    m_boss = _boss;
    m_velX = AppConst::HOMING_SPEED * _direction;
    m_velY = 0.0f;
    m_lifetime = 0;
    m_animFrame = 0;
    m_animTimer = 0;
}

void HomingBullet::Update()
{
    if (!m_aliveFlg) return;

    // 生存時間チェック
    m_lifetime++;
    if (m_lifetime >= AppConst::HOMING_LIFETIME)
    {
        m_aliveFlg = false;
        return;
    }

    // アニメーション更新
    m_animTimer++;
    if (m_animTimer >= AppConst::HOMING_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame = (m_animFrame + 1) % AppConst::HOMING_ANIM_MAX;
    }

    // 最も近い敵を探す
    BaseObject* target = nullptr;
    float       minDist = FLT_MAX;

    if (m_enemies)
    {
        for (auto& e : *m_enemies)
        {
            if (!e || !e->IsAlive()) continue;
            float dx = e->GetPos().x - m_pos.x;
            float dy = e->GetPos().y - m_pos.y;
            float dist = dx * dx + dy * dy;
            if (dist < minDist)
            {
                minDist = dist;
                target = e.get();
            }
        }
    }

    // ボスも対象に
    if (m_boss && *m_boss && (*m_boss)->IsAlive())
    {
        float dx = (*m_boss)->GetPos().x - m_pos.x;
        float dy = (*m_boss)->GetPos().y - m_pos.y;
        float dist = dx * dx + dy * dy;
        if (dist < minDist)
        {
            minDist = dist;
            target = m_boss->get();
        }
    }

    // ターゲットに向かって旋回
    if (target)
    {
        float dx = target->GetPos().x - m_pos.x;
        float dy = target->GetPos().y - m_pos.y;
        float len = sqrtf(dx * dx + dy * dy);
        if (len > 0.0f)
        {
            float targetVX = (dx / len) * AppConst::HOMING_SPEED;
            float targetVY = (dy / len) * AppConst::HOMING_SPEED;
            m_velX += (targetVX - m_velX) * AppConst::HOMING_TURN_SPEED;
            m_velY += (targetVY - m_velY) * AppConst::HOMING_TURN_SPEED;
        }
    }

    m_pos.x += m_velX;
    m_pos.y += m_velY;

    // 画面外に出たら消える
    if (m_pos.x > AppConst::SCREEN_HALF_W + 100 ||
        m_pos.x < -AppConst::SCREEN_HALF_W - 100 ||
        m_pos.y >  AppConst::SCREEN_HALF_H + 100 ||
        m_pos.y < -AppConst::SCREEN_HALF_H - 100)
    {
        m_aliveFlg = false;
        return;
    }

    m_mat = Math::Matrix::CreateScale(
        AppConst::HOMING_SCALE, AppConst::HOMING_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void HomingBullet::Draw()
{
    if (!m_aliveFlg) return;

    Math::Rectangle srcRect =
    {
        m_animFrame * AppConst::HOMING_W,
        0,
        AppConst::HOMING_W,
        AppConst::HOMING_H
    };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex, srcRect, AppConst::HOMING_ALPHA);

}

void HomingBullet::Release()
{
    m_tex.Release();
    m_aliveFlg = false;

}