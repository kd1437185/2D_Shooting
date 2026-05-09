#pragma once
#include "../BaseObject.h"

class BaseObject;

class HomingBullet : public BaseObject
{
public:
    HomingBullet() {}
    ~HomingBullet() override {}

    void Init()    override;
    void Update()  override;
    void Draw()    override;
    void Release() override;

    void Fire(Math::Vector2 _startPos, float _direction, int _damage,
        std::vector<std::shared_ptr<BaseObject>>* _enemies,
        std::shared_ptr<BaseObject>* _boss);

    bool IsAlive()  const { return m_aliveFlg; }
    void SetAlive(bool b) { m_aliveFlg = b; }
    int  GetDamage() const { return m_damage; }

private:
    std::vector<std::shared_ptr<BaseObject>>* m_enemies = nullptr;
    std::shared_ptr<BaseObject>* m_boss = nullptr;

    float m_velX = 0.0f;
    float m_velY = 0.0f;
    int   m_damage = 1;
    int   m_lifetime = 0;   // 生存タイマー
    int   m_animFrame = 0;
    int   m_animTimer = 0;
};