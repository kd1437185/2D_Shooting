#include "Boss.h"
#include "../../../AppConst.h"
#include "../../../Sound/SoundManager.h"

void Boss::Init()
{
    m_IdleBeforeTex.Load("Texture/Enemy/Boss/Idle_Before.png");
    m_TransformTex.Load("Texture/Enemy/Boss/Transform.png");
    m_IdleAfterTex.Load("Texture/Enemy/Boss/Idle_After.png");
    m_Attack1Tex.Load("Texture/Enemy/Boss/Attack_1.png");
    m_Attack2Tex.Load("Texture/Enemy/Boss/Attack_2.png");
    m_DeathTex.Load("Texture/Enemy/Boss/Death.png");
    m_aliveFlg = false;
    m_animFrame = 0;
    m_animTimer = 0;
    m_attackTimer = 0;
    m_prevWasIdle = false;
    m_fromLeft = false;
    m_phase = Phase::Enter;
    SetHp(AppConst::BOSS_HP);
    m_NameTex.Load("Texture/Enemy/Boss/bossname.png");
    m_nameAlpha = 0.0f;
    m_nameHoldTimer = 0;
    m_namePhase = NamePhase::None;
    m_danmaku.Init();
}

void Boss::Spawn()
{
    m_pos = { AppConst::BOSS_SPAWN_X, AppConst::BOSS_STOP_Y };
    m_aliveFlg = true;
    m_animFrame = 0;
    m_animTimer = 0;
    m_attackTimer = 0;
    m_prevWasIdle = false;
    m_fromLeft = false;
    m_deathFinished = false;
    m_phase = Phase::Enter;
    m_danmaku.Stop();
    m_danmakuTimer = 0;
}

void Boss::TriggerDeath()
{
    m_animFrame = 0;
    m_animTimer = 0;
    m_phase = Phase::Death;
}

