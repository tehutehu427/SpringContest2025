#include <chrono>
#include <DxLib.h>
#include<EffekseerForDXLib.h>
#include<cassert>

#include "../../Scene/SceneTitle.h"
#include "../../Scene/SceneGame.h"
#include "../../Scene/SceneGameOver.h"
#include "../../Scene/SceneGameClear.h"
#include "ResourceManager.h"
#include"../System/Collision.h"
#include"../Decoration/SoundManager.h"
#include"Camera.h"
#include "SceneManager.h"

SceneManager* SceneManager::instance_ = nullptr;

void SceneManager::CreateInstance()
{
	if (instance_ == nullptr){
		instance_ = new SceneManager();
	}
	instance_->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::Init(void)
{
	//�e�}�l�[�W���̐���
	//����̐���
	Collision::CreateInstance();
	SoundManager::CreateInstance();

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	fader_ = std::make_unique<Fader>();
	fader_->Init();

	// �J����
	camera_ = std::make_shared<Camera>();
	camera_->Init();

	scene_ = new SceneTitle();
	scene_->Init();

	isSceneChanging_ = false;

	// �f���^�^�C��
	preTime_ = std::chrono::system_clock::now();

	//3D�p�̏�����
	Init3D();

	// �����V�[���̐ݒ�
	DoChangeScene(SCENE_ID::TITLE);
}

void SceneManager::Init3D(void)
{

	// �w�i�F�ݒ�
	SetBackgroundColor(0, 0, 0);

	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(true);

	// �o�b�N�J�����O��L���ɂ���
	SetUseBackCulling(true);

	// ���C�g�̐ݒ�
	SetUseLighting(true);

	// ���C�g�̐ݒ�
	SetLightEnable(true);

	// ���ʂ���΂߉��Ɍ����������C�g
	//ChangeLightTypeDir({ 0.00f, -1.00f, 1.00f });

	// ���C�g�̐ݒ�
	//ChangeLightTypeDir({ 0.3f, -0.7f, 0.8f });

	// �t�H�O�ݒ�
	SetFogEnable(true);
	SetFogColor(5, 5, 5);
	SetFogStartEnd(10000.0f, 20000.0f);

}


void SceneManager::Update(void)
{

	if (scene_ == nullptr)return;

	// �f���^�^�C��
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	fader_->Update();
	if (isSceneChanging_){
		Fade();
	}
	else{
		scene_->Update();
	}

	// �J�����X�V
	camera_->Update();
}

void SceneManager::Draw(void)
{
	// �`���O���t�B�b�N�̈�̎w��
	// (�R�c�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(DX_SCREEN_BACK);

	//�t�����g�o�b�t�@�̉摜������
	ClearDrawScreen();

	// �J�����ݒ�
	camera_->SetBeforeDraw();

	//�Q�[�����e�`��
	// �`��
	scene_->Draw();

	// �Ó]�E���]
	fader_->Draw();

	////�t�����g�o�b�t�@�ɏ����o��
	//ScreenFlip();
}

void SceneManager::Destroy(void)
{

	scene_->Release();
	delete scene_;

	SoundManager::GetInstance().Destroy();

	delete instance_;
}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	// �t�F�[�h�������I����Ă���V�[����ς���ꍇ�����邽�߁A
	// �J�ڐ�V�[���������o�ϐ��ɕێ�
	waitSceneId_ = nextId;

	// �t�F�[�h�A�E�g(�Ó])���J�n����
	fader_->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;

}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
	//return 1.0f / 60.0f;
	return deltaTime_;
}

std::shared_ptr<Camera> SceneManager::GetCamera(void) const
{
	return camera_;
}

SceneManager::SceneManager(void)
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	scene_ = nullptr;
	fader_ = nullptr;

	isSceneChanging_ = false;
	// �f���^�^�C��
	deltaTime_ = 1.0f / 60.0f;	
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 1.0f / 60.0f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{
	auto& resM = ResourceManager::GetInstance();

	// ���\�[�X�̉��
	resM.Release();
	SoundManager::GetInstance().Release();

	// �V�[����ύX����
	sceneId_ = sceneId;

	// ���݂̃V�[�������
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
	}

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		scene_ = new SceneTitle();
		resM.InitTitle();
		break;		
		
	case SCENE_ID::GAME:
		scene_ = new SceneGame();
		resM.InitGame();
		break;

	case SCENE_ID::GAMEOVER:
		scene_ = new SceneGameOver();
		resM.InitGameOver();
		break;

	case SCENE_ID::GAMECLEAR:
		scene_ = new SceneGameClear();
		resM.InitGameClear();
		break;
	}

	scene_->Init();

	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;
}

void SceneManager::Fade(void)
{

	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		// ���]��
		if (fader_->IsEnd())
		{
			// ���]���I��������A�t�F�[�h�����I��
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		// �Ó]��
		if (fader_->IsEnd())
		{
			// ���S�ɈÓ]���Ă���V�[���J��
			DoChangeScene(waitSceneId_);
			// �Ó]���疾�]��
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}
}