#pragma once
#include "UnitBase.h"
class Enemy : public UnitBase
{
	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy()override;

	//������
	void Init(void)override;
	//�X�V
	void Update(void)override;
	//�`��
	void Draw(void)override;
	//���
	void Release(void)override;
};

