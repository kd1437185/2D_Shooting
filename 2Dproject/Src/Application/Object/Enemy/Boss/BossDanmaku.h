#pragma once
#include "../../Bullet/DanmakuBullet.h"

class BossDanmaku
{
public:
    void Init();
    void Update(Math::Vector2 _bossPos, Math::Vector2 _playerPos);
    void Draw();
    void Release();

    void SetPattern(int _pattern); // パターン切り替え
    void Start();
    void Stop();
    bool IsActive() const { return m_active; }

    std::vector<std::shared_ptr<DanmakuBullet>>& GetBullets() { return m_Bullets; }

    void SetFromLeft(bool _fromLeft) { m_fromLeft = _fromLeft; }

private:
    void FireCircle(Math::Vector2 _pos);   // パターン1
    void FireSpiral(Math::Vector2 _pos);   // パターン2
    void FireWave(Math::Vector2 _pos);     // パターン3
    void FireExpand(Math::Vector2 _pos);   // パターン4

    std::shared_ptr<DanmakuBullet> GetFreeBullet();

    std::vector<std::shared_ptr<DanmakuBullet>> m_Bullets;

    KdTexture m_BlueTex;
    KdTexture m_OrangeTex;

    bool  m_active = false;
    int   m_pattern = 1;
    int   m_timer = 0;
    float m_baseAngle = 0.0f;
    float m_waveTimer = 0.0f;  // 波状用タイマー
    int   m_shotCount = 0;
    bool  m_isOrange = false;
    int   m_expandTimer = 0;     // 展開弾タイマー
    bool m_fromLeft = false;
};