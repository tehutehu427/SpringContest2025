#include"../Utility/AsoUtility.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(void)
{
	//trans_.pos = { -STAGE_SIZE/2,ENEMY_SIZE,STAGE_SIZE / 2 };
	trans_.pos = { -STAGE_SIZE/2,ENEMY_SIZE, -STAGE_SIZE / 2 };
	trans_.scl = AsoUtility::VECTOR_ONE;
	trans_.rot = AsoUtility::VECTOR_ZERO;
	moveDir_ = MOVEDIR::RIGHT;
}

void Enemy::Update(void)
{
	//ŽžŒv‰ñ‚è
	switch (moveDir_)
	{
	case Enemy::MOVEDIR::UP:
		trans_.pos.z += MOVE_SPEED;
		if (trans_.pos.z + ENEMY_SIZE >= STAGE_SIZE / 2) {
			moveDir_ = MOVEDIR::RIGHT;
		}

		break;
	case Enemy::MOVEDIR::LEFT:
		trans_.pos.x -= MOVE_SPEED;
		if (trans_.pos.x - ENEMY_SIZE <= -STAGE_SIZE / 2) {
			moveDir_ = MOVEDIR::UP;
		}

		break;
	case Enemy::MOVEDIR::RIGHT:
		trans_.pos.x += MOVE_SPEED;
		if (trans_.pos.x + ENEMY_SIZE >= STAGE_SIZE / 2) {
			moveDir_ = MOVEDIR::DOWN;
		}

		break;
	case Enemy::MOVEDIR::DOWN:
		trans_.pos.z -= MOVE_SPEED;
		if (trans_.pos.z - ENEMY_SIZE <= -STAGE_SIZE / 2) {
			moveDir_ = MOVEDIR::LEFT;
		}
		break;
	}

}

void Enemy::Draw(void)
{
	DrawSphere3D(trans_.pos,ENEMY_SIZE , 10, 
		GetColor(255, 255, 255), GetColor(255, 255, 255), true);
}

void Enemy::Release(void)
{
}




//VECTOR Enemy::GetPos(void) const
//{
//	return trans_.pos;
//}

void Enemy::SetPos(const VECTOR& pos)
{
	trans_.pos = pos;
}
