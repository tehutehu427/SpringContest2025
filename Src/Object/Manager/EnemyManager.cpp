#include <DxLib.h>
#include "EnemyManager.h"
#include"../Enemy.h"
#include"../../Manager/System/Collision.h"
#include"../../Utility/AsoUtility.h"
//EnemyManager* EnemyManager::instance_ = nullptr;
//
//void EnemyManager::CreateInstance(void)
//{
//	if (instance_ == nullptr) {
//		instance_ = new EnemyManager();
//	}
//	instance_->Init();
//
//}
//
//EnemyManager& EnemyManager::GetInstance(void)
//{
//	return *instance_;
//}

EnemyManager::EnemyManager(void) {
 }

void EnemyManager::Init(void)
{
	//�G�̐���
	CreateEnemy();
}

void EnemyManager::Update(void)
{
	//for (int i = 0; i < ENEMY_NUM; i++) {
	//	enemy_[i]->Update();
	//}

	//�G�̍X�V
	size_t size = enemys_.size();
	for (int i = 0; i < size; i++) {
		enemys_[i]->Update();
	}
}

void EnemyManager::Draw(void)
{
	//for (int i = 0; i < ENEMY_NUM; i++) {
	//	enemy_[i]->Draw();
	//}

	for (int i = 0; i < ENEMY_NUM; i++) {
		enemys_[0]->SetDebugDrawPos(32);
		enemys_[1]->SetDebugDrawPos(48);
		enemys_[i]->Draw();

	}
}

void EnemyManager::Release(void)
{
	EraseEnemy();
	//delete instance_;
}

std::shared_ptr<Enemy> EnemyManager::EnemyClass(void)
{
	size_t size = enemys_.size();
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
	enemy->Init();
	enemys_.push_back(enemy);
	return enemy;
}

void EnemyManager::CreateEnemy(void)
{
	//for (int i = 0; i < ENEMY_NUM; i++) {
	//	enemy_[i] = nullptr;
	//	enemy_[i] = new Enemy();
	//	enemy_[i]->Init();

	//	//�����̓G
	//	enemy_[0]->SetPos({0.0f,100.0f,0.0f});
	//	enemy_[0]->SetMovePoint(100);
	//	enemy_[0]->SetMoveSpeed(1.0f);
	//	enemy_[0]->SetMoveClockDir(Enemy::MOVECLOCKDIR::CLOCKWISE);
	//	enemy_[0]->SetMoveDir(Enemy::MOVEDIR::RIGHT);	//���v���

	//	//�O���̓G
	//	//enemy_[1]->SetPos({ 0.0f,0.0f,0.0f });
	//	//enemy_[1]->SetMovePoint(200);
	//	//enemy_[1]->SetMoveSpeed(20.0f);
	//	//enemy_[1]->SetMoveClockDir(Enemy::MOVECLOCKDIR::COUNTERCLOCKWISE);
	//	//enemy_[1]->SetMoveDir(Enemy::MOVEDIR::DOWN);	//�����v���
	//}
	
	std::shared_ptr<Enemy> enemy = nullptr;
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy = EnemyClass();
		if (i == 0) {
			enemys_[0]->SetPos({ -700.0f, 50.0f, 670.0f });
		enemys_[0]->SetMovePoint(1400);					//�����`��ӂ̒���
		enemys_[0]->SetMoveSpeed(ENEMY1_MOVE_SPEED);		//�ړ��X�s�[�h
		enemys_[0]->SetMoveClockDir(Enemy::MOVECLOCKDIR::CLOCKWISE);
		enemys_[0]->SetMoveDir(Enemy::MOVEDIR::RIGHT);	//���v���
		}

		if (i == 1) {
		enemys_[1]->SetPos({ -280.0f,50.0f,268.0f });
		enemys_[1]->SetMovePoint(1400 * 0.4f);			//�����`��ӂ̒���
		enemys_[1]->SetMoveSpeed(ENEMY2_MOVE_SPEED);	//�ړ��X�s�[�h
		enemys_[1]->SetMoveClockDir(Enemy::MOVECLOCKDIR::COUNTERCLOCKWISE);
		enemys_[1]->SetMoveDir(Enemy::MOVEDIR::DOWN);	//�����v���
		}
	}
}

void EnemyManager::EraseEnemy(void)
{
	//for (int i = 0; i < ENEMY_NUM; i++) {
	//	enemy_[i]->Release();
	//}
	
	size_t size = enemys_.size();
	for (int i = (int)size; i > 0; i--) {
		enemys_[i - 1]->Release();
	}
	enemys_.clear();
}

bool EnemyManager::CollisionStage(const int& _stageModelId)
{
	auto& col = Collision::GetInstance();

	for (auto& enemy : enemys_)
	{
		if (col.IsHitUnitStageObject(_stageModelId, enemy->GetPos(), enemy->GetRadius()))
		{
			//���������̂ňړ��O�ɖ߂�
			//enemy->SetPos(enemy->GetPrePos());

			return true;
		}
	}

	return false;
}