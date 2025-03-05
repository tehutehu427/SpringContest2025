#include<DxLib.h>
#include"../Application.h"
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/System/Timer.h"
#include "../Object/ItemManager.h"
#include "../Object/Item.h"
#include "../Object/Stage.h"
#include "SceneGame.h"

SceneGame::SceneGame()
{
}

void SceneGame::Init(void)
{
	//�X�e�[�W�̏�����
	stage_ = std::make_unique<Stage>();
	stage_->Init();

	//�A�C�e���̏�����
	itemMng_ = std::make_unique<ItemManager>();
	itemMng_->Init();
}

void SceneGame::Update(void)
{
	//�V�[���J��(�f�o�b�O)
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);

	//�X�e�[�W�̍X�V
	stage_->Update();

	//�A�C�e���̍X�V
	itemMng_->Update();
}

void SceneGame::Draw(void)
{
#ifdef SCENE_DEBUG

	//�f�o�b�O
	DrawDebug();

#endif // SCENE_DEBUG

	//�X�e�[�W�̕`��
	stage_->Draw();

	//�A�C�e���̕`��
	itemMng_->Draw();
}

void SceneGame::Release(void)
{
	//�A�C�e���̉��
	itemMng_->Release();
}

void SceneGame::DrawDebug(void)
{
	//�f�o�b�O
	DrawBox(0 + 30, 0 + 30, Application::SCREEN_SIZE_X - 30, Application::SCREEN_SIZE_Y - 30, 0xff0000, true);
	DrawString(0, 0, "SceneGame", 0xffffff);
}
