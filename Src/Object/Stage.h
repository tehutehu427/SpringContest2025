#pragma once

#include"Common/Transform.h"

class Stage
{
public:
	//***********************************************
	//�����o�֐�
	//***********************************************

	//�R���X�g���N�^
	Stage();
	//�f�X�g���N�^
	~Stage();

	//������
	void Init(void);
	//�X�V
	void Update(void);
	//�`��
	void Draw(void);
	//���
	void Release(void);

private:
	//***********************************************
	//�����o�ϐ�
	//***********************************************

	//���f���̏��
	Transform trans_;
};