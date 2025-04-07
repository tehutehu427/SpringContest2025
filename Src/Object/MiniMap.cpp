#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"Player.h"
#include"Manager/EnemyManager.h"
#include"Enemy.h"
#include"Manager/ItemManager.h"
#include"Item.h"
#include"Stage.h"
#include "MiniMap.h"

MiniMap::MiniMap(Player* _player, EnemyManager* _eneMng, ItemManager* _itemMng, Stage* _stage)
	: player_(_player), eneMng_(_eneMng), itemMng_(_itemMng), stage_(_stage)
{
	//maskScreen_ = -1;

	mapFrameImg_ = -1;
	mapGroundImg_ = -1;
	mapImg_ = -1;
	mapPlayerImg_ = -1;
	mapEnemyImg_ = -1;
}

MiniMap::~MiniMap()
{
}

void MiniMap::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//�X�N���[���쐬
	//maskScreen_ = MakeScreen(MAP_SIZE, MAP_SIZE, TRUE);

	//�}�X�N�p�Ƃ��ăn���h���Z�b�g
	//SetMaskScreenGraph(maskScreen_);

	//�}�X�N��ʂ̍쐬
	CreateMaskScreen();

	//�摜�n���h��
	//------------------------------------

	//�g
	mapFrameImg_ = res.Load(ResourceManager::SRC::MAP_FRAME).handleId_;
	//�g��
	mapGroundImg_ = res.Load(ResourceManager::SRC::MAP_GROUND).handleId_;
	//�}�X�N
	mapMaskImg_ = res.Load(ResourceManager::SRC::MAP_MASK).handleId_;
	//�}�b�v
	mapImg_ = res.Load(ResourceManager::SRC::MAP_IMAGE).handleId_;
	//�v���C���[
	mapPlayerImg_ = res.Load(ResourceManager::SRC::MAP_PLAYER).handleId_;
	//�G
	mapEnemyImg_ = res.Load(ResourceManager::SRC::MAP_ENEMY).handleId_;
}

void MiniMap::Update(void)
{
}

void MiniMap::Draw(void)
{
	//�}�X�N�p�ɃX�N���[����ύX
	//SetDrawScreen(maskScreen_);

	//�}�X�N�摜�N���A
	//ClearDrawScreen();

	//�g���̕`��
	DrawMask(MAP_POS_X - MAP_SIZE+5, MAP_POS_Y - MAP_SIZE+5, mapMaskImg_, DX_MASKTRANS_NONE);

	//�`���𗠉�ʂɕύX
	//SetDrawScreen(DX_SCREEN_BACK);
	
	//�}�X�N��L���ɂ���
	SetUseMaskScreenFlag(TRUE);

	//�g���摜
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, MAP_EX_RATE, 0.0, mapGroundImg_, true);

	//�}�b�v�摜
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, MAP_EX_RATE, 0.0, mapImg_, true);

	//�v���C���[�`��
	DrawPlayer();

	//�G�̕`��
	DrawEnemy();

	//�A�C�e���̕`��
	DrawItem();

	//�}�X�N�𖳌��ɂ���
	SetUseMaskScreenFlag(FALSE);

	//�g�̕`��
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, MAP_EX_RATE, 0.0, mapFrameImg_, true);
}

void MiniMap::Release(void)
{
	//�}�X�N�X�N���[�����폜
	DeleteMaskScreen();
}

const VECTOR MiniMap::GetDistance(const VECTOR _startObj, const VECTOR _goalObj)const
{
	//���΋���
	VECTOR ret;
	//�����x�N�g��
	VECTOR dir;
	//����
	float distance;

	//����
	dir = GetMoveVec(_startObj, _goalObj);

	//����
	distance = CalcDistance(_startObj, _goalObj);

	//�}�b�v�ɍ��킹�ďk��
	distance *= MAP_RELATIVE_EX_RATE;

	//���W�v�Z
	ret = VScale(dir, distance);

	return ret;
}

void MiniMap::DrawPlayer(void)
{
	//�v���C���[�̊p�x(Y��)
	double playerAngle = player_->GetTransform().quaRot.ToEuler().y;

	//�X�e�[�W����̑��΍��W�v�Z
	VECTOR distance = GetDistance(player_->GetPos(), stage_->GetPos());

	//�v���C���[�̕`��
	DrawRotaGraph(MAP_POS_X - distance.x, MAP_POS_Y + distance.z, IMAGE_EX_RATE, playerAngle, mapPlayerImg_, true);
}

void MiniMap::DrawEnemy(void)
{
	for (auto& enemy : eneMng_->GetEnemys())
	{
		//�G�̊p�x(Y��)
		double enemyAngle = enemy.get()->GetTransform().quaRot.ToEuler().y;

		//�X�e�[�W����̑��΍��W�v�Z
		VECTOR distance = GetDistance(enemy.get()->GetPos(), stage_->GetPos());

		//�v���C���[�̕`��
		DrawRotaGraph(MAP_POS_X - distance.x, MAP_POS_Y + distance.z, IMAGE_EX_RATE, enemyAngle, mapEnemyImg_, true);
	}
}

void MiniMap::DrawItem(void)
{
	//�X�e�[�W����̑��΍��W�v�Z
	VECTOR distance = GetDistance(itemMng_->GetItem().get()->GetPos(), stage_->GetPos());

	//�v���C���[�̕`��
	DrawCircle(MAP_POS_X - distance.x, MAP_POS_Y + distance.z, 10.0 * IMAGE_EX_RATE, 0xffff00);
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
