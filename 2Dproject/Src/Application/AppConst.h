#pragma once

namespace AppConst
{
    // 画面
    static const int   SCREEN_W = 1280;
    static const int   SCREEN_H = 720;
    static const float SCREEN_HALF_W = 640.0f;
    static const float SCREEN_HALF_H = 360.0f;

    // タイトルロゴ
    static const int   LOGO_W = 536;
    static const int   LOGO_H = 357;
    static const float LOGO_Y = 100.0f; // 中央上部からの距離

    // プレイヤー
    static const int   PLAYER_W = 32;
    static const int   PLAYER_H = 32;
    static const float PLAYER_SCALE = 2.0f;
    static const float PLAYER_SCALED_W = 64.0f;
    static const float PLAYER_SCALED_H = 64.0f;
    static const int   PLAYER_SIZE = 64;   // 当たり判定用（既存との互換）
    static const float PLAYER_SPEED = 7.0f;
    static const int   PLAYER_ANIM_MAX = 8;
    static const int   PLAYER_ANIM_SPEED = 6;
    static const int SHOT_INTERVAL = 3; // 連射間隔（フレーム数）小さいほど速い

    // プレイヤー入場
    static const float PLAYER_ENTER_SPEED = 4.0f;
    static const float PLAYER_ENTER_START_X = -(SCREEN_HALF_W + 64.0f); // 画面左外
    static const float PLAYER_ENTER_STOP_X = -300.0f; // 停止位置

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

    // TankEnemy
    static const int   TANK_W = 32;
    static const int   TANK_H = 96;
    static const float TANK_SCALE = 2.0f;
    static const float TANK_SCALED_W = 64.0f;   // 32 * 2
    static const float TANK_SCALED_H = 192.0f;  // 96 * 2
    static const int   TANK_ANIM_MAX = 16;
    static const int   TANK_ANIM_SPEED = 4;
    static const float TANK_DROP_SPEED = 12.0f;   // 落下速度
    static const float TANK_RISE_SPEED = 3.0f;    // 上昇速度
    static const float TANK_RISE_AMOUNT = 60.0f;   // 上昇量
    static const int   TANK_MAX = 3;
    static const float TANK_RADIUS = 32.0f;
    static const int   SCORE_PER_TANK = 500;
    static const int   TANK_SPAWN_INTERVAL = 30;     // 0.5秒

    // TankEnemy の固定X座標
    static const float TANK_X_LIST[3] = { 200.0f, 200.0f, 200.0f };
    // TankEnemy の出現Y座標（画面上から出てくる）
    static const float TANK_SPAWN_Y = SCREEN_HALF_H + TANK_SCALED_H / 2.0f; // 456.0f
    // TankEnemy の停止Y座標
    static const float TANK_STOP_Y_LIST[3] = { 150.0f, -50.0f, -250.0f };

    // 弾
    static const int   BULLET_W = 100;
    static const int   BULLET_H = 100;
    static const float BULLET_SCALE = 0.8f;  // 1/5に縮小
    static const float BULLET_SCALED_W = 20.0f; // 100 * 0.2
    static const int   BULLET_SIZE = 20;    // 当たり判定用
    static const float BULLET_RADIUS = 10.0f;   // BULLET_SIZE の半分
    static const int   BULLET_ANIM_MAX = 60;
    static const int   BULLET_ANIM_COLS = 8;     // 横のコマ数
    static const int   BULLET_ANIM_SPEED = 1;     // アニメ速度
    static const float BULLET_SPEED = 12.0f;
    static const int   BULLET_MAX = 100; // 同時に出せる最大数

    // 弾のダメージ
    static const int BULLET_DAMAGE_LV1 = 10;  // レベル1
    static const int BULLET_DAMAGE_LV2 = 25;  // レベル2
    static const int BULLET_DAMAGE_LV3 = 50;  // レベル3
    static const int BULLET_DAMAGE_LV4 = 100; // レベル4（最大）

    // 当たり判定の半径
    static const float ENEMY_RADIUS = ENEMY_SCALED_W / 2.0f;  // 22.0f
    static const float PLAYER_RADIUS = 32.0f;  // PLAYER_SIZE の半分

