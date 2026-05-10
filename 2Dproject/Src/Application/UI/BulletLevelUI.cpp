#include "BulletLevelUI.h"
#include "../AppConst.h"

void BulletLevelUI::Init()
{
    m_tex[0].Load("Texture/UI/Bullet_Level_1.png");
    m_tex[1].Load("Texture/UI/Bullet_Level_2.png");
    m_tex[2].Load("Texture/UI/Bullet_Level_3.png");
    m_tex[3].Load("Texture/UI/Bullet_Level_4.png");
}

void BulletLevelUI::Release()
{
    for (int i = 0; i < 4; i++)
    {
        m_tex[i].Release();
    }
}

void BulletLevelUI::Draw(int _level)
{
    int idx = _level - 1;
    if (idx < 0 || idx > 3) return;

    Math::Matrix mat = Math::Matrix::CreateScale(
        AppConst::BULLET_LEVEL_SCALE, AppConst::BULLET_LEVEL_SCALE, 1.0f)
        * Math::Matrix::CreateTranslation(
            AppConst::SCREEN_HALF_W - AppConst::BULLET_LEVEL_X
            - AppConst::BULLET_LEVEL_W * AppConst::BULLET_LEVEL_SCALE / 2.0f,
            AppConst::SCREEN_HALF_H - AppConst::BULLET_LEVEL_Y
            - AppConst::BULLET_LEVEL_H * AppConst::BULLET_LEVEL_SCALE / 2.0f,
            0);

    SHADER.m_spriteShader.SetMatrix(mat);
    SHADER.m_spriteShader.DrawTex(&m_tex[idx],
        Math::Rectangle{ 0, 0, AppConst::BULLET_LEVEL_W, AppConst::BULLET_LEVEL_H },
        1.0f);
}