#pragma once

namespace AppConst
{
    // 画面
    static const int   SCREEN_W = 1280;
    static const int   SCREEN_H = 720;
    static const float SCREEN_HALF_W = 640.0f;
    static const float SCREEN_HALF_H = 360.0f;

    // プレイヤー
    static const int   PLAYER_SIZE = 64;
    static const float PLAYER_SPEED = 5.0f;

    // 敵
    static const int   ENEMY_SIZE = 64;
    static const float ENEMY_SPEED = 5.0f;
    static const int   ENEMY_COUNT = 5;
    static const float ENEMY_SPACE = 120.0f;

    // 弾（将来用）
    static const int   BULLET_SIZE = 16;
    static const float BULLET_SPEED = 10.0f;
    static const int   BULLET_MAX = 10; // 同時に出せる最大数
}