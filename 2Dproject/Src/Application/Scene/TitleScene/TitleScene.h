#pragma once

#include "../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:
	TitleScene() { Init(); }
	~TitleScene(){}

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;

private:

	// ƒ^ƒCƒgƒ‹”wŒi
	KdTexture m_BackTex;
	Math::Matrix m_BackMat;

};