void Boss::Update()
{
    if (!m_aliveFlg) return;

    m_animTimer++;

    switch (m_phase)
    {
    case Phase::Enter:      UpdateEnter();      break;
    case Phase::IdleBefore: UpdateIdleBefore(); break;
    case Phase::Transform:  UpdateTransform();  break;
    case Phase::Battle:     UpdateBattle();     break;
    case Phase::Attack1:    UpdateAttack1();    break;
    case Phase::Attack2:    UpdateAttack2();    break;
    case Phase::Death:      UpdateDeath();      break;
    case Phase::EnterFromLeft: UpdateEnterFromLeft(); break;
    }

    // 名前のアルファ更新
    switch (m_namePhase)
    {
    case NamePhase::FadeIn:
        m_nameAlpha += AppConst::BOSS_NAME_FADE_IN;
        if (m_nameAlpha >= 1.0f)
        {
            m_nameAlpha = 1.0f;
            m_nameHoldTimer = 0;
            m_namePhase = NamePhase::Hold;
        }
        break;

    case NamePhase::Hold:
        m_nameHoldTimer++;
        if (m_nameHoldTimer >= AppConst::BOSS_NAME_HOLD)
        {
            m_namePhase = NamePhase::FadeOut;
        }
        break;

    case NamePhase::FadeOut:
        m_nameAlpha -= AppConst::BOSS_NAME_FADE_OUT;
        if (m_nameAlpha <= 0.0f)
        {
            m_nameAlpha = 0.0f;
            m_namePhase = NamePhase::None;
        }
        break;

    default: break;
    }

    // 内部タイマーで弾幕制御・パターン切り替え
    if (m_phase == Phase::Battle ||
        m_phase == Phase::Attack1 ||
        m_phase == Phase::Attack2)
    {
        m_danmakuTimer++;

        // 最初の起動
        if (!m_danmaku.IsActive() && m_danmakuTimer >= 60)
        {
            m_currentPattern = 1;
            m_danmaku.SetPattern(m_currentPattern);
            m_danmaku.Start();
            m_patternTimer = 0;
        }

        // 一定時間でパターンを切り替え
        if (m_danmaku.IsActive())
        {
            m_patternTimer++;
            if (m_patternTimer >= 600)
            {
                m_patternTimer = 0;

                // ランダムで次のパターンを選ぶ（同じパターンが連続しないように）
                int next = m_currentPattern;
                while (next == m_currentPattern)
                {
                    next = (rand() % 4) + 1;
                }
                m_currentPattern = next;
                m_danmaku.SetPattern(m_currentPattern);
            }
        }
    }
    else
    {
        m_danmaku.Stop();
        m_danmakuTimer = 0;
    }

    m_danmaku.SetFromLeft(m_fromLeft);
    m_danmaku.Update(m_pos, m_playerPos);

    float scaleX = m_fromLeft ? AppConst::BOSS_SCALE : -AppConst::BOSS_SCALE;
    m_mat = Math::Matrix::CreateScale(scaleX, AppConst::BOSS_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void Boss::UpdateEnter()
{
    if (m_animTimer >= AppConst::BOSS_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame = (m_animFrame + 1) % AppConst::BOSS_IDLE_ANIM_MAX;
    }

    m_pos.x -= AppConst::BOSS_ENTER_SPEED;

    if (m_pos.x <= AppConst::BOSS_STOP_X)
    {
        m_pos.x = AppConst::BOSS_STOP_X;
        m_animFrame = 0;
        m_animTimer = 0;
        m_phase = Phase::IdleBefore;

        // 右から来たボスのみBGM切り替え
        if (!m_fromLeft)
        {
            SoundManager::Instance().PlayBossBGM();
        }
    }
}

void Boss::UpdateIdleBefore()
{
    if (m_animTimer >= AppConst::BOSS_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame++;

        if (m_animFrame >= AppConst::BOSS_IDLE_ANIM_MAX)
        {
            m_animFrame = 0;
            m_phase = Phase::Transform;
        }
    }
}

void Boss::UpdateTransform()
{
    if (m_animTimer >= AppConst::BOSS_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame++;

        if (m_animFrame >= AppConst::BOSS_TRANS_ANIM_MAX)
        {
            m_animFrame = 0;
            m_attackTimer = AppConst::BOSS_ATTACK_INTERVAL;
            m_phase = Phase::Battle;

            // 右から来たボスのみ名前を表示
            if (!m_fromLeft)
            {
                m_namePhase = NamePhase::FadeIn;
                m_nameAlpha = 0.0f;
                m_nameHoldTimer = 0;
            }
        }
    }
}

void Boss::UpdateBattle()
{
    // 待機アニメループ
    if (m_animTimer >= AppConst::BOSS_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame = (m_animFrame + 1) % AppConst::BOSS_IDLE_AFTER_ANIM_MAX;
    }

    // 攻撃タイマー
    m_attackTimer--;
    if (m_attackTimer <= 0)
    {
        SelectNextPattern();
    }
}

void Boss::UpdateAttack1()
{
    if (m_animTimer >= AppConst::BOSS_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame++;

        // アニメ完了で待機に戻る
        if (m_animFrame >= AppConst::BOSS_ATTACK1_ANIM_MAX)
        {
            m_animFrame = 0;
            m_attackTimer = AppConst::BOSS_ATTACK_INTERVAL;
            m_prevWasIdle = false;
            m_phase = Phase::Battle;
        }
    }
}

void Boss::UpdateAttack2()
{
    if (m_animTimer >= AppConst::BOSS_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame++;

        // アニメ完了で待機に戻る
        if (m_animFrame >= AppConst::BOSS_ATTACK2_ANIM_MAX)
        {
            m_animFrame = 0;
            m_attackTimer = AppConst::BOSS_ATTACK_INTERVAL;
            m_prevWasIdle = false;
            m_phase = Phase::Battle;
        }
    }
}

void Boss::UpdateDeath()
{
    // 落下しながらアニメーション
    m_pos.y -= AppConst::BOSS_DEATH_FALL_SPEED;

    if (m_animTimer >= AppConst::BOSS_DEATH_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame++;

        if (m_animFrame >= AppConst::BOSS_DEATH_ANIM_MAX ||
            m_pos.y < -AppConst::SCREEN_HALF_H - AppConst::BOSS_H)
        {
            if (m_fromLeft)
            {
                // 左から来たボスを倒した → クリア
                m_deathFinished = true;
                m_aliveFlg = false;
            }
            else
            {
                // 右から来たボスを倒した → 左から再登場
                m_pos = { AppConst::BOSS_SPAWN_X_LEFT, AppConst::BOSS_STOP_Y };
                m_animFrame = 0;
                m_animTimer = 0;
                m_fromLeft = true;
                SetHp(AppConst::BOSS_HP);
                m_phase = Phase::EnterFromLeft;
            }
        }
    }
}

void Boss::UpdateEnterFromLeft()
{
    // 左からゆっくり右に移動
    if (m_animTimer >= AppConst::BOSS_ANIM_SPEED)
    {
        m_animTimer = 0;
        m_animFrame = (m_animFrame + 1) % AppConst::BOSS_IDLE_ANIM_MAX;
    }

    m_pos.x += AppConst::BOSS_ENTER_SPEED;

    if (m_pos.x >= -AppConst::BOSS_STOP_X)
    {
        m_pos.x = -AppConst::BOSS_STOP_X;
        m_animFrame = 0;
        m_animTimer = 0;
        // m_fromLeft = false は削除！左から登場後もそのまま
        m_phase = Phase::IdleBefore;
    }
}

void Boss::SelectNextPattern()
{
    // 0: Attack1, 1: Attack2, 2: 待機（ただし連続待機は禁止）
    int pattern = rand() % 3;

    // 前回が待機なら待機以外を選ぶ
    if (m_prevWasIdle && pattern == 2)
    {
        pattern = rand() % 2; // 0 か 1 のみ
    }

    m_animFrame = 0;
    m_animTimer = 0;

    switch (pattern)
    {
    case 0:
        m_prevWasIdle = false;
        m_phase = Phase::Attack1;
        break;
    case 1:
        m_prevWasIdle = false;
        m_phase = Phase::Attack2;
        break;
    case 2:
        m_prevWasIdle = true;
        m_attackTimer = AppConst::BOSS_ATTACK_INTERVAL;
        // Battle のまま（待機継続）
        break;
    }
}


void Boss::Draw()
{
    if (!m_aliveFlg) return;

    KdTexture* tex = nullptr;
    int        h = AppConst::BOSS_H;

    switch (m_phase)
    {
    case Phase::Enter:
    case Phase::IdleBefore:
    case Phase::EnterFromLeft:
        tex = &m_IdleBeforeTex;
        h = AppConst::BOSS_H;
        break;
    case Phase::Transform:
        tex = &m_TransformTex;
        h = AppConst::BOSS_H;
        break;
    case Phase::Battle:
        tex = &m_IdleAfterTex;
        h = AppConst::BOSS_H_AFTER;
        break;
    case Phase::Attack1:
        tex = &m_Attack1Tex;
        h = AppConst::BOSS_ATTACK_H;
        break;
    case Phase::Attack2:
        tex = &m_Attack2Tex;
        h = AppConst::BOSS_ATTACK_H;
        break;
    case Phase::Death:
        tex = &m_DeathTex;
        h = AppConst::BOSS_H;
        break;
    }

    if (!tex) return;

    Math::Rectangle srcRect =
    {
        m_animFrame * AppConst::BOSS_W,
        0,
        AppConst::BOSS_W,
        h
    };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(tex, srcRect, 1.0f);

}

void Boss::Release()
{
    m_IdleBeforeTex.Release();
    m_TransformTex.Release();
    m_IdleAfterTex.Release();
    m_Attack1Tex.Release();
    m_Attack2Tex.Release();
    m_DeathTex.Release();
    m_NameTex.Release();
    m_danmaku.Release();

}

void Boss::Damage(int _amount)
{
    m_hp -= _amount;
    if (m_hp <= 0)
    {
        m_hp = 0;
        // aliveFlg は false にしない 死亡モーション後に処理する
        TriggerDeath();
    }
}

void Boss::DrawName()
{
    if (m_namePhase == NamePhase::None || m_nameAlpha <= 0.0f) return;

    Math::Matrix mat = Math::Matrix::CreateTranslation(
        m_pos.x,
        m_pos.y + AppConst::BOSS_NAME_OFFSET_Y,
        0);

    SHADER.m_spriteShader.SetMatrix(mat);
    SHADER.m_spriteShader.DrawTex(&m_NameTex,
        Math::Rectangle{ 0, 0, AppConst::BOSS_NAME_W, AppConst::BOSS_NAME_H },
        m_nameAlpha);
}