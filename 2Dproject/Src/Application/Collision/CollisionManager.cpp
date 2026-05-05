#include "CollisionManager.h"
#include "../Object/BaseObject.h"
#include "../Object/Bullet/Bullet.h"
#include "../AppConst.h"
#include "../Score/ScoreManager.h"

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

            if (CircleCollision(
                bullet->GetPos(), AppConst::BULLET_RADIUS,
                enemy->GetPos(), AppConst::ENEMY_RADIUS))
            {
                bullet->SetAlive(false);
                enemy->SetAlive(false);
                ScoreManager::Instance().AddScore(AppConst::SCORE_PER_ENEMY);
            }
        }
    }
}