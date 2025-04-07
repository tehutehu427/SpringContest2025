#pragma once
#include <map>
#include <string>
#include "Resource.h"

class ResourceManager
{

public:

	// ���\�[�X��
	enum class SRC
	{
		//************************************************************
		// �����ɕۑ����Ă��������摜�⃂�f���A�����Ȃǂ̖��O���L��
		//************************************************************
		
		/*��*/
		TITLE_LOGO,				//�^�C�g�����S
		GAMEOVER_LOGO,			//�Q�[���I�[�o�[
		GAMECLEAR_LOGO,			//�Q�[���N���A

		SKY_DOME,				//�X�J�C�h�[��
		STAGE,					//�X�e�[�W���f��
		GEM,					//��΃��f��

		//�G�֌W
		ENEMY,					//�G���f��

		//�~�j�}�b�v�֌W
		MAP_FRAME,				//�~�j�}�b�v�g
		MAP_GROUND,				//�~�j�}�b�v�g��
		MAP_MASK,				//�~�j�}�b�v�}�X�N�p
		MAP_IMAGE,				//�~�j�}�b�v�摜
		MAP_PLAYER,				//�~�j�}�b�v�p�v���C���[
		MAP_ENEMY,				//�~�j�}�b�v�p�G

		//�T�E���h
		BGM_TITLE,				//�^�C�g��BGM
		BGM_GAME,				//�Q�[��BGM
		BGM_GAMEOVER,			//�Q�[���I�[�o�[BGM
		BGM_GAMECLEAR,			//�Q�[���N���ABGM

		SE_PUSH,				//���艹
		SE_DAMAGE,				//�_���[�W��
		SE_GET,					//�擾��
	};

	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static ResourceManager& GetInstance(void);

	// ������
	void Init(void);
	//�^�C�g���Ŏg�����\�[�X������
	void InitTitle(void);
	//�Q�[���Ŏg�����\�[�X������
	void InitGame(void);
	//�Q�[���I�[�o�[�Ŏg�����\�[�X������
	void InitGameOver(void);
	//�Q�[���N���A�Ŏg�����\�[�X������
	void InitGameClear(void);

	//�v���C���[���g�����\�[�X
	void ResourcePlayer(void);
	//�G���g�����\�[�X
	void ResourceEnemy(void);

	// ���(�V�[���ؑ֎��Ɉ�U���)
	void Release(void);

	// ���\�[�X�̊��S�j��
	void Destroy(void);

	// ���\�[�X�̃��[�h
	Resource Load(SRC src);

	// ���\�[�X�̕������[�h(���f���p)
	int LoadModelDuplicate(SRC src);

private:

	// �ÓI�C���X�^���X
	static ResourceManager* instance_;

	// ���\�[�X�Ǘ��̑Ώ�
	std::map<SRC, Resource> resourcesMap_;

	// �ǂݍ��ݍς݃��\�[�X
	std::map<SRC, Resource*> loadedMap_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	ResourceManager(void);

	// �f�X�g���N�^�����l
	~ResourceManager(void) = default;

	// �������[�h
	Resource* _Load(SRC src);

};

