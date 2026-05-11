#pragma once
#include "Object/Point/PointItem.h"

class PointManager
{
public:
    void Init();
    void Update(Math::Vector2 _playerPos);
    void Draw();
    void Release();

    void SpawnPoint(Math::Vector2 _pos, int _value);

    // ƒVƒ“ƒOƒ‹ƒgƒ“
private:
    PointManager() {}
    ~PointManager() {}
    PointManager(const PointManager&) = delete;
    PointManager& operator=(const PointManager&) = delete;

    std::vector<std::shared_ptr<PointItem>> m_Items;

public:
    static PointManager& Instance()
    {
        static PointManager instance;
        return instance;
    }
};