#pragma once
#include "UnitBase.h"
class Player : public UnitBase
{
public:
	//�R���X�g���N�^
	Player() = default;
	//�f�X�g���N�^
	~Player()override;

	//������
	void Init(void)override;
	//�X�V
	void Update(void)override;
	//�`��
	void Draw(void)override;
	//���
	void Release(void)override;
};

