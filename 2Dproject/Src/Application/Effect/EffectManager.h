#pragma once
#include "HitEffect.h"

class EffectManager
{
public:
    void Init();
    void Update();
    void Draw();
    void Release();

    void PlayHitEffect(Math::Vector2 _pos); // ヒットエフェクト再生

    // シングルトン
private:
    EffectManager() {}
    ~EffectManager() {}
    EffectManager(const EffectManager&) = delete;
    EffectManager& operator=(const EffectManager&) = delete;

    static const int HIT_POOL_SIZE = 20; // 同時再生数
    HitEffect m_hitEffects[HIT_POOL_SIZE];

public:
    static EffectManager& Instance()
    {
        static EffectManager instance;
        return instance;
    }
};