#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"Player.h"
#include"Manager/EnemyManager.h"
#include"Manager/ItemManager.h"
#include"Stage.h"
#include "MiniMap.h"

MiniMap::MiniMap(Player* _player, EnemyManager* _eneMng, ItemManager* _itemMng, Stage* _stage)
	: player_(_player), eneMng_(_eneMng), itemMng_(_itemMng), stage_(_stage)
{

}

MiniMap::~MiniMap()
{
}

void MiniMap::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//�g
	mapFrameImg_ = res.Load(ResourceManager::SRC::MAP_FRAME).handleId_;
	//�g��
	mapGroundImg_ = res.Load(ResourceManager::SRC::MAP_GROUND).handleId_;
	//�}�b�v
	mapImg_ = res.Load(ResourceManager::SRC::MAP_IMAGE).handleId_;
	//�v���C���[
	mapPlayerImg_ = res.Load(ResourceManager::SRC::MAP_PLAYER).handleId_;
}

void MiniMap::Update(void)
{
}

void MiniMap::Draw(void)
{
	//�g���̕`��
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, IMAGE_EX_RATE, 0.0, mapGroundImg_,true);

	//�}�b�v�摜
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, IMAGE_EX_RATE, 0.0, mapImg_,true);

	//�v���C���[�`��
	DrawPlayer();
	
	//�g�̕`��
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, IMAGE_EX_RATE, 0.0, mapFrameImg_, true);
}

void MiniMap::Release(void)
{
}

const VECTOR MiniMap::GetDistance(const VECTOR _startObj, const VECTOR _goalObj)const
{
	//���΋���
	VECTOR ret;
	//�����x�N�g��
	VECTOR dir;
	//����
	float distance;
	//�}�b�v���a
	float radius = MAP_SIZE / 2;

	//����
	dir = GetMoveVec(_startObj, _goalObj);

	//����
	distance = CalcDistance(_startObj, _goalObj);

	//�}�b�v�ɍ��킹�ďk��
	distance *= MAP_EX_RATE;

	//���W�v�Z
	ret = VScale(dir, distance);

	return ret;
}

void MiniMap::DrawPlayer(void)
{
	//�v���C���[�̊p�x(Y��)
	double playerAngle = player_->GetTransform().quaRot.ToEuler().y;

	//�v���C���[����̑��΍��W�v�Z
	VECTOR distance = GetDistance(player_->GetPos(), stage_->GetPos());

	//�v���C���[�̕`��
	DrawRotaGraph(MAP_POS_X - distance.x, MAP_POS_Y + distance.z, IMAGE_EX_RATE, playerAngle, mapPlayerImg_, true);
}

void MiniMap::DrawEnemy(void)
{
	for (auto& enemy : eneMng_)
	{

	}
}

void MiniMap::DrawItem(void)
{
}

void MiniMap::DrawVision(void)
{
}

const VECTOR MiniMap::GetMoveVec(const VECTOR _start, const VECTOR _goal, const float _speed)const
{
	//�W�I�ւ̕����x�N�g�����擾
	VECTOR targetVec = VSub(_goal, _start);

	//���K��
	targetVec = VNorm(targetVec);

	//Y���W�͕K�v�Ȃ��̂ŗv�f������
	targetVec = { targetVec.x,0.0f,targetVec.z };

	//�ړ��ʂ����߂�
	VECTOR ret = VScale(targetVec, _speed);

	return ret;
}

const float MiniMap::CalcDistance(const VECTOR _start, const VECTOR _goal)const
{
	VECTOR ret;

	ret.x = powf(_goal.x - _start.x, 2);
	ret.y = powf(_goal.y - _start.y, 2);
	ret.z = powf(_goal.z - _start.z, 2);

	return sqrtf(ret.x + ret.y + ret.z);
}
