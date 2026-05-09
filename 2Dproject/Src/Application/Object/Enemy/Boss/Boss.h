#pragma once
#include "Application/Object/BaseObject.h"

class Boss : public BaseObject
{
public:
    Boss() {}
    ~Boss() override {}

    void Init()    override;
    void Update()  override;
    void Draw()    override;
    void Release() override;

    void Spawn();

    void TriggerDeath(); // 死亡トリガー

    bool IsTransformDone() const { return m_phase == Phase::Battle; }

    enum class Phase
    {
        Enter,      // 入場
        IdleBefore, // 入場後待機
        Transform,  // 変身
        Battle,     // 戦闘待機（当たり判定あり）
        Attack1,  // 攻撃1
        Attack2,  // 攻撃2
        Death,        // 死亡
        EnterFromLeft // 左から再登場
    };

    // 当たり判定が有効かどうか
    bool IsCollidable() const
    {
        return m_phase == Phase::Battle ||
            m_phase == Phase::Attack1 ||
            m_phase == Phase::Attack2;
    }
    Phase GetPhase() const { return m_phase; }

    void Damage(int _amount) override;

    bool IsFromLeft() const { return m_fromLeft; }

    bool IsDeathFinished() const { return m_deathFinished; }

    void ResetDeathFinished() { m_deathFinished = false; }

    void DrawName();

private:
    void UpdateEnter();
    void UpdateIdleBefore();
    void UpdateTransform();
    void UpdateBattle();
    void UpdateAttack1();
    void UpdateAttack2();
    void UpdateDeath();
    void UpdateEnterFromLeft();

    void SelectNextPattern(); // 次の攻撃パターンを選ぶ

    KdTexture m_IdleBeforeTex;
    KdTexture m_TransformTex;
    KdTexture m_IdleAfterTex;
    KdTexture m_Attack1Tex;
    KdTexture m_Attack2Tex;
    KdTexture m_DeathTex;

    int   m_animFrame = 0;
    int   m_animTimer = 0;
    int   m_attackTimer = 0; // 攻撃間隔タイマー
    bool  m_prevWasIdle = false; // 前回が待機だったか
    bool  m_fromLeft = false; // 左から登場中か

    bool m_deathFinished = false;

    Phase m_phase = Phase::Enter;

    KdTexture m_NameTex;
    float     m_nameAlpha = 0.0f;
    int       m_nameHoldTimer = 0;
    bool      m_nameVisible = false; // 名前表示フラグ

    enum class NamePhase
    {
        None,
        FadeIn,
        Hold,
        FadeOut
    };
    NamePhase m_namePhase = NamePhase::None;
};