    // スコア
    static const int   SCORE_MAX = 9999999;
    static const int   SCORE_DIGITS = 7;
    static const int   SCORE_PER_ENEMY = 100;
    static const int   NUMBER_W = 30;
    static const int   NUMBER_H = 30;
    static const float SCORE_X = (SCREEN_W / 2.0f) - (NUMBER_W * SCORE_DIGITS / 2.0f); // 中央揃え
    static const float SCORE_Y = 30.0f;  // 左上からのY位置（調整可）

    // タイトル画面
    static const int   TEXT_W = 256;   // テキスト画像の幅
    static const int   TEXT_H = 64;    // テキスト画像の高さ
    static const int   BLINK_INTERVAL = 30;    // 点滅間隔（フレーム数）
    static const float PRESS_ENTER_Y = 200.0f; // 画面下からの距離（調整可）
    static const float MENU_START_Y = 200.0f; // メニューのY位置（調整可）

    // 体力ゲージ
    static const int   HP_MAX = 3;
    static const int   GAUGE_W = 64;
    static const int   GAUGE_H = 7;
    static const float GAUGE_SCALE = 1.0f;   // 2.0f → 1.0f（半分に）
    static const float GAUGE_SCALED_W = 64.0f;  // 128.0f → 64.0f
    static const float GAUGE_SCALED_H = 7.0f;   // 14.0f → 7.0f
    static const float GAUGE_X = 50.0f;
    static const float GAUGE_Y = 55.0f;
    static const float GAUGE_SPACING = 70.0f;  // 間隔（GAUGE_SCALED_W より少し大きく）

    // 背景スクロール
    static const int   BG_LAYER_COUNT = 6;     // 8 → 6
    static const float BG_SCROLL_SPEED[6] =     // 8 → 6
    {
        0.2f,  // 0.png
        0.4f,  // 1.png
        0.6f,  // 2.png
        0.8f,  // 3.png
        1.0f,  // 4.png
        1.5f,  // 5.png
    };
    static const float BG_ALPHA[6] =            // 8 → 6
    {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    // Boss
    static const int   BOSS_W = 359;
    static const int   BOSS_H = 285;
    static const float BOSS_SCALE = 1.0f;
    static const int   BOSS_IDLE_ANIM_MAX = 12;   // Idle_Before
    static const int   BOSS_TRANS_ANIM_MAX = 29;   // Transform
    static const int   BOSS_ANIM_SPEED = 6;
    static const float BOSS_ENTER_SPEED = 2.0f; // 入場速度（ゆっくり）
    static const float BOSS_STOP_X = 300.0f;
    static const float BOSS_STOP_Y = 0.0f;
    static const float BOSS_SPAWN_X = SCREEN_HALF_W + BOSS_W; // 640 + 359 = 999.0f
    static const int   SCORE_PER_BOSS = 10000;
    static const int BOSS_IDLE_AFTER_ANIM_MAX = 10;  // 戦闘待機
    static const int BOSS_H_AFTER = 265; // 戦闘形態の高さ
    static const float BOSS_RADIUS = 150.0f; // 当たり判定半径

    // Boss 攻撃
    static const int   BOSS_ATTACK1_ANIM_MAX = 12;
    static const int   BOSS_ATTACK2_ANIM_MAX = 9;
    static const int   BOSS_ATTACK_INTERVAL = 120; // 2秒
    static const int   BOSS_ATTACK_H = 285; // Attack画像の高さ

    // Boss 死亡
    static const int   BOSS_DEATH_ANIM_MAX = 9;
    static const int   BOSS_DEATH_ANIM_SPEED = 10;  // 少し遅め
    static const float BOSS_DEATH_FALL_SPEED = 4.0f; // 落下速度
    // 左から再登場
    static const float BOSS_SPAWN_X_LEFT = -(SCREEN_HALF_W + 359.0f); // 画面左外

    // 各敵の体力
    static const int MOB_HP = 100;
    static const int SHOOTER_HP = 200;
    static const int TANK_HP = 500;
    static const int BOSS_HP = 1000;

}