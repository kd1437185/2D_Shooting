#include "CollisionManager.h"
#include "../Object/BaseObject.h"
#include "../Object/Bullet/Bullet.h"
#include "../Object/Bullet/HomingBullet.h"
#include "../Object/Bullet/DanmakuBullet.h"
#include "../AppConst.h"
#include "../Score/ScoreManager.h"
#include "../Wave/WaveManager.h"
#include "../Object/Enemy/MobEnemy/MobEnemy.h"
#include "../Object/Enemy/ShooterEnemy/ShooterEnemy.h"
#include "../Object/Enemy/TankEnemy/TankEnemy.h"
#include "../Object/Enemy/Boss/Boss.h"
#include "../Effect/EffectManager.h"
#include "../Object/Player/Player.h"
#include "../Health/HealthManager.h"

bool CollisionManager::CircleCollision(
    const Math::Vector2& _posA, float _radiusA,
    const Math::Vector2& _posB, float _radiusB)
{
    Math::Vector2 diff = { _posA.x - _posB.x, _posA.y - _posB.y };
    float distSq = diff.x * diff.x + diff.y * diff.y;
    float radiusSum = _radiusA + _radiusB;
    return distSq <= radiusSum * radiusSum;
}

void CollisionManager::CheckBulletsVsEnemies(
    std::vector<std::shared_ptr<Bullet>>& _bullets,
    std::vector<std::shared_ptr<BaseObject>>& _enemies)
{
    for (auto& bullet : _bullets)
    {
        if (!bullet || !bullet->IsAlive()) continue;

        for (auto& enemy : _enemies)
        {
            // フェード中・非アクティブはスキップ
            if (!enemy || !enemy->IsAlive() || enemy->IsFading()) continue;

            float radius = AppConst::ENEMY_RADIUS;
            if (std::dynamic_pointer_cast<ShooterEnemy>(enemy))
                radius = AppConst::SHOOTER_RADIUS;
            else if (std::dynamic_pointer_cast<TankEnemy>(enemy))
                radius = AppConst::TANK_RADIUS;

            if (CircleCollision(
                bullet->GetPos(), AppConst::BULLET_RADIUS,
                enemy->GetPos(), radius))
            {
                bullet->SetAlive(false);
                enemy->Damage(bullet->GetDamage());
                EffectManager::Instance().PlayHitEffect(bullet->GetPos());

                // フェードアウト開始 = 死亡
                if (enemy->IsFading())
                {
                    if (std::dynamic_pointer_cast<ShooterEnemy>(enemy))
                        ScoreManager::Instance().AddScore(AppConst::SCORE_PER_SHOOTER);
                    else if (std::dynamic_pointer_cast<TankEnemy>(enemy))
                        ScoreManager::Instance().AddScore(AppConst::SCORE_PER_TANK);
                    else
                        ScoreManager::Instance().AddScore(AppConst::SCORE_PER_ENEMY);

                    WaveManager::Instance().OnEnemyDefeated();
                }
            }
        }
    }
}

void CollisionManager::CheckBulletsVsBoss(
    std::vector<std::shared_ptr<Bullet>>& _bullets,
    std::shared_ptr<Boss>& _boss)
{
    if (!_boss || !_boss->IsAlive()) return;
    if (!_boss->IsCollidable()) return;

    for (auto& bullet : _bullets)
    {
        if (!bullet || !bullet->IsAlive()) continue;

        if (CircleCollision(
            bullet->GetPos(), AppConst::BULLET_RADIUS,
            _boss->GetPos(), AppConst::BOSS_RADIUS))
        {
            bullet->SetAlive(false);
            _boss->Damage(bullet->GetDamage());
            EffectManager::Instance().PlayHitEffect(bullet->GetPos());

            if (_boss->IsDead())
            {
                ScoreManager::Instance().AddScore(AppConst::SCORE_PER_BOSS);
            }
        }
    }
}

