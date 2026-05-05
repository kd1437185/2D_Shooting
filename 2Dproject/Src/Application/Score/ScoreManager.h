#pragma once

class ScoreManager
{
public:
    void Init();
    void Release();
    void Draw();

    void AddScore(int _score);
    int  GetScore() const { return m_score; }
    void Reset() { m_score = 0; }

    // ƒVƒ“ƒOƒ‹ƒgƒ“
private:
    ScoreManager() {}
    ~ScoreManager() {}

    ScoreManager(const ScoreManager&) = delete;
    ScoreManager& operator=(const ScoreManager&) = delete;

    int       m_score = 0;
    KdTexture m_numTex;

public:
    static ScoreManager& Instance()
    {
        static ScoreManager instance;
        return instance;
    }
};