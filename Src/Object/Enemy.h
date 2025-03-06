#pragma once
#include <DxLib.h>

#include "UnitBase.h"

class Enemy : public UnitBase
{
public:
	static constexpr float ENEMY_SIZE = 50.0f;	//�G�̑傫��(���a)

	static constexpr float STAGE_SIZE = 1700.0f;	//�X�e�[�W�̑傫��(�����`1�ӂ̒���)

	static constexpr float MOVE_SPEED = 10.0f;	//�ړ����x

	enum class MOVEDIR
	{
		NONE,

		UP,
		LEFT,
		RIGHT,
		DOWN,

	};

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

	//���W�擾
	//VECTOR GetPos(void) const;

	void SetPos(const VECTOR& pos);


private:

	//�ړ�����
	MOVEDIR moveDir_;


	//�ړ���
	float moveSpeed_;


};
