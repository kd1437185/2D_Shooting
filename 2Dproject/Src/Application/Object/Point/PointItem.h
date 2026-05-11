#pragma once
#include "../BaseObject.h"

class PointItem : public BaseObject
{
public:
    PointItem() {}
    ~PointItem() override {}

    void Init()    override;
    void Update()  override;
    void Draw()    override;
    void Release() override;

    void Spawn(Math::Vector2 _pos, int _value);
    void Collect(); // 回収

    bool IsCollected() const { return m_collected; }
    int  GetValue()    const { return m_value; }

    // プレイヤー位置を渡して回収判定
    bool CheckCollect(Math::Vector2 _playerPos);

private:
    int   m_value = 0;
    bool  m_collected = false;
    int   m_autoTimer = 0;    // 自動回収タイマー
    bool  m_attracting = false; // 吸い寄せ中か
    Math::Vector2 m_playerPos = {};
};