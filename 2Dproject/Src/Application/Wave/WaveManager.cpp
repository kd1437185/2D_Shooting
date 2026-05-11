#include "WaveManager.h"
#include "../AppConst.h"

// ウェーブの定義
// spawnMob, spawnShooter, spawnTank, spawnBoss, mobCount, shooterCount, tankCount, repeatCount
const WaveData WaveManager::WAVE_LIST[WAVE_COUNT] =
{
    { true,  false, false, false, AppConst::MOB_MAX_WAVE1, 0,                      0,                   1 }, // フェーズ1: MobEnemy
    { false, true,  false, false, 0,                       AppConst::SHOOTER_MAX,  0,                   1 }, // フェーズ2: ShooterEnemy
    { false, false, true,  false, 0,                       0,                      AppConst::TANK_MAX,  1 }, // フェーズ3: TankEnemy
    { true,  false, false, false, AppConst::MOB_MAX_WAVE4, AppConst::SHOOTER_MAX,  0,                   1 }, // フェーズ4: MobEnemy
    { true,  true,  true,  false, AppConst::MOB_MAX_WAVE4, AppConst::SHOOTER_MAX,  AppConst::TANK_MAX,  1 }, // フェーズ5: ShooterEnemy + TankEnemy同時
    { true,  true,  true,  false, AppConst::MOB_MAX_WAVE4, AppConst::SHOOTER_MAX,  AppConst::TANK_MAX,  1 }, // フェーズ6: TankEnemy x2回
    { false, false, false, true,  0,                       0,                      0,                   1 }, // フェーズ7: Boss
};

void WaveManager::Init()
{
    m_waveIndex = 0;
    m_currentRepeat = 0;
    m_waveClear = false;
    m_mobDefeated = 0;
    m_shooterDefeated = 0;
    m_tankDefeated = 0;
    m_bossDefeated = 0;
}

bool WaveManager::CheckWaveClear() const
{
    const WaveData& wave = WAVE_LIST[m_waveIndex];

    if (wave.spawnMob && m_mobDefeated < wave.mobCount)     return false;
    if (wave.spawnShooter && m_shooterDefeated < wave.shooterCount) return false;
    if (wave.spawnTank && m_tankDefeated < wave.tankCount)     return false;
    if (wave.spawnBoss && m_bossDefeated < 1)                 return false;

    return true;
}

void WaveManager::OnEnemyDefeated(bool _isMob, bool _isShooter, bool _isTank, bool _isBoss)
{
    if (_isMob)     m_mobDefeated++;
    if (_isShooter) m_shooterDefeated++;
    if (_isTank)    m_tankDefeated++;
    if (_isBoss)    m_bossDefeated++;

    if (CheckWaveClear())
    {
        NextWave();
    }
}

void WaveManager::NextWave()
{
    const WaveData& wave = WAVE_LIST[m_waveIndex];

    m_currentRepeat++;

    if (m_currentRepeat < wave.repeatCount)
    {
        // まだ繰り返しが残っている → カウンターだけリセット
        m_mobDefeated = 0;
        m_shooterDefeated = 0;
        m_tankDefeated = 0;
        m_bossDefeated = 0;
        m_waveClear = true;
        return;
    }

    // 次のウェーブへ
    m_currentRepeat = 0;
    m_waveIndex++;
    m_mobDefeated = 0;
    m_shooterDefeated = 0;
    m_tankDefeated = 0;
    m_bossDefeated = 0;
    m_waveClear = true;
}