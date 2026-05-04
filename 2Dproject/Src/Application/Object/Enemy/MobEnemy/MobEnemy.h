#pragma once

#include"Application/Object/BaseObject.h"

class MobEnemy : public BaseObject
{
public:

	MobEnemy() {}
	~MobEnemy()override {}

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;

private:

};