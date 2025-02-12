#pragma once
#include <chrono>
#include<vector>
#include<memory>
#include"../../Application.h"
#include"../../Common/Fader.h"

class SceneBase;
class Fader;
class Camera;

class SceneManager
{

public:

	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		GAME,
		GAMECLEAR,
		GAMEOVER,
	};

	//�R���g���[���n��
	enum class CNTL
	{
		NONE,
		KEYBOARD,
		PAD
	};
	
	//�萔

	// �C���X�^���X�̐���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static SceneManager& GetInstance(void);

	void Init(void);
	void Init3D(void);
	void Update(void);
	void Draw(void);

	// ���\�[�X�̔j��
	void Destroy(void);

	// ��ԑJ��
	void ChangeScene(SCENE_ID nextId);

	// �V�[��ID�̎擾
	SCENE_ID GetSceneID(void);

	// �f���^�^�C���̎擾
	float GetDeltaTime(void) const;

	// �J�����̎擾
	std::shared_ptr<Camera> GetCamera(void) const;

private:
	// �ÓI�C���X�^���X
	static SceneManager* instance_;

	SCENE_ID sceneId_;				//���݂̃V�[�����
	SCENE_ID waitSceneId_;			//���̃V�[��

	// �t�F�[�h
	std::unique_ptr<Fader> fader_;

	// �e��V�[��
	SceneBase* scene_;

	// �J����
	std::shared_ptr<Camera> camera_;

	// �V�[���J�ڒ�����
	bool isSceneChanging_;

	// �f���^�^�C��
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;
	
	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SceneManager(void);
	// �R�s�[�R���X�g���N�^�����l
	SceneManager(const SceneManager&);
	// �f�X�g���N�^�����l
	~SceneManager(void) = default;

	// �f���^�^�C�������Z�b�g����
	void ResetDeltaTime(void);

	// �V�[���J��
	void DoChangeScene(SCENE_ID sceneId);

	// �t�F�[�h
	void Fade(void);
};