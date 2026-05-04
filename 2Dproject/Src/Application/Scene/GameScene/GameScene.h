#pragma once

#include "../BaseScene/BaseScene.h"

class BaseObject;

class GameScene : public BaseScene
{
public:
	GameScene() {}
	~GameScene() override {}

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;

private:

	// ƒQ[ƒ€‰æ–Ê”wŒi
	KdTexture		m_BackTex;
	Math::Matrix	m_BackMat;

	std::shared_ptr<BaseObject> m_player = nullptr;
	std::vector<std::shared_ptr<BaseObject>> m_Enemies;	// •¡”‘Î‰

	bool m_prevSpace = false;

};