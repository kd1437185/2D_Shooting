#include "WaveManager.h"
#include "../AppConst.h"

// ウェーブの順番
const WaveType WaveManager::WAVE_ORDER[WAVE_ORDER_MAX] =
{
    WaveType::MobEnemy,
    WaveType::Enemy2,
    WaveType::Enemy3,
    WaveType::MobEnemy,
    WaveType::Enemy2,
    WaveType::Enemy3,
    WaveType::Boss
};

// 各ウェーブで倒す必要がある敵の数
const int WaveManager::WAVE_KILL_COUNT[WAVE_ORDER_MAX] =
{
    AppConst::MOB_MAX_WAVE1,  // フェーズ1 MobEnemy
    AppConst::SHOOTER_MAX,
    AppConst::TANK_MAX,
    AppConst::MOB_MAX_WAVE4,  // フェーズ4 MobEnemy
    AppConst::SHOOTER_MAX,
    AppConst::TANK_MAX,
    1                          // Boss
};

void WaveManager::Init()
{
    m_waveIndex = 0;
    m_currentWave = WAVE_ORDER[0];
    m_defeatedCount = 0;
    m_waveClear = false;
}

void WaveManager::OnEnemyDefeated()
{
    m_defeatedCount++;

    if (m_defeatedCount >= WAVE_KILL_COUNT[m_waveIndex])
    {
        NextWave();
    }
}

void WaveManager::NextWave()
{
    m_defeatedCount = 0;
    m_waveIndex++;

    if (m_waveIndex >= WAVE_ORDER_MAX)
    {
        m_currentWave = WaveType::Clear;
    }
    else
    {
        m_currentWave = WAVE_ORDER[m_waveIndex];
    }

    m_waveClear = true; // GameScene に通知
}