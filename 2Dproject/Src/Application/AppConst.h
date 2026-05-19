#pragma once

namespace AppConst
{
    // 画面
    static const int   SCREEN_W      = 1280;
    static const int   SCREEN_H      = 720;
    static const float SCREEN_HALF_W = 640.0f;
    static const float SCREEN_HALF_H = 360.0f;

    // MobEnemy 出現数（ウェーブごと）
    static const int MOB_MAX_WAVE1 = 8;   // フェーズ1（調整可）
    static const int MOB_MAX_WAVE4 = 10;  // フェーズ4・2周目MobEnemy（調整可）

    // タイトルロゴ
    static const int   LOGO_W = 536;
    static const int   LOGO_H = 357;
    static const float LOGO_Y = 100.0f; // 中央上部からの距離

    // プレイヤー
    static const int   PLAYER_W          = 32;
    static const int   PLAYER_H          = 32;
    static const float PLAYER_SCALE      = 2.0f;
    static const float PLAYER_SCALED_W   = 64.0f;
    static const float PLAYER_SCALED_H   = 64.0f;
    static const int   PLAYER_SIZE       = 64;   // 当たり判定用（既存との互換）
    static const float PLAYER_SPEED      = 9.0f;
    static const int   PLAYER_ANIM_MAX   = 8;
    static const int   PLAYER_ANIM_SPEED = 6;
    static const int   SHOT_INTERVAL     = 10; // 連射間隔（フレーム数）小さいほど速い

    // プレイヤー入場
    static const float PLAYER_ENTER_SPEED   = 4.0f;
    static const float PLAYER_ENTER_START_X = -(SCREEN_HALF_W + 64.0f); // 画面左外
    static const float PLAYER_ENTER_STOP_X  = -300.0f; // 停止位置

    // MobEnemy
    static const int   ENEMY_W              = 22;    // 1コマの幅
    static const int   ENEMY_H              = 24;    // 1コマの高さ
    static const float ENEMY_SCALE          = 2.0f;  // 拡大倍率
    static const float ENEMY_SCALED_W       = ENEMY_W * ENEMY_SCALE;  // 44
    static const float ENEMY_SCALED_H       = ENEMY_H * ENEMY_SCALE;  // 48
    static const int   ENEMY_ANIM_MAX       = 10;    // アニメーションコマ数
    static const int   ENEMY_ANIM_SPEED     = 6;     // 何フレームで1コマ進むか
    static const float ENEMY_SPEED          = 1.0f;
    static const int   ENEMY_MAX            = 5;      // 最大同時出現数
    static const int   ENEMY_SPAWN_INTERVAL = 60; // 1秒（60fps × 1）

    // MobEnemy 改造版
    static const float MOB_ENTER_SPEED = 4.0f;   // 侵入速度（調整可）
    static const float MOB_SLOW_SPEED = 0.5f;   // 減速後の速度（調整可）
    static const int   MOB_SLOW_DURATION = 120;     // 減速時間（フレーム）
    static const float MOB_ANGLE = 30.0f;  // 侵入角度（度・調整可）
    static const float MOB_SPAWN_X_MARGIN = 200.0f; // 画面端からのX余白（調整可）

    // 敵弾
    static const int   ENEMY_BULLET_W = 24;
    static const int   ENEMY_BULLET_H = 24;
    static const float ENEMY_BULLET_SCALE = 1.0f;   // 調整可
    static const float ENEMY_BULLET_ALPHA = 1.0f;   // 調整可
    static const float ENEMY_BULLET_SPEED = 3.0f;   // 調整可
    static const float ENEMY_BULLET_RADIUS = 8.0f;
    static const int   ENEMY_BULLET_MAX = 20;     // 同時出現最大数

    // ShooterEnemy
    static const int   SHOOTER_W           = 32;
    static const int   SHOOTER_H           = 32;
    static const float SHOOTER_SCALE       = 2.0f;
    static const float SHOOTER_SCALED_W    = SHOOTER_W * SHOOTER_SCALE;  // 64
    static const float SHOOTER_SCALED_H    = SHOOTER_H * SHOOTER_SCALE;  // 64
    static const int   SHOOTER_ANIM_MAX    = 16;
    static const int   SHOOTER_ANIM_SPEED  = 4;
    static const float SHOOTER_SPEED       = 4.0f;
    static const float SHOOTER_STOP_X      = 500.0f;
    static const float SHOOTER_FLOAT_SPEED = 0.05f;
    static const float SHOOTER_FLOAT_RANGE = 80.0f;
    static const int   SHOOTER_MAX         = 2;
    static const float SHOOTER_RADIUS      = SHOOTER_SCALED_W / 2.0f;  // 32.0f
    static const int   SCORE_PER_SHOOTER   = 3200;

