#pragma once

#include "../BaseScene/BaseScene.h"

class BaseObject;

class GameScene : public BaseScene
{
public:
	GameScene() { Init(); }
	~GameScene(){}

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;

private:

	// ÉQÅ[ÉÄâÊñ îwåi
	KdTexture m_BackTex;
	Math::Matrix m_BackMat;

	std::shared_ptr<BaseObject> m_player = nullptr;

};