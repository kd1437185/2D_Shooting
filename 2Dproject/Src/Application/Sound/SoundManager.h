#pragma once

class SoundManager
{
public:
    void Init();
    void Release();

    // BGM
    void PlayTitleBGM();
    void PlayGameBGM();
    void PlayBossBGM();
    void StopBGM();

    // SE
    void PlayShotSE();
    void PlayBombSE();
    void PlayDamageSE();

    // 音量設定
    void SetBGMVolume(float _vol);
    void SetSEVolume(float _vol);

    // シングルトン
private:
    SoundManager() {}
    ~SoundManager() {}
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    // BGM
    std::shared_ptr<KdSoundEffect>   m_titleBGM;
    std::shared_ptr<KdSoundInstance> m_titleBGMInst;
    std::shared_ptr<KdSoundEffect>   m_gameBGM;
    std::shared_ptr<KdSoundInstance> m_gameBGMInst;
    std::shared_ptr<KdSoundEffect>   m_bossBGM;
    std::shared_ptr<KdSoundInstance> m_bossBGMInst;

    // SE
    std::shared_ptr<KdSoundEffect>   m_shotSE;
    std::shared_ptr<KdSoundInstance> m_shotSEInst;
    std::shared_ptr<KdSoundEffect>   m_bombSE;
    std::shared_ptr<KdSoundInstance> m_bombSEInst;
    std::shared_ptr<KdSoundEffect>   m_damageSE;
    std::shared_ptr<KdSoundInstance> m_damageSEInst;

    float m_bgmVol = 0.5f;
    float m_seVol = 0.8f;

    // 現在再生中のBGMインスタンス
    std::shared_ptr<KdSoundInstance> m_currentBGMInst = nullptr;

public:
    static SoundManager& Instance()
    {
        static SoundManager instance;
        return instance;
    }
};