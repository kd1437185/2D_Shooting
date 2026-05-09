#include "EffectManager.h"

void EffectManager::Init()
{
    for (int i = 0; i < HIT_POOL_SIZE; i++)
    {
        m_hitEffects[i].Init();
    }
}

void EffectManager::Update()
{
    for (int i = 0; i < HIT_POOL_SIZE; i++)
    {
        m_hitEffects[i].Update();
    }
}

void EffectManager::Draw()
{
    for (int i = 0; i < HIT_POOL_SIZE; i++)
    {
        m_hitEffects[i].Draw();
    }
}

void EffectManager::Release()
{
    for (int i = 0; i < HIT_POOL_SIZE; i++)
    {
        m_hitEffects[i].Release();
    }
}

void EffectManager::PlayHitEffect(Math::Vector2 _pos)
{
    // 再生中でないエフェクトを探して再生
    for (int i = 0; i < HIT_POOL_SIZE; i++)
    {
        if (!m_hitEffects[i].IsPlaying())
        {
            m_hitEffects[i].Play(_pos);
            return;
        }
    }
}