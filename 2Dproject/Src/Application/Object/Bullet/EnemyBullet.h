#pragma once
#include "../BaseObject.h"
#include "Application/AppConst.h"

class EnemyBullet : public BaseObject
{
public:
    EnemyBullet() {}
    ~EnemyBullet() override {}

    void Init()    override;
    void Update()  override;
    void Draw()    override;
    void Release() override;

    // 発射位置・方向ベクトルを指定して発射
    void Fire(Math::Vector2 _startPos, Math::Vector2 _targetPos);

    bool IsAlive()  const { return m_aliveFlg; }
    void SetAlive(bool b) { m_aliveFlg = b; }
    float GetRadius() const { return AppConst::ENEMY_BULLET_RADIUS; }

private:
    float m_velX = 0.0f;
    float m_velY = 0.0f;
};