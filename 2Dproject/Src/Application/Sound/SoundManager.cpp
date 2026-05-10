#include "SoundManager.h"
#include "Application/AppConst.h"

void SoundManager::Init()
{
    // BGM読み込み
    m_titleBGM = std::make_shared<KdSoundEffect>();
    m_titleBGM->Load("Sound/BGM/Lazy_night_気だるい夜_.wav");
    m_titleBGMInst = m_titleBGM->CreateInstance(false);
    m_titleBGMInst->SetVolume(AppConst::VOL_TITLE_BGM);

    m_gameBGM = std::make_shared<KdSoundEffect>();
    m_gameBGM->Load("Sound/BGM/灰色の脳細胞.wav");
    m_gameBGMInst = m_gameBGM->CreateInstance(false);
    m_gameBGMInst->SetVolume(AppConst::VOL_GAME_BGM);

    m_bossBGM = std::make_shared<KdSoundEffect>();
    m_bossBGM->Load("Sound/BGM/ボスバトル！.wav");
    m_bossBGMInst = m_bossBGM->CreateInstance(false);
    m_bossBGMInst->SetVolume(AppConst::VOL_BOSS_BGM);

    // SE読み込み
    m_shotSE = std::make_shared<KdSoundEffect>();
    m_shotSE->Load("Sound/SE/Hit 3 - Sound effects Pack 2.wav");
    m_shotSEInst = m_shotSE->CreateInstance(false);
    m_shotSEInst->SetVolume(AppConst::VOL_SHOT_SE);

    m_bombSE = std::make_shared<KdSoundEffect>();
    m_bombSE->Load("Sound/SE/Teleport 8 - Sound effects Pack 2.wav");
    m_bombSEInst = m_bombSE->CreateInstance(false);
    m_bombSEInst->SetVolume(AppConst::VOL_BOMB_SE);

    m_damageSE = std::make_shared<KdSoundEffect>();
    m_damageSE->Load("Sound/SE/Teleport 8 - Sound effects Pack 2.wav");
    m_damageSEInst = m_damageSE->CreateInstance(false);
    m_damageSEInst->SetVolume(AppConst::VOL_DAMAGE_SE);

}

void SoundManager::Release()
{
    StopBGM();
    m_titleBGMInst = nullptr;
    m_gameBGMInst = nullptr;
    m_bossBGMInst = nullptr;
    m_shotSEInst = nullptr;
    m_bombSEInst = nullptr;
    m_damageSEInst = nullptr;
    m_titleBGM = nullptr;
    m_gameBGM = nullptr;
    m_bossBGM = nullptr;
    m_shotSE = nullptr;
    m_bombSE = nullptr;
    m_damageSE = nullptr;
}

void SoundManager::StopBGM()
{
    if (m_currentBGMInst && m_currentBGMInst->IsPlay())
    {
        m_currentBGMInst->Stop();
    }
    m_currentBGMInst = nullptr;
}

void SoundManager::PlayTitleBGM()
{
    StopBGM();
    m_titleBGMInst->Play(true); // ループ再生
    m_currentBGMInst = m_titleBGMInst;
}

void SoundManager::PlayGameBGM()
{
    StopBGM();
    m_gameBGMInst->Play(true);
    m_currentBGMInst = m_gameBGMInst;
}

void SoundManager::PlayBossBGM()
{
    StopBGM();
    m_bossBGMInst->Play(true);
    m_currentBGMInst = m_bossBGMInst;
}

void SoundManager::PlayShotSE()
{
    if (!m_shotSEInst->IsPlay())
    {
        m_shotSEInst->Play(false);
    }
}

void SoundManager::PlayBombSE()
{
    m_bombSEInst->Stop();
    m_bombSEInst->Play(false);
}

void SoundManager::PlayDamageSE()
{
    m_damageSEInst->Stop();
    m_damageSEInst->Play(false);
}

void SoundManager::SetBGMVolume(float _vol)
{
    m_bgmVol = _vol;
    m_titleBGMInst->SetVolume(m_bgmVol);
    m_gameBGMInst->SetVolume(m_bgmVol);
    m_bossBGMInst->SetVolume(m_bgmVol);
}

void SoundManager::SetSEVolume(float _vol)
{
    m_seVol = _vol;
    m_shotSEInst->SetVolume(m_seVol);
    m_bombSEInst->SetVolume(m_seVol);
    m_damageSEInst->SetVolume(m_seVol);
}