#pragma once
#include <string>
#include<windows.h>

//#define DEBUG_SCREEN

class Application
{

public:
#ifdef DEBUG_SCREEN
	static constexpr int SCREEN_SIZE_X = 800;
	static constexpr int SCREEN_SIZE_Y = 600;
	// �X�N���[���T�C�Y

	//static constexpr int SCREEN_SIZE_X = 1920;
	//static constexpr int SCREEN_SIZE_Y = 1080;
#endif // DEBUG_SCREEN

	static constexpr int DEFA_SCREEN_SIZE_X = 1920;
	static constexpr int DEFA_SCREEN_SIZE_Y = 1080;

	static constexpr int SCREEN_SIZE_X = 800;
	static constexpr int SCREEN_SIZE_Y = 600;

	//FPS
	static constexpr int DEFAULT_FPS = 60;
	static constexpr float FRAME_RATE = 1000 / 60;

	// �f�[�^�p�X�֘A
	//-------------------------------------------
	static const std::string PATH_IMAGE;
	static const std::string PATH_MODEL;
	static const std::string PATH_EFFECT;
	static const std::string PATH_TEXT;
	static const std::string PATH_FONT;
	static const std::string PATH_JSON;
	static const std::string PATH_BGM;
	static const std::string PATH_SE;
	//-------------------------------------------

	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static Application& GetInstance(void);

	// ������
	void Init(void);

	// �Q�[�����[�v�̊J�n
	void Run(void);

	// ���\�[�X�̔j��
	void Destroy(void);

	// �����������^���s�̔���
	bool IsInitFail(void) const;

	// ��������^���s�̔���
	bool IsReleaseFail(void) const;

private:

	// �ÓI�C���X�^���X
	static Application* instance_;

	// ���������s
	bool isInitFail_;

	// ������s
	bool isReleaseFail_;

	//�G�t�F�N�V�A�̏�����
	void InitEffekseer(void);

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	Application(void);

	// �R�s�[�R���X�g���N�^�����l
	Application(const Application&);

	// �f�X�g���N�^�����l
	~Application(void) = default;

	//�t���[�����[�g�֘A
	//---------------------------------
	int currentFrame_;	//���݂̃t���[����ۑ�
	int lastFrame_;		//�Ō�Ɏ��s�����t���[����ۑ�

	int frameCnt_ = 0;				//�t���[���J�E���g�p
	int updateFrameRateTime_ = 0;	//�t���[�����[�g���X�V��������

	float frameRate_ = 0.f;			//�t���[�����[�g(�\���p)

	bool isDrawFrameRate_ = false;	//�t���[�����[�g�̕\���t���O(true:�\��)

	//�t���[�����[�g�v�Z
	void CalcFrameRate();

	//�t���[�����[�g�\��(�f�o�b�O�p)
	void DrawFrameRate();
};