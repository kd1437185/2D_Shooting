#pragma once

class ResultManager
{
public:
    void Init();
    void Update();
    void Draw();
    void Release();

    void Show(int _score);
    bool IsActive() const { return m_isActive; }

    void ShowGameOver(int _score); // ゲームオーバー時
    bool IsGameOver() const { return m_isGameOver; }

    // シングルトン
private:
    ResultManager() {}
    ~ResultManager() {}
    ResultManager(const ResultManager&) = delete;
    ResultManager& operator=(const ResultManager&) = delete;

    enum class Phase
    {
        ScoreAnim,
        SelectWait,
        Select
    };

    void UpdateScoreAnim();
    void UpdateSelect();

    KdTexture m_BgTex;
    KdTexture m_BackTitleTex;  // PLAY AGAIN削除

    bool  m_isActive = false;
    int   m_score = 0;
    int   m_timer = 0;
    int   m_blinkTimer = 0;
    bool  m_blinkVisible = true;
    Phase m_phase = Phase::ScoreAnim;

    float m_scorePosY = 0.0f;
    float m_scoreScale = 1.0f;

    bool m_prevEnter = false;

    bool m_isGameOver = false;

public:
    static ResultManager& Instance()
    {
        static ResultManager instance;
        return instance;
    }
};