    // ShooterEnemy 改造版
    static const float SHOOTER_ENTER_X = 450.0f;  // 停止X座標（調整可）
    static const float SHOOTER_ENTER_SPEED = 5.0f;    // 横移動速度（調整可）
    static const float SHOOTER_VERT_SPEED = 4.0f;    // 縦移動速度（調整可）
    static const int   SHOOTER_STOP_FRAMES = 30;       // 停止時間（調整可）
    static const float SHOOTER_3WAY_ANGLE = 40.0f;   // 3WAY角度（度・調整可）
    static const float SHOOTER_BULLET_SPEED = 2.0f;    // 弾速（調整可）
    static const int   SHOOTER_SHOT_INTERVAL = 300;    // 発射インターバル（フレーム・調整可）

    // TankEnemy
    static const int   TANK_W              = 32;
    static const int   TANK_H              = 96;
    static const float TANK_SCALE          = 2.0f;
    static const float TANK_SCALED_W       = 64.0f;   // 32 * 2
    static const float TANK_SCALED_H       = 192.0f;  // 96 * 2
    static const int   TANK_ANIM_MAX       = 16;
    static const int   TANK_ANIM_SPEED     = 4;
    static const float TANK_DROP_SPEED     = 12.0f;   // 落下速度
    static const float TANK_RISE_SPEED     = 3.0f;    // 上昇速度
    static const float TANK_RISE_AMOUNT    = 60.0f;   // 上昇量
    static const int   TANK_MAX            = 3;
    static const float TANK_RADIUS         = 32.0f;
    static const int   SCORE_PER_TANK      = 4500;
    static const int   TANK_SPAWN_INTERVAL = 30;     // 0.5秒

    // TankEnemy の固定X座標
    static const float TANK_X_LIST[3] = { 200.0f, 200.0f, 200.0f };
    // TankEnemy の出現Y座標（画面上から出てくる）
    static const float TANK_SPAWN_Y = SCREEN_HALF_H + TANK_SCALED_H / 2.0f; // 456.0f
    // TankEnemy の停止Y座標
    static const float TANK_STOP_Y_LIST[3] = { 150.0f, -50.0f, -250.0f };

    // TankEnemy 弾
    static const int   TANK_BULLET_W = 36;
    static const int   TANK_BULLET_H = 36;
    static const float TANK_BULLET_SCALE = 1.0f;   // 調整可
    static const float TANK_BULLET_ALPHA = 1.0f;   // 調整可
    static const float TANK_BULLET_SPEED = 2.0f;   // 低速（調整可）
    static const float TANK_BULLET_FALL = 0.001f;  // 下に下がる速度（調整可）
    static const float TANK_BULLET_RADIUS = 10.0f;  // 小さめの当たり判定（調整可）
    static const int   TANK_BULLET_MAX = 10;     // 同時出現最大数
    static const int   TANK_SHOT_INTERVAL = 240;    // 発射間隔（4秒・調整可）

    // 弾
    static const int   BULLET_W = 243;
    static const int   BULLET_H = 140;
    static const float BULLET_SCALE = 0.5f;  // 倍率（調整可）
    static const float BULLET_SCALED_W = 121.5f; // 243 * 0.5
    static const int   BULLET_SIZE = 20;
    static const float BULLET_RADIUS = 10.0f;
    static const float BULLET_ALPHA = 0.4f; // アルファ値
    static const float BULLET_SPEED = 20.0f;
    static const int   BULLET_MAX = 100; // 同時に出せる最大数

    // 弾のダメージ
    static const int BULLET_DAMAGE_LV1 = 20;  // レベル1
    static const int BULLET_DAMAGE_LV2 = 20;  // レベル2
    static const int BULLET_DAMAGE_LV3 = 20;  // レベル3
    static const int BULLET_DAMAGE_LV4 = 30; // レベル4（最大）

