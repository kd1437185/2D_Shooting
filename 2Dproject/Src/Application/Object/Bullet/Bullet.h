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
    void Fire(Math::Vector2 _startPos);

    bool IsAlive() const { return m_aliveFlg; }
};