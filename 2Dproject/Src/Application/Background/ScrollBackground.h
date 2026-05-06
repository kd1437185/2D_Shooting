#pragma once

class ScrollBackground
{
public:
    void Init();
    void Update();
    void Draw();
    void Release();

private:
    struct Layer
    {
        KdTexture tex;
        float     scrollX = 0.0f; // Œ»İ‚ÌƒXƒNƒ[ƒ‹—Ê
    };

    Layer m_layers[6];
};