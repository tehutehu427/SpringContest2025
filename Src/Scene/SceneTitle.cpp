#include<DxLib.h>
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/Camera.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/Decoration/SoundManager.h"
#include"../DrawUI/titleUiDraw.h"
#include"../Object/Grid.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
	logo_ = -1;
	grid_ = nullptr;
}

void SceneTitle::Init(void)
{
	//�J�����ݒ�
	auto camera = SceneManager::GetInstance().GetCamera();
	camera->ChangeMode(Camera::MODE::FREE);

	//�^�C�g�����S
	logo_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE_LOGO).handleId_;

	//�O���b�h��
	grid_ = new Grid();
	grid_->Init();

	//UI
	ui_ = std::make_unique<titleUi>();
	ui_->AddCharactor("Space�������ĊJ�n");

	//�T�E���h
	auto& sound = SoundManager::GetInstance();
	auto& res = ResourceManager::GetInstance();

	sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_TITLE, res.Load(ResourceManager::SRC::BGM_TITLE).handleId_);
	sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_PUSH, res.Load(ResourceManager::SRC::SE_PUSH).handleId_);
	sound.AdjustVolume(SoundManager::SOUND::BGM_TITLE, 40);
	sound.AdjustVolume(SoundManager::SOUND::SE_PUSH, 50);

	//����BGM
	sound.Play(SoundManager::SOUND::BGM_TITLE);
}

void SceneTitle::Update(void)
{
	auto& sound = SoundManager::GetInstance();

	//�V�[���J��(�f�o�b�O)
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		//���艹
		sound.Play(SoundManager::SOUND::SE_PUSH);

		//BGM��~
		sound.Stop(SoundManager::SOUND::BGM_TITLE);

		//�V�[���J��
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		
		//�����I��
		return;
	}

	//�_��
	ui_->FontSettings();
}

void SceneTitle::Draw(void)
{
#ifdef SCENE_DEBUG

	//�f�o�b�O
	DrawDebug();

	//�O���b�h��
	grid_->Draw();

#endif // SCENE_DEBUG

	//�^�C�g�����S
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0, 0.0, logo_, true);

	int font = CreateFontToHandle(NULL, 10, 10);

	//�B���v�f
	DrawStringFToHandle(0.0f, 0.0f, "�����T���Ă��ꂽ�l:�v���Ӑl��", 0x222222, font);

	DeleteFontToHandle(font);

	//UI
	ui_->Draw();
}

void SceneTitle::Release(void)
{
	grid_->Release();
	delete grid_;
	grid_ = nullptr;
}

void SceneTitle::DrawDebug(void)
{
	//�f�o�b�O
	//DrawBox(0 + 30, 0 + 30, Application::SCREEN_SIZE_X - 30, Application::SCREEN_SIZE_Y - 30, 0xffffff, true);
	DrawString(0, 0, "SceneTitle", 0xffffff);
}
