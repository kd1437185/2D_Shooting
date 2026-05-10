#pragma once

class BulletLevelUI
{
public:
    void Init();
    void Draw(int _level);
    void Release();

private:
    KdTexture m_tex[4]; // Lv1〜Lv4
};