#pragma once
#include "Application/Object/BaseObject.h"

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

private:
    enum class Phase
    {
        Drop,   // 上から落下
        Rise,   // 少し上昇
        Stay    // 停止
    };

    int   m_animFrame = 0;
    int   m_animTimer = 0;
    float m_stopY = 0.0f;  // 停止Y座標
    float m_riseStartY = 0.0f; // 上昇開始Y座標
    Phase m_phase = Phase::Drop;
};