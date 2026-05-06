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
    static const float PLAYER_SPEED = 7.0f;
    static const int SHOT_INTERVAL = 3; // 連射間隔（フレーム数）小さいほど速い

    // MobEnemy
    static const int   ENEMY_W = 22;    // 1コマの幅
    static const int   ENEMY_H = 24;    // 1コマの高さ
    static const float ENEMY_SCALE = 2.0f;  // 拡大倍率
    static const float ENEMY_SCALED_W = ENEMY_W * ENEMY_SCALE;  // 44
    static const float ENEMY_SCALED_H = ENEMY_H * ENEMY_SCALE;  // 48
    static const int   ENEMY_ANIM_MAX = 10;    // アニメーションコマ数
    static const int   ENEMY_ANIM_SPEED = 6;     // 何フレームで1コマ進むか
    static const float ENEMY_SPEED = 5.0f;
    static const int   ENEMY_MAX = 5;      // 最大同時出現数
    static const int   ENEMY_SPAWN_INTERVAL = 60; // 1秒（60fps × 1）

    // 敵のY座標候補（5か所）
    static const float ENEMY_Y_LIST[5] = { 200.0f, 100.0f, 0.0f, -100.0f, -200.0f };

    // ShooterEnemy
    static const int   SHOOTER_W = 32;
    static const int   SHOOTER_H = 32;
    static const float SHOOTER_SCALE = 2.0f;
    static const float SHOOTER_SCALED_W = SHOOTER_W * SHOOTER_SCALE;  // 64
    static const float SHOOTER_SCALED_H = SHOOTER_H * SHOOTER_SCALE;  // 64
    static const int   SHOOTER_ANIM_MAX = 16;
    static const int   SHOOTER_ANIM_SPEED = 4;
    static const float SHOOTER_SPEED = 4.0f;
    static const float SHOOTER_STOP_X = 500.0f;
    static const float SHOOTER_FLOAT_SPEED = 0.05f;
    static const float SHOOTER_FLOAT_RANGE = 80.0f;
    static const int   SHOOTER_MAX = 5;
    static const float SHOOTER_RADIUS = SHOOTER_SCALED_W / 2.0f;  // 32.0f
    static const int   SCORE_PER_SHOOTER = 300;

    // 弾（将来用）
    static const int   BULLET_SIZE = 16;
    static const float BULLET_SPEED = 15.0f;
    static const int   BULLET_MAX = 100; // 同時に出せる最大数

    // 当たり判定の半径
    static const float BULLET_RADIUS = 8.0f;   // BULLET_SIZE の半分
    static const float ENEMY_RADIUS = ENEMY_SCALED_W / 2.0f;  // 22.0f
    static const float PLAYER_RADIUS = 32.0f;  // PLAYER_SIZE の半分

    // スコア
    static const int   SCORE_MAX = 9999999;
    static const int   SCORE_DIGITS = 7;
    static const int   SCORE_PER_ENEMY = 100;
    static const int   NUMBER_W = 30;
    static const int   NUMBER_H = 30;
    static const float SCORE_X = 50.0f;  // 左上からのX位置（調整可）
    static const float SCORE_Y = 30.0f;  // 左上からのY位置（調整可）

    // タイトル画面
    static const int   TEXT_W = 256;   // テキスト画像の幅
    static const int   TEXT_H = 64;    // テキスト画像の高さ
    static const int   BLINK_INTERVAL = 30;    // 点滅間隔（フレーム数）
    static const float PRESS_ENTER_Y = 200.0f; // 画面下からの距離（調整可）
    static const float MENU_START_Y = 200.0f; // メニューのY位置（調整可）

}