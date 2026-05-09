#pragma once

class HitEffect
{
public:
    void Init();
    void Update();
    void Draw();
    void Release();

    void Play(Math::Vector2 _pos);
    bool IsPlaying() const { return m_isPlaying; }

private:
    KdTexture     m_tex;  // スプライトシート1枚に変更
    int           m_animFrame = 0;
    int           m_animTimer = 0;
    bool          m_isPlaying = false;
    Math::Vector2 m_pos = {};
    Math::Matrix  m_mat;
};