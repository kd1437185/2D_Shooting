#pragma once
#include "Application/Object/BaseObject.h"
#include "../../Bullet/EnemyBullet.h"

class ShooterEnemy : public BaseObject
{
public:
    ShooterEnemy() {}
    ~ShooterEnemy() override {}

    void Init()    override;
    void Update()  override;
    void Draw()    override;
    void Release() override;

    void Spawn(float _x, float _y);

    bool IsYReleased() const { return m_yReleased; }
    void SetYReleased(bool _flag) { m_yReleased = _flag; }

    void DrawBullets();
    std::vector<std::shared_ptr<EnemyBullet>>& GetBullets() { return m_Bullets; }

    void Damage(int _amount) override;

private:
    enum class Phase
    {
        Enter,    // 右から横移動で入場
        MoveVert, // 縦移動
        Stay,     // 停止して発射し続ける
    };

    void UpdateEnter();
    void UpdateMoveVert();
    void UpdateStay();
    void Shot3Way();

    int   m_animFrame = 0;
    int   m_animTimer = 0;
    float m_vertDir = 1.0f;
    bool  m_yReleased = false;
    bool  m_fromTop = true;
    int   m_phaseTimer = 0;
    int   m_shotTimer = 0;  // 発射インターバルタイマー
    Phase m_phase = Phase::Enter;

    std::vector<std::shared_ptr<EnemyBullet>> m_Bullets;
};