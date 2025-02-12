#pragma once

#include"Common/Transform.h"

class UnitBase
{
public:

	//***********************************************
	//�����o�֐�
	//***********************************************

	//�R���X�g���N�^
	UnitBase() = default;
	//�f�X�g���N�^
	virtual ~UnitBase() = 0;

	//������
	virtual void Init(void) = 0;
	//�X�V
	virtual void Update(void) = 0;
	//�`��
	virtual void Draw(void) = 0;
	//���
	virtual void Release(void) = 0;

protected:

	//***********************************************
	//�����o�ϐ�
	//***********************************************

	//���f���̏��
	Transform trans_;

	//
};

