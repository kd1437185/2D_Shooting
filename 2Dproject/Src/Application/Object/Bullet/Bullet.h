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

    bool IsAlive() const { return m_aliveFlg; }

    void SetDamage(int _damage) { m_damage = _damage; }
    int  GetDamage()      const { return m_damage; }

private:

    int   m_animFrame = 0;
    int   m_animTimer = 0;
    // 1.0f = 右、-1.0f = 左
    float m_direction = 1.0f;
    int   m_damage = 1;

};