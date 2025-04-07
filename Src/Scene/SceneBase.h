#pragma once

class SceneBase
{
	//�f�o�b�O�p
//#define SCENE_DEBUG	

public:

	// �R���X�g���N�^
	SceneBase(void) = default;

	// �f�X�g���N�^
	virtual ~SceneBase(void) = 0;

	// ������
	virtual void Init(void) = 0;
	// �X�V
	virtual void Update(void) = 0;
	// �`��
	virtual void Draw(void) = 0;
	// ���
	virtual void Release(void) = 0;
};

