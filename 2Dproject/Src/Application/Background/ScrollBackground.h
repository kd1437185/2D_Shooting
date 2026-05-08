#pragma once

class ScrollBackground
{
public:
    void Init();
    void Update();
    void Draw();
    void Release();

    // シングルトン
private:
    ScrollBackground() {}
    ~ScrollBackground() {}
    ScrollBackground(const ScrollBackground&) = delete;
    ScrollBackground& operator=(const ScrollBackground&) = delete;

    struct Layer
    {
        KdTexture tex;
        float     scrollX = 0.0f;
    };

    Layer m_layers[6];
    bool  m_initialized = false; // 初回だけロードする

public:
    static ScrollBackground& Instance()
    {
        static ScrollBackground instance;
        return instance;
    }
};