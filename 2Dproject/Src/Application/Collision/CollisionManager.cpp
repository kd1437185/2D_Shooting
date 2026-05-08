#include "CollisionManager.h"
#include "../Object/BaseObject.h"
#include "../Object/Bullet/Bullet.h"
#include "../AppConst.h"
#include "../Score/ScoreManager.h"
#include "../Wave/WaveManager.h"
#include "../Object/Enemy/ShooterEnemy/ShooterEnemy.h"
#include "../Object/Enemy/TankEnemy/TankEnemy.h"
#include "../Object/Enemy/Boss/Boss.h"

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
            if (!enemy || !enemy->IsAlive()) continue;

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
                enemy->Damage(bullet->GetDamage()); // Bulletのダメージを使用

                if (enemy->IsDead())
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

// ボス専用の当たり判定を追加
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
            _boss->Damage(bullet->GetDamage()); // Bulletのダメージを使用

            if (_boss->IsDead())
            {
                ScoreManager::Instance().AddScore(AppConst::SCORE_PER_BOSS);
                _boss->TriggerDeath();
            }
        }
    }
}