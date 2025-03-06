#include <DxLib.h>
#include "EnemyManager.h"
#include"../../Object/Enemy.h"

EnemyManager* EnemyManager::instance_ = nullptr;

void EnemyManager::CreateInstance(void)
{
	if (instance_ == nullptr) {
		instance_ = new EnemyManager();
	}
	instance_->Init();

}

EnemyManager& EnemyManager::GetInstance(void)
{
	return *instance_;
}

EnemyManager::EnemyManager(void) {
	enemy_ = nullptr;
 }

void EnemyManager::Init(void)
{
	enemy_ = new Enemy();
	enemy_->Init();
}

void EnemyManager::Update(void)
{
	enemy_->Update();
}

void EnemyManager::Draw(void)
{
	enemy_->Draw();
}

void EnemyManager::Release(void)
{
	enemy_->Release();

	delete instance_;
}
