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
	trans_.pos = AsoUtility::VECTOR_ZERO;
	trans_.scl = AsoUtility::VECTOR_ONE;
	trans_.rot = AsoUtility::VECTOR_ZERO;

	moveDir_ = MOVEDIR::UP;
}

void Enemy::Update(void)
{
	EnemyMove();

	
}

void Enemy::Draw(void)
{
	DrawSphere3D(trans_.pos,ENEMY_SIZE , 10, 
		GetColor(255, 255, 255), GetColor(255, 255, 255), true);
	DrawFormatString(0, DebugDrawPos, 0xffffff, "enemy(%.2f,%.2f,%.2f)", trans_.pos.x, trans_.pos.y, trans_.pos.z);

}
void Enemy::SetDebugDrawPos(const int& pos)
{
	DebugDrawPos = pos;
}

void Enemy::Release(void)
{

}

//VECTOR Enemy::GetPos(void) const
//{
//	return trans_.pos;
//}

void Enemy::EnemyMove(void)
{	
	switch (moveClockDir_)
	{
	case Enemy::MOVECLOCKDIR::CLOCKWISE:
		Clockwise();
		break;
	case Enemy::MOVECLOCKDIR::COUNTERCLOCKWISE:
		CounterClockwise();
		break;
	}
}

/// <summary>
/// ���v���
/// </summary>
/// <param name=""></param>
void Enemy::Clockwise(void)
{
	//���v���
	switch (moveDir_)
	{
	case Enemy::MOVEDIR::UP:
		trans_.pos.z += moveSpeed_;
		if (trans_.pos.z >= movePointPos_[0].z) {
			moveDir_ = MOVEDIR::RIGHT;
		}
		break;
	case Enemy::MOVEDIR::LEFT:
		trans_.pos.x -= moveSpeed_;
		if (trans_.pos.x <= movePointPos_[3].x) {
			moveDir_ = MOVEDIR::UP;
		}
		break;
	case Enemy::MOVEDIR::RIGHT:
		trans_.pos.x += moveSpeed_;
		if (trans_.pos.x >= movePointPos_[1].x) {
			moveDir_ = MOVEDIR::DOWN;
		}
		break;
	case Enemy::MOVEDIR::DOWN:
		trans_.pos.z -= moveSpeed_;
		if (trans_.pos.z <= movePointPos_[2].z) {
			moveDir_ = MOVEDIR::LEFT;
		}
		break;
	}
}

/// <summary>
/// �����v���
/// </summary>
/// <param name=""></param>
void Enemy::CounterClockwise(void)
{	
	//�����v���
	switch (moveDir_)
	{
	case Enemy::MOVEDIR::UP:
		trans_.pos.z += moveSpeed_;
		if (trans_.pos.z >= movePointPos_[0].z) {
			moveDir_ = MOVEDIR::LEFT;
		}
		break;
	case Enemy::MOVEDIR::LEFT:
		trans_.pos.x -= moveSpeed_;
		if (trans_.pos.x <= movePointPos_[3].x) {
			moveDir_ = MOVEDIR::DOWN;
		}
		break;
	case Enemy::MOVEDIR::RIGHT:
		trans_.pos.x += moveSpeed_;
		if (trans_.pos.x >= movePointPos_[1].x) {
			moveDir_ = MOVEDIR::UP;
		}
		break;
	case Enemy::MOVEDIR::DOWN:
		trans_.pos.z -= moveSpeed_;
		if (trans_.pos.z <= movePointPos_[2].z) {
			moveDir_ = MOVEDIR::RIGHT;
		}
		break;
	}
}



/// <summary>
/// �����ʒu
/// </summary>
/// <param name="pos"></param>
void Enemy::SetPos(const VECTOR& pos)
{
	trans_.pos = pos;
}

/// <summary>
/// �ړ��|�C���g(�����`)
/// </summary>
/// <param name="squarSize_">�����`�̈ړ��o�H�̈�ӂ̒���</param>
/// <returns></returns>
void Enemy::SetMovePoint(const float& squarSize)
{
	//����
	movePointPos_[0]=trans_.pos;
	//�E��
	movePointPos_[1] = { trans_.pos.x + squarSize,trans_.pos.y,trans_.pos.z };
	//�E��
	movePointPos_[2] = { trans_.pos.x + squarSize,trans_.pos.y,trans_.pos.z - squarSize };
	//����
	movePointPos_[3] = { trans_.pos.x ,trans_.pos.y,trans_.pos.z - squarSize };
}

/// <summary>
/// �ړ����x
/// </summary>
/// <param name="moveSpeed"></param>
/// <returns></returns>
void Enemy::SetMoveSpeed(const float& moveSpeed)
{
	moveSpeed_ = moveSpeed;
}

Enemy::MOVECLOCKDIR Enemy::SetMoveClockDir(const MOVECLOCKDIR& moveClockDir)
{
	return moveClockDir_=moveClockDir;
}

Enemy::MOVEDIR Enemy::SetMoveDir(const MOVEDIR& moveDir)
{
	return moveDir_=moveDir;
}

