#include<DxLib.h>
#include"../Application.h"
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/System/Timer.h"
#include"../Manager/Generic/Camera.h"
#include"../Manager/System/Collision.h"
#include "../Object/MiniMap.h"
#include "../Object/Manager/ItemManager.h"
#include "../Object/Item.h"
#include "../Object/Manager/EnemyManager.h"
#include "../Object/Enemy.h"
#include "../Object/Player.h"
#include "../Object/Stage.h"
#include "SceneGame.h"

SceneGame::SceneGame()
{
}

void SceneGame::Init(void)
{
	//�J����
	auto camera = SceneManager::GetInstance().GetCamera();

	//�J�������Œ�ɐݒ�
	camera->ChangeMode(Camera::MODE::FOLLOW_PERSPECTIVE);

	//�X�e�[�W�̏�����
	stage_ = std::make_unique<Stage>();
	stage_->Init();

	//�v���C���[�̏�����
	player_ = std::make_unique<Player>();
	player_->Init();

	//�G�̏�����
	enmMng_ = std::make_unique<EnemyManager>();
	enmMng_->Init();

	//�A�C�e���̏�����
	itemMng_ = std::make_unique<ItemManager>();
	itemMng_->Init();

	//�A�C�e���̏�����
	miniMap_ = std::make_unique<MiniMap>(player_.get(), enmMng_.get(), itemMng_.get());
	miniMap_->Init();

	//�J�������v���C���[�ɒǏ]
	camera->SetFollow(&player_->GetTransform());
	camera->SetRot(player_->GetRot());
}

void SceneGame::Update(void)
{
	//�V�[���J��(�f�o�b�O)
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);

	//�X�e�[�W�̍X�V
	stage_->Update();

	//�v���C���[�̍X�V
	player_->Update();

	//�G�̍X�V
	enmMng_->Update();

	//�A�C�e���̍X�V
	itemMng_->Update();

	//�~�j�}�b�v�̍X�V
	miniMap_->Update();

	//�����蔻��
	Collision();
}

void SceneGame::Draw(void)
{
#ifdef SCENE_DEBUG

	//�f�o�b�O
	DrawDebug();

#endif // SCENE_DEBUG

	//�X�e�[�W�̕`��
	stage_->Draw();

	//�v���C���[�̕`��
	player_->Draw();

	//�G�̕`��
	enmMng_->Draw();

	//�A�C�e���̕`��
	itemMng_->Draw();

	//�~�j�}�b�v�̕`��
	miniMap_->Draw();
}

void SceneGame::Release(void)
{
	//�~�j�}�b�v�̉��
	miniMap_->Release();

	//�A�C�e���̉��
	itemMng_->Release();

	//�G�̉��
	enmMng_->Release();

	//�v���C���[�̉��
	player_->Release();
}

void SceneGame::DrawDebug(void)
{
	//�f�o�b�O
	//DrawBox(0 + 30, 0 + 30, Application::SCREEN_SIZE_X - 30, Application::SCREEN_SIZE_Y - 30, 0xff0000, true);
	DrawString(0, 0, "SceneGame", 0xffffff);
}

void SceneGame::Collision(void)
{
	auto& col = Collision::GetInstance();

	//�v���C���[�ƓG�̓����蔻��
	//for(auto enm:enmMng_->)
	
	//if(col.IsHitUnitStageObject(stage_->GetModelId(),player_->GetPos(),Player::SIZE))
}
