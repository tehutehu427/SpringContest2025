#include<DxLib.h>
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/Decoration/SoundManager.h"
#include"../DrawUI/titleUiDraw.h"
#include "SceneGameClear.h"

SceneGameClear::SceneGameClear()
{
}

void SceneGameClear::Init(void)
{
	//UI
	ui_ = std::make_unique<titleUi>();
	ui_->AddCharactor("Space�������ă^�C�g���ɖ߂�");

	//�Q�[���I�[�o�[���S
	logo_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::GAMECLEAR_LOGO).handleId_;

	//�T�E���h
	auto& sound = SoundManager::GetInstance();
	auto& res = ResourceManager::GetInstance();

	sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_GAMECLEAR, res.Load(ResourceManager::SRC::BGM_GAMECLEAR).handleId_);
	sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_PUSH, res.Load(ResourceManager::SRC::SE_PUSH).handleId_);
	sound.AdjustVolume(SoundManager::SOUND::BGM_GAMECLEAR, 40);
	sound.AdjustVolume(SoundManager::SOUND::SE_PUSH, 50);

	//����BGM
	sound.Play(SoundManager::SOUND::BGM_GAMECLEAR);
}

void SceneGameClear::Update(void)
{
	auto& sound = SoundManager::GetInstance();

	//�V�[���J��(�f�o�b�O)
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		//���艹
		sound.Play(SoundManager::SOUND::SE_PUSH);

		//BGM��~
		sound.Stop(SoundManager::SOUND::BGM_GAMECLEAR);

		//�V�[���J��
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);

		//�����I��
		return;
	}

	//�_��
	ui_->FontSettings();
}

void SceneGameClear::Draw(void)
{
#ifdef SCENE_DEBUG

	//�f�o�b�O
	DrawDebug();

#endif // SCENE_DEBUG

	//�Q�[���N���A���S
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0, 0.0, logo_, true);

	//UI
	ui_->Draw();
}

void SceneGameClear::Release(void)
{
}

void SceneGameClear::DrawDebug(void)
{
	//�f�o�b�O
	DrawBox(0 + 30, 0 + 30, Application::SCREEN_SIZE_X - 30, Application::SCREEN_SIZE_Y - 30, 0x00ff00, true);
	DrawString(0, 0, "SceneGameClear", 0xffffff);
}
