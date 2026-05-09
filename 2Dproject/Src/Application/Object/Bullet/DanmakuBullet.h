#pragma once
#include "../BaseObject.h"

class DanmakuBullet : public BaseObject
{
public:
    DanmakuBullet() {}
    ~DanmakuBullet() override {}

    void Init()    override;
    void Update()  override;
    void Draw()    override;
    void Release() override;

    void Fire(Math::Vector2 _startPos, float _angleRad, bool _isOrange);

    bool IsAlive()  const { return m_aliveFlg; }
    void SetAlive(bool b) { m_aliveFlg = b; }
    float GetRadius() const { return AppConst::DANMAKU_BULLET_RADIUS; }
    void SetTex(KdTexture* _blue, KdTexture* _orange)
    {
        m_texBlue = _blue;
        m_texOrange = _orange;
        m_tex = m_isOrange ? _orange : _blue;
    }

    // 展開弾用
    void SetExpandMode(float _stopRadius, int _stopTime, float _fastSpeed);
    void UpdateExpand(); // 展開弾専用Updates

private:

    float m_velX = 0.0f;
    float m_velY = 0.0f;
    bool  m_isOrange = false;

    // 展開弾用
    bool  m_isExpand = false;
    float m_stopRadius = 0.0f;
    int   m_stopTime = 0;
    int   m_stopTimer = 0;
    float m_fastSpeed = 0.0f;
    float m_distFromBoss = 0.0f;
    Math::Vector2 m_startPos = {};

    enum class ExpandPhase { Expand, Stop, Launch };
    ExpandPhase m_expandPhase = ExpandPhase::Expand;

    KdTexture* m_tex = nullptr; // 外部テクスチャへのポインタ
    KdTexture* m_texBlue = nullptr;
    KdTexture* m_texOrange = nullptr;
};