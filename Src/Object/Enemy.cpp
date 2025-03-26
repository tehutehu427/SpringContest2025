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
/// 時計回り
/// </summary>
/// <param name=""></param>
void Enemy::Clockwise(void)
{
	//時計回り
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
/// 反時計回り
/// </summary>
/// <param name=""></param>
void Enemy::CounterClockwise(void)
{	
	//反時計回り
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
/// 初期位置
/// </summary>
/// <param name="pos"></param>
void Enemy::SetPos(const VECTOR& pos)
{
	trans_.pos = pos;
}

/// <summary>
/// 移動ポイント(正方形)
/// </summary>
/// <param name="squarSize_">正方形の移動経路の一辺の長さ</param>
/// <returns></returns>
void Enemy::SetMovePoint(const float& squarSize)
{
	//左上
	movePointPos_[0]=trans_.pos;
	//右上
	movePointPos_[1] = { trans_.pos.x + squarSize,trans_.pos.y,trans_.pos.z };
	//右下
	movePointPos_[2] = { trans_.pos.x + squarSize,trans_.pos.y,trans_.pos.z - squarSize };
	//左下
	movePointPos_[3] = { trans_.pos.x ,trans_.pos.y,trans_.pos.z - squarSize };
}

/// <summary>
/// 移動速度
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

const VECTOR Enemy::GetMoveVec(const VECTOR _start, const VECTOR _goal, const float _speed)const
{
	//標的への方向ベクトルを取得
	VECTOR targetVec = VSub(_goal, _start);

	//正規化
	targetVec = VNorm(targetVec);

	//Y座標は必要ないので要素を消す
	targetVec = { targetVec.x,0.0f,targetVec.z };

	//移動量を求める
	VECTOR ret = VScale(targetVec, _speed);

	return ret;
}

const float Enemy::CalcDistance(const VECTOR _start, const VECTOR _goal)const
{
	VECTOR ret;

	ret.x = powf(_goal.x - _start.x, 2);
	ret.y = powf(_goal.y - _start.y, 2);
	ret.z = powf(_goal.z - _start.z, 2);

	return sqrtf(ret.x + ret.y + ret.z);
}
