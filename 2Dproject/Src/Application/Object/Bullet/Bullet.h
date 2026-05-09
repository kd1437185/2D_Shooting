#pragma once
#include "../BaseObject.h"

class Bullet : public BaseObject
{
public:
    Bullet() {}
    ~Bullet() override {}

    void Init()    override;
    void Update()  override;
    void Draw()    override;
    void Release() override;

    // 発射位置をセットして有効化
    void Fire(Math::Vector2 _startPos, float _direction, int _damage);

    void FireAngle(Math::Vector2 _startPos, float _velX, float _velY, int _damage);

    bool IsAlive() const { return m_aliveFlg; }

    void SetDamage(int _damage) { m_damage = _damage; }
    int  GetDamage()      const { return m_damage; }

private:

    int   m_animFrame = 0;
    int   m_animTimer = 0;
    float m_direction = 1.0f;// 1.0f = 右、-1.0f = 左
    int   m_damage = 1;
    float m_velX = 0.0f;
    float m_velY = 0.0f;

};