#include <DxLib.h>
#include<EffekseerForDXLib.h>
#include "Manager/Generic/ResourceManager.h"
#include "Manager/Generic/InputManager.h"
#include "Manager/Generic/SceneManager.h"
#include "Application.h"

Application* Application::instance_ = nullptr;

//�t�@�C���w��p�X
const std::string Application::PATH_IMAGE = "Data/Image/";
const std::string Application::PATH_MODEL = "Data/Model/";
const std::string Application::PATH_EFFECT = "Data/Effect/";
const std::string Application::PATH_TEXT = "Data/Text/";
const std::string Application::PATH_FONT = "Data/Font/";
const std::string Application::PATH_JSON = "Data/Json/";
const std::string Application::PATH_BGM = "Data/Sound/BGM/";
const std::string Application::PATH_SE = "Data/Sound/SE/";

void Application::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}
	instance_->Init();
}

Application& Application::GetInstance(void)
{
	return *instance_;
}

void Application::Init(void)
{
	// �A�v���P�[�V�����̏����ݒ�
	SetWindowText("Main");
	// �E�B���h�E�T�C�Y
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);
	// ��A�N�e�B�u��Ԃł����삷��
	SetAlwaysRunFlag(TRUE);			

	// DxLib�̏�����
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		isInitFail_ = true;
		return;
	}

	//�G�t�F�N�V�A�̏�����
	InitEffekseer();

	// �L�[���䏉����
	SetUseDirectInputFlag(true);
	InputManager::CreateInstance();

	// ���\�[�X�Ǘ�������
	ResourceManager::CreateInstance();

	// �V�[���Ǘ�������
	SceneManager::CreateInstance();

	//FPS�p������
	currentFrame_ = 0;
	lastFrame_ = 0;
}

void Application::Run(void)
{
	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();

	MSG msg;

	// �Q�[�����[�v
	while (ProcessMessage() == 0)
	{
		//���b�Z�[�W���[�v
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Sleep(1);	//�V�X�e���ɏ�����Ԃ�
		currentFrame_ = GetNowCount();	//���݂̃t���[�������l��

		//���݂̎������A�O��̃t���[�������
		//1/60�b�o�߂��Ă����珈�������s����
		if (currentFrame_ - lastFrame_ >= FRAME_RATE)
		{
			//�t���[�����s���̎��Ԃ��X�V
			lastFrame_ = currentFrame_;

			//�t���[�����̃J�E���g
			frameCnt_++;

			//ESCAPE�L�[�������ꂽ��I��
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				return;
			}

			//�X�V����
			inputManager.Update();
			sceneManager.Update();

			//�`�揈��
			sceneManager.Draw();

			//�t���[�����[�g�v�Z
			CalcFrameRate();

			//�t���[�����[�g�̕\��(�f�o�b�O)
			DrawFrameRate();

			//�t�����g�o�b�t�@�ɏ����o��
			ScreenFlip();

		}
	}
}

void Application::Destroy(void)
{

	InputManager::GetInstance().Destroy();
	ResourceManager::GetInstance().Destroy();
	SceneManager::GetInstance().Destroy();
	
	// Effekseer���I������B
	Effkseer_End();

	// DxLib�I��
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}

	delete instance_;

}

bool Application::IsInitFail(void) const
{
	return isInitFail_;
}

bool Application::IsReleaseFail(void) const
{
	return isReleaseFail_;
}

void Application::InitEffekseer(void)
{
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
	}
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

}

Application::Application(void)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
}

void Application::CalcFrameRate()
{
	//�O��̃t���[�����[�g�X�V����̌o�ߎ��Ԃ����߂�
	int nDifTime = currentFrame_ - updateFrameRateTime_;

	//�O��̃t���[�����[�g���X�V����
	//1�b�ȏ�o�߂��Ă�����t���[�����[�g���X�V����
	if (nDifTime > 1000)
	{
		//�t���[���񐔂�1�~���b�ɍ��킹��
		//�����܂ŏo�����̂�float�ɃL���X�g
		float fFrameCnt = (float)(frameCnt_ * 1000);

		//�t���[�����[�g�����߂�
		//���z�ʂ�Ȃ� 60000 / 1000 �� 60 �ɂȂ�
		frameRate_ = fFrameCnt / nDifTime;

		//�t���[���J�E���g���N���A
		frameCnt_ = 0;

		//�t���[�����[�g�X�V���Ԃ��X�V
		updateFrameRateTime_ = currentFrame_;
	}
}

void Application::DrawFrameRate()
{
	int fontHandle;
	int fontSize = 20;
	int fontTickness = 8;

	fontHandle = CreateFontToHandle(NULL, fontSize, fontTickness, NULL);

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_TAB) && !isDrawFrameRate_)
	{
		isDrawFrameRate_ = true;
	}
	else if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_TAB) && isDrawFrameRate_)
	{
		isDrawFrameRate_ = false;
	}

	if (isDrawFrameRate_)
	{
		DrawFormatStringToHandle(SCREEN_SIZE_X - 110, 2, GetColor(255, 255, 30), fontHandle, "FPS[%.2f]", frameRate_);
	}

	DeleteFontToHandle(fontHandle);
}
