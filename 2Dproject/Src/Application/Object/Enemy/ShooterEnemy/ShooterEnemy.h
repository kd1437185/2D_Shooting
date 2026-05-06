#pragma once
#include "Application/Object/BaseObject.h"

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

private:
    enum class Phase
    {
        Enter,  // ‰E‚©‚çi“ü
        Float   // ã‰ºˆÚ“®
    };

    int   m_animFrame = 0;
    int   m_animTimer = 0;
    float m_direction = -1.0f;
    float m_floatTimer = 0.0f;
    float m_baseY = 0.0f;
    bool  m_yReleased = false;
    Phase m_phase = Phase::Enter;
};