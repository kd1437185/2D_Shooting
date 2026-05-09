#pragma once
#include "Application/Object/BaseObject.h"
#include "../../Bullet/EnemyBullet.h"

class MobEnemy : public BaseObject
{
public:
    MobEnemy() {}
    ~MobEnemy() override {}

    void Init()    override;
    void Update()  override;
    void Draw()    override;
    void Release() override;

    // 出現パターン指定（fromRight=右側から、fromRight=falseで左側から）
    void Spawn(bool _fromRight, Math::Vector2* _playerPos);

    bool IsYReleased() const { return m_yReleased; }
    void SetYReleased(bool _flag) { m_yReleased = _flag; }

    // 敵弾の描画（プレイヤーより上に描画するため外部から呼ぶ）
    void DrawBullets();

    std::vector<std::shared_ptr<EnemyBullet>>& GetBullets() { return m_Bullets; }

    bool IsEscaped() const { return m_escaped; }
    void ResetEscaped() { m_escaped = false; }
    void Damage(int _amount) override;

private:
    enum class Phase
    {
        Enter,  // 侵入
        Slow,   // 減速
        Shot,   // 発射
        Leave   // 退場
    };

    void UpdateEnter();
    void UpdateSlow();
    void UpdateShot();
    void UpdateLeave();

    int   m_animFrame = 0;
    int   m_animTimer = 0;
    float m_velX = 0.0f;
    float m_velY = 0.0f;
    float m_direction = -1.0f;
    bool  m_yReleased = false;
    bool  m_fromRight = true;
    bool  m_fromTop = true;
    int   m_phaseTimer = 0;
    bool m_escaped = false;
    Phase m_phase = Phase::Enter;

    Math::Vector2* m_playerPos = nullptr;

    std::vector<std::shared_ptr<EnemyBullet>> m_Bullets;
};