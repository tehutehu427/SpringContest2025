#include"../Application.h"
#include"../Utility/AsoUtility.h"
#include"../Manager/System/Timer.h"
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(void)
{
	trans_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::ENEMY));

	trans_.pos = AsoUtility::VECTOR_ZERO;
	trans_.scl = AsoUtility::VECTOR_ONE;
	trans_.rot = AsoUtility::VECTOR_ZERO;
	trans_.quaRot = Quaternion();
	trans_.quaRotLocal =
		Quaternion::Euler({ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f });

	moveDir_ = MOVEDIR::UP;

	nowPos_ = AsoUtility::VECTOR_ZERO;
	goalPos_ = AsoUtility::VECTOR_ZERO;

	radius_ = ENEMY_SIZE;
	speed_ = 0.0f;
	atkCnt_ = ATK_CNT;

	//モデル制御
	trans_.Update();

	//アニメーションリセット
	InitAnimation();
}

void Enemy::Update(void)
{
	//前座標更新
	prePos_ = trans_.pos;

	//攻撃時間更新
	if (atkCnt_ < ATK_CNT)Timer::GetInstance().CntUp(atkCnt_);

	EnemyMove();

	//モデル制御
	trans_.Update();

	//アニメーション
	anim_->Update();
}

void Enemy::Draw(void)
{
	//DrawSphere3D(trans_.pos,ENEMY_SIZE , 10, 
	//	GetColor(255, 255, 255), GetColor(255, 255, 255), false);
	//DrawFormatString(0, DebugDrawPos, 0xffffff, "enemy(%.2f,%.2f,%.2f)", trans_.pos.x, trans_.pos.y, trans_.pos.z);

	MV1DrawModel(trans_.modelId);

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
		trans_.pos.z += speed_;
		if (trans_.pos.z >= movePointPos_[0].z) {
			moveDir_ = MOVEDIR::RIGHT;

			nowPos_ = movePointPos_[0];
			goalPos_ = movePointPos_[1];
		}

		trans_.quaRot = Quaternion::LookRotation({ 0.0f,0.0f,1.0f });

		break;
	case Enemy::MOVEDIR::LEFT:
		trans_.pos.x -= speed_;
		if (trans_.pos.x <= movePointPos_[3].x) {
			moveDir_ = MOVEDIR::UP;

			nowPos_ = movePointPos_[3];
			goalPos_ = movePointPos_[0];
		}

		trans_.quaRot = Quaternion::LookRotation({-1.0f,0.0f,0.0f});

		break;
	case Enemy::MOVEDIR::RIGHT:
		trans_.pos.x += speed_;
		if (trans_.pos.x >= movePointPos_[1].x) {
			moveDir_ = MOVEDIR::DOWN;

			nowPos_ = movePointPos_[1];
			goalPos_ = movePointPos_[2];
		}

		trans_.quaRot = Quaternion::LookRotation({ 1.0f,0.0f,0.0f });

		break;
	case Enemy::MOVEDIR::DOWN:
		trans_.pos.z -= speed_;
		if (trans_.pos.z <= movePointPos_[2].z) {
			moveDir_ = MOVEDIR::LEFT;

			nowPos_ = movePointPos_[2];
			goalPos_ = movePointPos_[3];
		}

		trans_.quaRot = Quaternion::LookRotation({ 0.0f,0.0f,-1.0f });

		break;
	}
	GetMoveVec(nowPos_, goalPos_, speed_);
	CalcDistance(nowPos_, goalPos_);
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
		trans_.pos.z += speed_;
		if (trans_.pos.z >= movePointPos_[0].z) {
			moveDir_ = MOVEDIR::LEFT;
		
			nowPos_ = movePointPos_[0];
			goalPos_ = movePointPos_[3];
		}
		trans_.quaRot = Quaternion::LookRotation({ 0.0f,0.0f,1.0f });
		break;
	case Enemy::MOVEDIR::LEFT:
		trans_.pos.x -= speed_;
		if (trans_.pos.x <= movePointPos_[3].x) {
			moveDir_ = MOVEDIR::DOWN;

			nowPos_ = movePointPos_[3];
			goalPos_ = movePointPos_[2];
		}
		trans_.quaRot = Quaternion::LookRotation({ -1.0f,0.0f,0.0f });
		break;
	case Enemy::MOVEDIR::RIGHT:
		trans_.pos.x += speed_;
		if (trans_.pos.x >= movePointPos_[1].x) {
			moveDir_ = MOVEDIR::UP;

			nowPos_ = movePointPos_[1];
			goalPos_ = movePointPos_[0];
		}
		trans_.quaRot = Quaternion::LookRotation({ 1.0f,0.0f,0.0f });
		break;
	case Enemy::MOVEDIR::DOWN:
		trans_.pos.z -= speed_;
		if (trans_.pos.z <= movePointPos_[2].z) {
			moveDir_ = MOVEDIR::RIGHT;

			nowPos_ = movePointPos_[2];
			goalPos_ = movePointPos_[1];
		}
		trans_.quaRot = Quaternion::LookRotation({ 0.0f,0.0f,-1.0f });
		break;
	}
	GetMoveVec(nowPos_, goalPos_, speed_);
	CalcDistance(nowPos_, goalPos_);
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
	speed_ = moveSpeed;
}

/// <summary>
/// 時計回り、反時計回り
/// </summary>
/// <param name="moveClockDir"></param>
/// <returns></returns>
Enemy::MOVECLOCKDIR Enemy::SetMoveClockDir(const MOVECLOCKDIR& moveClockDir)
{
	return moveClockDir_=moveClockDir;
}

/// <summary>
/// 
/// </summary>
/// <param name="moveDir"></param>
/// <returns></returns>
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

void Enemy::InitAnimation(void)
{
	std::string path = Application::PATH_ANIM + "Enemy/";

	//アニメーションコントローラー作成
	anim_ = std::make_unique<AnimationController>(trans_.modelId);

	//アニメーション追加
	anim_->Add((int)ANIM::IDLE, path + "Zombie_Idle.mv1", ANIM_SPEED);
	anim_->Add((int)ANIM::WALK, path + "Zombie_Walk.mv1", ANIM_SPEED);

	//最初のアニメーション
	anim_->Play((int)ANIM::WALK);
}
