#pragma once

class BaseObject;
class Bullet;

class CollisionManager
{
public:
    // ‰~”»’èi2“_ŠÔ‚Ì‹——£‚Å”»’èj
    static bool CircleCollision(
        const Math::Vector2& _posA, float _radiusA,
        const Math::Vector2& _posB, float _radiusB);

    // ’e‚Æ“G‚Ì“–‚½‚è”»’è‚ğ‚Ü‚Æ‚ß‚Äˆ—
    static void CheckBulletsVsEnemies(
        std::vector<std::shared_ptr<Bullet>>& _bullets,
        std::vector<std::shared_ptr<BaseObject>>& _enemies);
};