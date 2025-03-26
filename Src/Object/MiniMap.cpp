#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"Player.h"
#include"Manager/EnemyManager.h"
#include"Manager/ItemManager.h"
#include "MiniMap.h"

MiniMap::MiniMap(Player* _player, EnemyManager* _eneMng, ItemManager* _itemMng)
	: player_(_player), eneMng_(_eneMng), itemMng_(_itemMng)
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
	//�v���C���[
	mapPlayerImg_ = res.Load(ResourceManager::SRC::MAP_PLAYER).handleId_;
}

void MiniMap::Update(void)
{
}

void MiniMap::Draw(void)
{
	//�g���̕`��
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, MAP_EX_RATE, 0.0, mapGroundImg_,true);

	//�v���C���[�`��
	DrawPlayer();
	
	//�g�̕`��
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, MAP_EX_RATE, 0.0, mapFrameImg_, true);
}

void MiniMap::Release(void)
{
}

void MiniMap::DrawPlayer(void)
{
	//�v���C���[�̊p�x(Y��)
	double playerAngle = player_->GetTransform().quaRot.ToEuler().y;

	//�v���C���[�̕`��
	DrawRotaGraph(MAP_POS_X, MAP_POS_Y, PLAYER_EX_RATE, playerAngle, mapPlayerImg_, true);
}

void MiniMap::DrawEnemy(void)
{
}

void MiniMap::DrawItem(void)
{
}

void MiniMap::DrawVision(void)
{
}
