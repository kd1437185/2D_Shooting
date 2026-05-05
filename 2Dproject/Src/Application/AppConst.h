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

    // 当たり判定の半径
    static const float BULLET_RADIUS = 8.0f;   // BULLET_SIZE の半分
    static const float ENEMY_RADIUS = 32.0f;   // ENEMY_SIZE の半分
    static const float PLAYER_RADIUS = 32.0f;  // PLAYER_SIZE の半分

    // スコア
    static const int   SCORE_MAX = 9999999;
    static const int   SCORE_DIGITS = 7;
    static const int   SCORE_PER_ENEMY = 100;
    static const int   NUMBER_W = 30;
    static const int   NUMBER_H = 30;
    static const float SCORE_X = 50.0f;  // 左上からのX位置（調整可）
    static const float SCORE_Y = 30.0f;  // 左上からのY位置（調整可）

}