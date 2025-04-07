#include<DxLib.h>
#include"../Application.h"
#include"../Common/Easing.h"
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Manager/Decoration/SoundManager.h"
#include"../Manager/System/Timer.h"
#include"../Manager/Generic/Camera.h"
#include"../Manager/System/Collision.h"
#include"../Object/SkyDome.h"
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
	//camera->ChangeMode(Camera::MODE::FREE);

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
	miniMap_ = std::make_unique<MiniMap>(player_.get(), enmMng_.get(), itemMng_.get(),stage_.get());
	miniMap_->Init();

	//�X�J�C�h�[���̏�����
	skyDome_ = std::make_unique<SkyDome>(player_->GetTransform());
	skyDome_->Init();

	//�J�������v���C���[�ɒǏ]
	camera->SetFollow(&player_->GetTransform());

	scrollBannerPos_ = Application::SCREEN_SIZE_X;
	scrollBannerTime_ = 0.0f;

	//�T�E���h
	auto& sound = SoundManager::GetInstance();
	auto& res = ResourceManager::GetInstance();

	sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_GAME, res.Load(ResourceManager::SRC::BGM_GAME).handleId_);
	sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_GET, res.Load(ResourceManager::SRC::SE_GET).handleId_);
	sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_DAMAGE, res.Load(ResourceManager::SRC::SE_DAMAGE).handleId_);
	sound.AdjustVolume(SoundManager::SOUND::BGM_GAME, 40);
	sound.AdjustVolume(SoundManager::SOUND::SE_GET, 50);
	sound.AdjustVolume(SoundManager::SOUND::SE_DAMAGE, 50);

	//����BGM
	sound.Play(SoundManager::SOUND::BGM_GAME);
}

void SceneGame::Update(void)
{
	//�o�i�[�����ꒆ��
	if (ScrollBanner())return;

	//�X�J�C�h�[���̍X�V
	skyDome_->Update();

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

	//�Q�[���N���A����
	GameClear();

	//�Q�[���I�[�o�[����
	GameOver();
}

void SceneGame::Draw(void)
{
#ifdef SCENE_DEBUG

	//�f�o�b�O
	DrawDebug();

#endif // SCENE_DEBUG

	//�X�J�C�h�[���̕`��
	skyDome_->Draw();

	//�X�e�[�W�̕`��
	stage_->Draw();

	//�G�̕`��
	enmMng_->Draw();

	//�A�C�e���̕`��
	itemMng_->Draw();

	//�v���C���[�̕`��
	player_->Draw();

	//�~�j�}�b�v�̕`��
	miniMap_->Draw();

	//�����o�i�[�̕`��
	int font = CreateFontToHandle(NULL, 50, 10, DX_FONTTYPE_EDGE);

	DrawStringFToHandle(scrollBannerPos_, Application::SCREEN_SIZE_Y / 2, "�G������A��΂��W�߂�I�I", 0xffffff, font);

	DeleteFontToHandle(font);
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

bool SceneGame::ScrollBanner(void)
{
	//����Ă��鎞��
	if (scrollBannerTime_ < SCROLL_BANNER_TIME)
	{
		scrollBannerTime_++;
		scrollBannerPos_ = SineOut(scrollBannerTime_
			, SCROLL_BANNER_TIME
			, Application::SCREEN_SIZE_X
			, -SCROLL_BANNER_SIZE_X *1.5);

		return true;
	}

	return false;
}

void SceneGame::Collision(void)
{
	CollisionPlayer();
	CollisionEnemy();
}

void SceneGame::CollisionPlayer(void)
{
	//�T�E���h
	auto& sound = SoundManager::GetInstance();

	//�R���C�_
	auto& col = Collision::GetInstance();

	player_->CollisionStage(stage_->GetModelId());

	for (auto& enemy : enmMng_->GetEnemys())
	{
		//�v���C���[�ƓG�̓����蔻��
		if (col.IsHitSpheres(player_->GetPos(), player_->GetRadius(), enemy->GetPos(), enemy->GetRadius()))
		{
			//�U�����ĂȂ��Ȃ�
			if (!enemy->IsAtk())
			{
				//�̗͂�������
				player_->SubHp();

				//�čU�����ԃ��Z�b�g
				enemy->Hit();

				//�_���[�W��
				sound.Play(SoundManager::SOUND::SE_DAMAGE);
			}
		}
	}

	//�v���C���[�ƃA�C�e���̓����蔻��
	if (col.IsHitSpheres(player_->GetPos(), player_->GetRadius(), itemMng_->GetItem()->GetPos(), itemMng_->GetItem()->GetRadius()))
	{
		//�A�C�e���擾���𑝉�
		player_->AddItemNum();

		//�A�C�e���̍ďo��
		itemMng_->CreateItem();

		//�擾��
		sound.Play(SoundManager::SOUND::SE_GET);
	}
}

void SceneGame::CollisionEnemy(void)
{
	//�R���C�_
	auto& col = Collision::GetInstance();

	enmMng_->CollisionStage(stage_->GetModelId());

	for (auto& enemy : enmMng_->GetEnemys())
	{

	}
}

void SceneGame::GameClear(void)
{
	//�T�E���h
	auto& sound = SoundManager::GetInstance();

	//�Q�[���N���A����
	if (player_->GetItemNum() >= Player::ITEM_NUM)
	{
		//BGM��~
		sound.Stop(SoundManager::SOUND::BGM_GAME);

		//�Q�[���N���A�ɑJ��
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
	}
}

void SceneGame::GameOver(void)
{
	//�T�E���h
	auto& sound = SoundManager::GetInstance();

	//�Q�[���I�[�o�[����
	if (!player_->IsAlive())
	{
		//BGM��~
		sound.Stop(SoundManager::SOUND::BGM_GAME);

		//�Q�[���I�[�o�[�ɑJ��
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);
	}
}
