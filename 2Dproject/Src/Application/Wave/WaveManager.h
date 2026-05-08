#pragma once

// ウェーブの種類
enum class WaveType
{
    MobEnemy,   // 雑魚敵
    Enemy2,     // 敵2
    Enemy3,     // 敵3
    Boss,       // ボス
    Clear       // 全ウェーブクリア
};

class WaveManager
{
public:
    void Init();

    // 現在のウェーブを取得
    WaveType GetCurrentWave() const { return m_currentWave; }

    // 現在のウェーブの敵を全滅させたら次のウェーブへ
    void OnEnemyDefeated();

    // 現在のウェーブで倒した敵の数
    int GetDefeatedCount() const { return m_defeatedCount; }

    // 現在のウェーブがクリアされたか
    bool IsWaveClear() const { return m_waveClear; }

    void ResetWaveClear() { m_waveClear = false; }

    // シングルトン
private:
    WaveManager() {}
    ~WaveManager() {}
    WaveManager(const WaveManager&) = delete;
    WaveManager& operator=(const WaveManager&) = delete;

    void NextWave();

    WaveType m_currentWave = WaveType::MobEnemy;
    int      m_defeatedCount = 0;
    bool     m_waveClear = false;

    // ウェーブごとの撃破必要数
    // MobEnemy→Enemy2→Enemy3→MobEnemy→Enemy2→Enemy3→Boss の順
    static const int WAVE_ORDER_MAX = 7;
    static const WaveType WAVE_ORDER[WAVE_ORDER_MAX];
    static const int      WAVE_KILL_COUNT[WAVE_ORDER_MAX]; // 各ウェーブの撃破必要数

    int m_waveIndex = 0; // 現在何番目のウェーブか

public:
    static WaveManager& Instance()
    {
        static WaveManager instance;
        return instance;
    }
};