    // 弾レベル設定
    static const float BULLET_LV2_OFFSET_Y = 20.0f;  // Lv2の上下オフセット（調整可）
    static const float BULLET_LV3_ANGLE = 4.0f;  // Lv3の3WAY角度（度数・調整可）

   // ホーミング弾
    static const int   HOMING_W = 24;
    static const int   HOMING_H = 24;
    static const int   HOMING_ANIM_MAX = 8;
    static const int   HOMING_ANIM_SPEED = 3;     // アニメ速度（調整可）
    static const float HOMING_SCALE = 2.0f;  // 倍率（調整可）
    static const float HOMING_ALPHA = 0.4f;  // アルファ値（調整可）
    static const float HOMING_SPEED = 15.0f;  // 速度（調整可）
    static const float HOMING_TURN_SPEED = 0.08f; // 旋回速度（調整可）
    static const int   HOMING_MAX = 20;
    static const int   HOMING_DAMAGE = 10;    // ダメージ（調整可）
    static const int   HOMING_LIFETIME = 60;   // 生存時間（フレーム・調整可）2秒=120
    static const int   HOMING_INTERVAL = 4;    // 発射間隔（フレーム・調整可）

    // ボス弾幕
    static const int   DANMAKU_BULLET_MAX = 200;  // 同時出現最大数
    static const float DANMAKU_BULLET_SPEED = 3.0f; // 弾速（調整可）
    static const float DANMAKU_BULLET_RADIUS = 8.0f; // 当たり判定（調整可）
    static const int   DANMAKU_SHOT_COUNT = 12;   // 1回の発射数（調整可）
    static const int   DANMAKU_INTERVAL = 30;   // 発射間隔（調整可）
    static const float DANMAKU_ROTATE_SPEED = 3.5f; // 回転速度（度/フレーム・調整可）
    static const int   DANMAKU_COLOR_CHANGE = 5;    // 何回撃ったら色を変えるか（調整可）

    // ボス弾幕パターン別設定
    // パターン2：スパイラル
    static const int   DANMAKU_SPIRAL_ARMS = 6;     // 腕の数（調整可）
    static const float DANMAKU_SPIRAL_ROTATE = 3.0f;  // 回転速度（度/フレーム・調整可）
    static const int   DANMAKU_SPIRAL_INTERVAL = 12;     // 発射間隔（調整可）

    // パターン3：波状
    static const int   DANMAKU_WAVE_COUNT = 8;     // 1回の発射数（調整可）
    static const float DANMAKU_WAVE_SPEED = 4.0f;  // 弾速（調整可）
    static const float DANMAKU_WAVE_AMPLITUDE = 30.0f; // 波の振幅（度・調整可）
    static const float DANMAKU_WAVE_FREQ = 0.1f;  // 波の周波数（調整可）
    static const int   DANMAKU_WAVE_INTERVAL = 30;    // 発射間隔（調整可）

    // パターン4：展開弾
    static const int   DANMAKU_EXPAND_COUNT = 18;    // 展開弾数（調整可）
    static const float DANMAKU_EXPAND_SPEED = 1.5f;  // 展開速度（低速・調整可）
    static const float DANMAKU_EXPAND_RADIUS = 150.0f;// 展開半径（調整可）
    static const int   DANMAKU_EXPAND_STOP_TIME = 60;    // 停止時間（フレーム・調整可）
    static const float DANMAKU_EXPAND_FAST_SPEED = 26.0f; // 高速発射速度（調整可）
    static const int   DANMAKU_EXPAND_INTERVAL = 300;   // 全体の発射間隔（調整可）

    // 当たり判定の半径
    static const float ENEMY_RADIUS = ENEMY_SCALED_W / 2.0f;  // 22.0f
    static const float PLAYER_RADIUS = 8.0f;

