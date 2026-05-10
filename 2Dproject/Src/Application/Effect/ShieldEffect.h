#pragma once

class ShieldEffect
{
public:
    void Init();
    void Update(Math::Vector2 _playerPos);
    void Draw();
    void Release();

    void Activate();              // 通常シールド
    void ActivateBomb();          // ボム発動
    bool IsActive()   const { return m_isActive; }
    bool IsBombing()  const { return m_isBombing; }
    float GetCurrentRadius() const { return m_currentRadius; } // 当たり判定用

private:
    KdTexture     m_tex;
    int           m_animFrame = 0;
    int           m_animTimer = 0;
    int           m_duration = 0;
    bool          m_isActive = false;
    bool          m_isBombing = false;
    float         m_currentScale = 1.0f;
    float         m_currentRadius = 0.0f;
    int           m_bombTimer = 0;
    Math::Vector2 m_pos = {};
    Math::Matrix  m_mat;
};