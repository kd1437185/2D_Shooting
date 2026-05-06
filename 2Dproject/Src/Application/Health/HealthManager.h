#pragma once

#include "../AppConst.h"

class HealthManager
{
public:
    void Init();
    void Release();
    void Draw();

    void Damage();                          // ‘Ì—Í‚ð1Œ¸‚ç‚·
    int  GetHp()    const { return m_hp; }
    bool IsDead()   const { return m_hp <= 0; }
    void Reset() { m_hp = AppConst::HP_MAX; }

    // ƒVƒ“ƒOƒ‹ƒgƒ“
private:
    HealthManager() {}
    ~HealthManager() {}
    HealthManager(const HealthManager&) = delete;
    HealthManager& operator=(const HealthManager&) = delete;

    int       m_hp = 3;
    KdTexture m_GreenTex; // ‘Ì—Í‚ ‚è
    KdTexture m_WhiteTex; // ‘Ì—Í‚È‚µ

public:
    static HealthManager& Instance()
    {
        static HealthManager instance;
        return instance;
    }
};