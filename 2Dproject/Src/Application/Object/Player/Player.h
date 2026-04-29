#pragma once

#include "../BaseObject.h"

class Player : public BaseObject
{
public:

	Player() { Init(); }
	~Player() override{}

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	Math::Matrix m_playerMat;
};