void CollisionManager::CheckHomingVsEnemies(
    std::vector<std::shared_ptr<HomingBullet>>& _bullets,
    std::vector<std::shared_ptr<BaseObject>>& _enemies)
{
    for (auto& bullet : _bullets)
    {
        if (!bullet || !bullet->IsAlive()) continue;

        for (auto& enemy : _enemies)
        {
            // フェード中・非アクティブはスキップ
            if (!enemy || !enemy->IsAlive() || enemy->IsFading()) continue;

            float radius = AppConst::ENEMY_RADIUS;
            if (std::dynamic_pointer_cast<ShooterEnemy>(enemy))
                radius = AppConst::SHOOTER_RADIUS;
            else if (std::dynamic_pointer_cast<TankEnemy>(enemy))
                radius = AppConst::TANK_RADIUS;

            if (CircleCollision(
                bullet->GetPos(), AppConst::BULLET_RADIUS,
                enemy->GetPos(), radius))
            {
                bullet->SetAlive(false);
                enemy->Damage(bullet->GetDamage());
                EffectManager::Instance().PlayHitEffect(bullet->GetPos());

                if (enemy->IsFading())
                {
                    if (std::dynamic_pointer_cast<ShooterEnemy>(enemy))
                        ScoreManager::Instance().AddScore(AppConst::SCORE_PER_SHOOTER);
                    else if (std::dynamic_pointer_cast<TankEnemy>(enemy))
                        ScoreManager::Instance().AddScore(AppConst::SCORE_PER_TANK);
                    else
                        ScoreManager::Instance().AddScore(AppConst::SCORE_PER_ENEMY);

                    WaveManager::Instance().OnEnemyDefeated();
                }
            }
        }
    }
}

void CollisionManager::CheckHomingVsBoss(
    std::vector<std::shared_ptr<HomingBullet>>& _bullets,
    std::shared_ptr<Boss>& _boss)
{
    if (!_boss || !_boss->IsAlive()) return;
    if (!_boss->IsCollidable()) return;

    for (auto& bullet : _bullets)
    {
        if (!bullet || !bullet->IsAlive()) continue;

        if (CircleCollision(
            bullet->GetPos(), AppConst::BULLET_RADIUS,
            _boss->GetPos(), AppConst::BOSS_RADIUS))
        {
            bullet->SetAlive(false);
            _boss->Damage(bullet->GetDamage());
            EffectManager::Instance().PlayHitEffect(bullet->GetPos());

            if (_boss->IsDead())
            {
                ScoreManager::Instance().AddScore(AppConst::SCORE_PER_BOSS);
            }
        }
    }
}

void CollisionManager::CheckEnemyBulletsVsPlayer(
    std::vector<std::shared_ptr<BaseObject>>& _enemies,
    std::shared_ptr<Player>& _player)
{
    if (!_player) return;

    for (auto& e : _enemies)
    {
        // MobEnemy
        auto mob = std::dynamic_pointer_cast<MobEnemy>(e);
        if (mob)
        {
            for (auto& b : mob->GetBullets())
            {
                if (!b || !b->IsAlive()) continue;
                if (CircleCollision(
                    b->GetPos(), AppConst::ENEMY_BULLET_RADIUS,
                    _player->GetPos(), AppConst::PLAYER_RADIUS))
                {
                    b->SetAlive(false);
                    HealthManager::Instance().Damage();
                }
            }
            continue;
        }

        // ShooterEnemy
        auto shooter = std::dynamic_pointer_cast<ShooterEnemy>(e);
        if (shooter)
        {
            for (auto& b : shooter->GetBullets())
            {
                if (!b || !b->IsAlive()) continue;
                if (CircleCollision(
                    b->GetPos(), AppConst::ENEMY_BULLET_RADIUS,
                    _player->GetPos(), AppConst::PLAYER_RADIUS))
                {
                    b->SetAlive(false);
                    HealthManager::Instance().Damage();
                }
            }
            continue;
        }

        // TankEnemy
        auto tank = std::dynamic_pointer_cast<TankEnemy>(e);
        if (tank)
        {
            for (auto& b : tank->GetBullets())
            {
                if (!b || !b->IsAlive()) continue;
                if (CircleCollision(
                    b->GetPos(), AppConst::TANK_BULLET_RADIUS,
                    _player->GetPos(), AppConst::PLAYER_RADIUS))
                {
                    b->SetAlive(false);
                    HealthManager::Instance().Damage();
                }
            }
        }
    }
}

void CollisionManager::CheckDanmakuVsPlayer(
    std::vector<std::shared_ptr<DanmakuBullet>>& _bullets,
    std::shared_ptr<Player>& _player)
{
    if (!_player) return;

    for (auto& b : _bullets)
    {
        if (!b || !b->IsAlive()) continue;
        if (CircleCollision(
            b->GetPos(), AppConst::DANMAKU_BULLET_RADIUS,
            _player->GetPos(), AppConst::PLAYER_RADIUS))
        {
            b->SetAlive(false);
            HealthManager::Instance().Damage();
        }
    }
}