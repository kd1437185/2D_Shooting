#include "MobEnemy.h"
#include "../../../AppConst.h"

void MobEnemy::Init()
{
    m_tex.Load("Texture/Enemy/MobEnemy/D3.png");
    m_aliveFlg = false;
    m_animFrame = 0;
    m_animTimer = 0;
    m_phase = Phase::Enter;

    // 弾プールを生成
    for (int i = 0; i < AppConst::ENEMY_BULLET_MAX; i++)
    {
        auto b = std::make_shared<EnemyBullet>();
        b->Init();
        m_Bullets.push_back(b);
    }
}

void MobEnemy::Spawn(bool _fromRight, Math::Vector2* _playerPos)
{
    m_fromRight = _fromRight;
    m_playerPos = _playerPos;
    m_aliveFlg = true;
    m_animFrame = 0;
    m_animTimer = 0;
    m_phaseTimer = 0;
    m_phase = Phase::Enter;
    m_yReleased = false;
    m_escaped = false;
    m_isFading = false;
    m_alpha = 1.0f;

    // 上から来るか下から来るかをランダムに決定
    m_fromTop = (rand() % 2 == 0);

    float angleRad = AppConst::MOB_ANGLE * 3.14159f / 180.0f;

    if (_fromRight)
    {
        // 右側から出現
        float spawnX = AppConst::SCREEN_HALF_W + AppConst::ENEMY_SCALED_W;
        float spawnY = m_fromTop
            ? AppConst::SCREEN_HALF_H + AppConst::ENEMY_SCALED_H  // 上から
            : -(AppConst::SCREEN_HALF_H + AppConst::ENEMY_SCALED_H); // 下から

        m_pos = { spawnX, spawnY };
        m_direction = -1.0f; // 左向き

        // 右上から来る場合は左下へ、右下から来る場合は左上へ
        m_velX = -AppConst::MOB_ENTER_SPEED * cosf(angleRad);
        m_velY = m_fromTop
            ? -AppConst::MOB_ENTER_SPEED * sinf(angleRad)  // 左下へ
            : AppConst::MOB_ENTER_SPEED * sinf(angleRad); // 左上へ
    }
    else
    {
        // 左側から出現
        float spawnX = -(AppConst::SCREEN_HALF_W + AppConst::ENEMY_SCALED_W);
        float spawnY = m_fromTop
            ? AppConst::SCREEN_HALF_H + AppConst::ENEMY_SCALED_H
            : -(AppConst::SCREEN_HALF_H + AppConst::ENEMY_SCALED_H);

        m_pos = { spawnX, spawnY };
        m_direction = 1.0f; // 右向き

        // 左上から来る場合は右下へ、左下から来る場合は右上へ
        m_velX = AppConst::MOB_ENTER_SPEED * cosf(angleRad);
        m_velY = m_fromTop
            ? -AppConst::MOB_ENTER_SPEED * sinf(angleRad)
            : AppConst::MOB_ENTER_SPEED * sinf(angleRad);
    }

    SetHp(AppConst::MOB_HP);
}

void MobEnemy::Update()
{
    // 弾の更新は aliveFlg に関係なく常に行う
    for (auto& b : m_Bullets)
    {
        if (b) b->Update();
    }

    // フェードアウト中
    if (m_isFading)
    {
        UpdateFade();
        return;
    }

    if (!m_aliveFlg) return; // 敵本体は死んでいたらここで終了

    // アニメーション更新
    m_animTimer++;
    if (m_animTimer >= AppConst::ENEMY_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame = (m_animFrame + 1) % AppConst::ENEMY_ANIM_MAX;
    }

    m_phaseTimer++;

    switch (m_phase)
    {
    case Phase::Enter: UpdateEnter(); break;
    case Phase::Slow:  UpdateSlow();  break;
    case Phase::Shot:  UpdateShot();  break;
    case Phase::Leave: UpdateLeave(); break;
    }

    m_mat = Math::Matrix::CreateScale(
        m_direction * AppConst::ENEMY_SCALE, AppConst::ENEMY_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void MobEnemy::UpdateEnter()
{
    m_pos.x += m_velX;
    m_pos.y += m_velY;

    // 画面内に入ったら減速フェーズへ
    if (m_pos.x < AppConst::SCREEN_HALF_W - AppConst::MOB_SPAWN_X_MARGIN &&
        m_pos.x > -(AppConst::SCREEN_HALF_W - AppConst::MOB_SPAWN_X_MARGIN) &&
        m_pos.y < AppConst::SCREEN_HALF_H &&
        m_pos.y > -AppConst::SCREEN_HALF_H)
    {
        m_phaseTimer = 0;
        m_phase = Phase::Slow;
    }
}

void MobEnemy::UpdateSlow()
{
    // 徐々に減速
    float t = (float)m_phaseTimer / AppConst::MOB_SLOW_DURATION;
    float speed = AppConst::MOB_ENTER_SPEED + (AppConst::MOB_SLOW_SPEED - AppConst::MOB_ENTER_SPEED) * t;

    float len = sqrtf(m_velX * m_velX + m_velY * m_velY);
    if (len > 0.0f)
    {
        m_pos.x += (m_velX / len) * speed;
        m_pos.y += (m_velY / len) * speed;
    }

    if (m_phaseTimer >= AppConst::MOB_SLOW_DURATION)
    {
        m_phaseTimer = 0;
        m_phase = Phase::Shot;
    }
}

void MobEnemy::UpdateShot()
{
    // 発射フェーズ：プレイヤーに向けて1発撃つ
    if (m_phaseTimer == 1 && m_playerPos)
    {
        for (auto& b : m_Bullets)
        {
            if (b && !b->IsAlive())
            {
                b->Fire(m_pos, *m_playerPos);
                break;
            }
        }
    }

    // 少し待ってから退場
    if (m_phaseTimer >= 10)
    {
        m_phaseTimer = 0;
        m_phase = Phase::Leave;
    }
}

void MobEnemy::UpdateLeave()
{
    // 侵入方向の逆に加速して退場
    m_pos.x += m_velX;
    m_pos.y += m_velY;

    // 画面外に出たら非アクティブ
    if (m_pos.x > AppConst::SCREEN_HALF_W + AppConst::ENEMY_SCALED_W * 2 ||
        m_pos.x < -AppConst::SCREEN_HALF_W - AppConst::ENEMY_SCALED_W * 2 ||
        m_pos.y >  AppConst::SCREEN_HALF_H + AppConst::ENEMY_SCALED_H * 2 ||
        m_pos.y < -AppConst::SCREEN_HALF_H - AppConst::ENEMY_SCALED_H * 2)
    {
        m_aliveFlg = false;
        m_escaped = true; // 逃げたフラグ
    }
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
    SHADER.m_spriteShader.DrawTex(&m_tex, srcRect, m_alpha);
}

void MobEnemy::DrawBullets()
{
    for (auto& b : m_Bullets)
    {
        if (b && b->IsAlive()) b->Draw();
    }
}

void MobEnemy::Release()
{
    m_tex.Release();
    for (auto& b : m_Bullets)
    {
        if (b) b->Release();
    }
    m_Bullets.clear();
}

void MobEnemy::Damage(int _amount)
{
    m_hp -= _amount;
    if (m_hp <= 0)
    {
        m_hp = 0;
        StartFadeOut(); // フェードアウト開始
    }
}