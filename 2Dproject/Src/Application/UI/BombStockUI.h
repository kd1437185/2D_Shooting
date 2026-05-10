#pragma once

class BombStockUI
{
public:
    void Init();
    void Draw(int _stock);
    void Release();

private:
    KdTexture m_tex;
};