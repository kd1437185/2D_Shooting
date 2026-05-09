#pragma once
#include "../BaseObject.h"
#include "Application/AppConst.h"

class EnemyBullet : public BaseObject
{
public:
    EnemyBullet() {}
    ~EnemyBullet() override {}

    void Init()    override; // 引数なし版（BaseObjectの純粋仮想関数）
    void InitWithTex(const char* _texPath = "Texture/Bullet/Enemy_bullet_blue.png");
    void Update()  override;
    void Draw()    override;
    void Release() override;

    // 発射位置・方向ベクトルを指定して発射
    void Fire(Math::Vector2 _startPos, Math::Vector2 _targetPos);

    bool IsAlive()  const { return m_aliveFlg; }
    void SetAlive(bool b) { m_aliveFlg = b; }
    float GetRadius() const { return AppConst::ENEMY_BULLET_RADIUS; }
    void FireVelocity(Math::Vector2 _startPos, float _velX, float _velY);
    void FireWithGravity(Math::Vector2 _startPos, float _velX, float _velY, float _gravity);

    void SetTexSize(float _w, float _h) { m_texW = _w; m_texH = _h; }

private:
    float m_velX = 0.0f;
    float m_velY = 0.0f;

    float m_gravity = 0.0f; // 重力加速度
    float m_texW = AppConst::ENEMY_BULLET_W;
    float m_texH = AppConst::ENEMY_BULLET_H;
};