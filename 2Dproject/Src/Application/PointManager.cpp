#include "PointManager.h"
#include "AppConst.h"
#include "Score/ScoreManager.h"
#include "Application/Sound/SoundManager.h"

void PointManager::Init()
{
    m_Items.clear();
    for (int i = 0; i < AppConst::POINT_MAX; i++)
    {
        auto item = std::make_shared<PointItem>();
        item->Init();
        m_Items.push_back(item);
    }
}

void PointManager::Update(Math::Vector2 _playerPos)
{
    for (auto& item : m_Items)
    {
        if (!item || !item->IsAlive()) continue;

        // プレイヤー位置を渡して吸い寄せフラグを更新
        item->CheckCollect(_playerPos);

        // 移動・回収処理
        item->Update();

        // 回収完了したらスコア加算
        if (item->IsCollected())
        {
            ScoreManager::Instance().AddScore(item->GetValue());
            SoundManager::Instance().PlayPointSE();
            item->Collect(); // フラグリセット
        }
    }
}

void PointManager::Draw()
{
    for (auto& item : m_Items)
    {
        if (item && item->IsAlive()) item->Draw();
    }
}

void PointManager::Release()
{
    for (auto& item : m_Items)
    {
        if (item) item->Release();
    }
    m_Items.clear();
}

void PointManager::SpawnPoint(Math::Vector2 _pos, int _value)
{
    for (auto& item : m_Items)
    {
        if (item && !item->IsAlive())
        {
            item->Spawn(_pos, _value);
            return;
        }
    }
}