    // スコア
    static const int   SCORE_MAX = 9999999;
    static const int   SCORE_DIGITS = 7;
    static const int   SCORE_PER_ENEMY = 1500;
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
    static const int   HP_MAX = 5;      // 3 → 5
    static const int   GAUGE_W = 16;     // 1コマの幅
    static const int   GAUGE_H = 16;     // 1コマの高さ
    static const float GAUGE_SCALE = 4.0f;   // 2倍
    static const float GAUGE_SCALED_W = 32.0f; // 16 * 2
    static const float GAUGE_SCALED_H = 32.0f; // 16 * 2
    static const float GAUGE_X = 50.0f;
    static const float GAUGE_Y = 25.0f;
    static const float GAUGE_SPACING = 36.0f;  // 間隔（調整可）

    // 背景スクロール
    static const int   BG_LAYER_COUNT = 6;     // 6
    static const float BG_SCROLL_SPEED[6] =     // 6
    {
        0.2f,  // 0.png
        0.4f,  // 1.png
        0.6f,  // 2.png
        0.8f,  // 3.png
        1.0f,  // 4.png
        1.5f,  // 5.png
    };
    static const float BG_ALPHA[6] =            // 6
    {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    // Boss
    static const int   BOSS_W = 359;
    static const int   BOSS_H = 285;
    static const float BOSS_SCALE = 2.0f;
    static const int   BOSS_IDLE_ANIM_MAX = 12;   // Idle_Before
    static const int   BOSS_TRANS_ANIM_MAX = 29;   // Transform
    static const int   BOSS_ANIM_SPEED = 6;
    static const float BOSS_ENTER_SPEED = 2.0f; // 入場速度（ゆっくり）
    static const float BOSS_STOP_X = 400.0f;
    static const float BOSS_STOP_X_LEFT = 400.0f; // 左から来たボスの停止X
    static const float BOSS_STOP_Y = 0.0f;
    static const float BOSS_SPAWN_X = SCREEN_HALF_W + BOSS_W; // 640 + 359 = 999.0f
    static const int   SCORE_PER_BOSS = 30000;
    static const int   BOSS_IDLE_AFTER_ANIM_MAX = 10;  // 戦闘待機
    static const int   BOSS_H_AFTER = 265; // 戦闘形態の高さ
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

    // ボス名前表示
    static const int   BOSS_NAME_W = 336;
    static const int   BOSS_NAME_H = 224;
    static const float BOSS_NAME_OFFSET_Y = -200.0f; // ボスの下（調整可）
    static const float BOSS_NAME_FADE_IN = 0.03f;   // フェードイン速度（調整可）
    static const float BOSS_NAME_FADE_OUT = 0.01f;   // フェードアウト速度（調整可）
    static const int   BOSS_NAME_HOLD = 120;      // 最大アルファ値を保持するフレーム数（2秒）

    // 各敵の体力
    static const int MOB_HP = 60;
    static const int SHOOTER_HP = 120;
    static const int TANK_HP = 200;
    static const int BOSS_HP = 3000;

    // リザルト
    static const int   RESULT_BG_W = 676;
    static const int   RESULT_BG_H = 400;
    static const float RESULT_BG_ALPHA = 0.75f;
    static const float RESULT_BG_Y = -10.0f;    // 背景のY座標（調整可）
    static const int   RESULT_SELECT_W = 256;
    static const int   RESULT_SELECT_H = 64;
    static const float RESULT_SELECT_Y1 = -80.0f;  // BACK TITLE のY座標（調整可）

    // スコア演出
    static const float RESULT_SCORE_START_Y = SCREEN_HALF_H - 30.0f; // スコアの初期Y（上部）
    static const float RESULT_SCORE_END_Y = 40.0f;  // 着地Y座標（調整可）
    static const float RESULT_SCORE_START_SCALE = 1.0f;
    static const float RESULT_SCORE_END_SCALE = 2.0f; // 拡大後のスケール
    static const int   RESULT_ANIM_DURATION = 60;    // 1秒（60fps）
    static const int   RESULT_SELECT_DELAY = 90;    // 選択肢表示までの遅延

    // ヒットエフェクト
    static const int   HIT_W = 355;
    static const int   HIT_H = 365;
    static const float HIT_SCALE = 0.4f;  // 拡大倍率（調整可）
    static const float HIT_ALPHA = 0.4f;  // アルファ値（調整可）
    static const int   HIT_ANIM_MAX = 60;    // 総コマ数
    static const int   HIT_ANIM_COLS = 10;    // 横のコマ数
    static const int   HIT_ANIM_SPEED = 1;     // アニメ速度（調整可）

    // フェードアウト
    static const float FADE_SPEED = 0.05f; // フェード速度

    // シールド
    static const int   SHIELD_W = 265;
    static const int   SHIELD_H = 265;
    static const float SHIELD_SCALE = 0.5f;   // 拡大率（調整可）
    static const float SHIELD_ALPHA = 0.8f;   // アルファ値（調整可）
    static const int   SHIELD_ANIM_MAX = 60;
    static const int   SHIELD_ANIM_COLS = 9;      // 横のコマ数
    static const int   SHIELD_ANIM_SPEED = 2;      // アニメ速度（調整可）
    static const int   SHIELD_DURATION = 180;    // シールド持続時間（2秒・調整可）
    static const float SHIELD_RADIUS = 80.0f; // シールドの当たり判定半径

    // ボム
    static const int   BOMB_MAX = 3;      // 最大ストック数（調整可）
    static const int   BOMB_EXPAND_FRAMES = 30;     // 拡大時間（0.5秒・調整可）
    static const float BOMB_MAX_RADIUS = 900.0f; // 最大半径（画面全体・調整可）
    static const float BOMB_SCALE_MAX = 12.0f;   // 最大スケール（調整可）
    static const int   BOMB_W = 16;
    static const int   BOMB_H = 16;
    static const float BOMB_ICON_SCALE = 3.0f;   // アイコン拡大率（調整可）
    static const float BOMB_ICON_X = 50.0f;  // 左下からのX位置（調整可）
    static const float BOMB_ICON_Y = 80.0f;  // 左上からのY位置（調整可）
    static const float BOMB_ICON_SPACING = 50.0f;  // アイコン間隔（調整可）

    // バレットレベルUI
    static const int   BULLET_LEVEL_W = 250;
    static const int   BULLET_LEVEL_H = 48;
    static const float BULLET_LEVEL_SCALE = 1.0f;  // 拡大率（調整可）
    static const float BULLET_LEVEL_X = 50.0f; // 右上からのX位置（調整可）
    static const float BULLET_LEVEL_Y = 10.0f; // 右上からのY位置（調整可）

    // 音量設定（0.0f〜1.0f）
    static const float VOL_TITLE_BGM    = 0.6f;  // タイトルBGM（調整可）
    static const float VOL_GAME_BGM     = 0.3f;  // ゲームBGM（調整可）
    static const float VOL_BOSS_BGM     = 0.15f;  // ボスBGM（調整可）
    static const float VOL_SHOT_SE      = 0.3f;  // 発射SE（調整可）
    static const float VOL_BOMB_SE      = 0.9f;  // ボムSE（調整可）
    static const float VOL_DAMAGE_SE    = 0.9f;  // 被弾SE（調整可）
    static const float VOL_HIT_SE = 0.8f;  // 着弾SE（調整可）
    static const float VOL_POINT_SE = 0.2f;  // ポイント回収SE（調整可）
    static const float VOL_RESULT_SE = 0.4f;  // リザルトSE（調整可）
    static const float VOL_GAMEOVER_SE = 0.8f; // ゲームオーバーSE（調整可）

    // ポイントアイテム
    static const int   POINT_W = 24;
    static const int   POINT_H = 24;
    static const float POINT_SCALE = 1.0f;   // 調整可
    static const float POINT_FALL_SPEED = 2.0f;   // 落下速度（調整可）
    static const float POINT_COLLECT_DIST = 50.0f;  // 回収距離
    static const float POINT_ATTRACT_SPEED = 30.0f;  // 吸い寄せ速度（調整可）
    static const int   POINT_AUTO_COLLECT = 30;    // 自動回収までの時間（2秒）
    static const float POINT_MIN_Y = -(SCREEN_HALF_H - 20.0f); // 画面下限
    static const int   POINT_MAX = 50;     // 同時出現最大数
    static const float POINT_ALPHA = 0.5f; // アルファ値

    // プレイヤー死亡演出
    static const float PLAYER_DEATH_FALL_SPEED = 3.0f;  // 落下速度（調整可）
    static const float PLAYER_DEATH_FADE_SPEED = 0.02f; // フェード速度（調整可）
    static const int   PLAYER_DEATH_DELAY = 120;   // 死亡後リザルトまでの待機時間

}