#include "CollisionManager.h"
#include "../Object/BaseObject.h"
#include "../Object/Bullet/Bullet.h"
#include "../AppConst.h"
#include "../Score/ScoreManager.h"
#include "../Wave/WaveManager.h"
#include "../Object/Enemy/ShooterEnemy/ShooterEnemy.h"

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
            {
                radius = AppConst::SHOOTER_RADIUS;
            }

            if (CircleCollision(
                bullet->GetPos(), AppConst::BULLET_RADIUS,
                enemy->GetPos(), radius))
            {
                bullet->SetAlive(false);
                enemy->SetAlive(false);

                if (std::dynamic_pointer_cast<ShooterEnemy>(enemy))
                {
                    ScoreManager::Instance().AddScore(AppConst::SCORE_PER_SHOOTER);
                }
                else
                {
                    ScoreManager::Instance().AddScore(AppConst::SCORE_PER_ENEMY);
                }

                WaveManager::Instance().OnEnemyDefeated();
            }
        }
    }
}