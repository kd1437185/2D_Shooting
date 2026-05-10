#pragma once

struct WaveData
{
    bool spawnMob = false;
    bool spawnShooter = false;
    bool spawnTank = false;
    bool spawnBoss = false;
    int  mobCount = 0;
    int  shooterCount = 0;
    int  tankCount = 0;
    int  repeatCount = 1;  // このウェーブを何回繰り返すか
};

class WaveManager
{
public:
    void Init();
    void OnEnemyDefeated(bool _isMob, bool _isShooter, bool _isTank, bool _isBoss);
    bool IsWaveClear()     const { return m_waveClear; }
    void ResetWaveClear() { m_waveClear = false; }
    int  GetWaveIndex()    const { return m_waveIndex; }
    int  GetRepeatCount()  const { return m_currentRepeat; }

    // 現在のウェーブ情報取得
    const WaveData& GetCurrentWave() const { return WAVE_LIST[m_waveIndex]; }

    // 現在のウェーブで各敵の残り倒す数
    int GetMobDefeated()     const { return m_mobDefeated; }
    int GetShooterDefeated() const { return m_shooterDefeated; }
    int GetTankDefeated()    const { return m_tankDefeated; }

    // シングルトン
private:
    WaveManager() {}
    ~WaveManager() {}
    WaveManager(const WaveManager&) = delete;
    WaveManager& operator=(const WaveManager&) = delete;

    void NextWave();
    bool CheckWaveClear() const;

    static const int WAVE_COUNT = 7;
    static const WaveData WAVE_LIST[WAVE_COUNT];

    int  m_waveIndex = 0;
    int  m_currentRepeat = 0;  // 現在の繰り返し回数
    bool m_waveClear = false;

    int  m_mobDefeated = 0;
    int  m_shooterDefeated = 0;
    int  m_tankDefeated = 0;
    int  m_bossDefeated = 0;

public:
    static WaveManager& Instance()
    {
        static WaveManager instance;
        return instance;
    }
};