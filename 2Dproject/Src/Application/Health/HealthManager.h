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

    bool WasDamaged() const { return m_wasDamaged; }
    void ResetDamaged() { m_wasDamaged = false; }

    // ƒVƒ“ƒOƒ‹ƒgƒ“
private:
    HealthManager() {}
    ~HealthManager() {}
    HealthManager(const HealthManager&) = delete;
    HealthManager& operator=(const HealthManager&) = delete;

    int       m_hp = 5;
    KdTexture m_HeartTex; // 1–‡‚ÅŠÇ—
    bool m_wasDamaged = false;

public:
    static HealthManager& Instance()
    {
        static HealthManager instance;
        return instance;
    }
};