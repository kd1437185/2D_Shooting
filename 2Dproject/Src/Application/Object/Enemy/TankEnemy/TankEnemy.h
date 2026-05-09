#pragma once
#include "Application/Object/BaseObject.h"
#include "../../Bullet/EnemyBullet.h"

class TankEnemy : public BaseObject
{
public:
    TankEnemy() {}
    ~TankEnemy() override {}

    void Init()    override;
    void Update()  override;
    void Draw()    override;
    void Release() override;

    void Spawn(float _x, float _stopY);

    void DrawBullets();
    std::vector<std::shared_ptr<EnemyBullet>>& GetBullets() { return m_Bullets; }

    void Damage(int _amount) override;

private:
    enum class Phase
    {
        Drop,   // è„Ç©ÇÁóéâ∫
        Rise,   // è≠Çµè„è∏
        Stay    // í‚é~ÅEî≠éÀ
    };

    void UpdateDrop();
    void UpdateRise();
    void UpdateStay();
    void Shot();

    int   m_animFrame = 0;
    int   m_animTimer = 0;
    float m_stopY = 0.0f;
    float m_riseStartY = 0.0f;
    int   m_shotTimer = 0;
    Phase m_phase = Phase::Drop;

    std::vector<std::shared_ptr<EnemyBullet>> m_Bullets;
};