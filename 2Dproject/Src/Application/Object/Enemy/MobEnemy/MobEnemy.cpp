#include "MobEnemy.h"
#include "../../../AppConst.h"

void MobEnemy::Init()
{
	m_tex.Load("Texture/Enemy/MobEnemy/enemy.png");
	m_pos = {};
	m_aliveFlg = true;
}

void MobEnemy::Update()
{
	m_pos.x -= AppConst::ENEMY_SPEED;

	if (m_pos.x < -AppConst::SCREEN_HALF_W - AppConst::ENEMY_SIZE)
	{
		m_pos.x = AppConst::SCREEN_HALF_W + AppConst::ENEMY_SIZE;
	}

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void MobEnemy::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle{ 0,0,AppConst::ENEMY_SIZE,AppConst::ENEMY_SIZE }, 1.0f);
}

void MobEnemy::Release()
{
	m_tex.Release();
}
