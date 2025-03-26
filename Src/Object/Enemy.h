#pragma once
#include <DxLib.h>

#include "UnitBase.h"

class Enemy : public UnitBase
{
public:
	static constexpr float ENEMY_SIZE = 50.0f;	//�G�̑傫��(���a)

	static constexpr float STAGE_SIZE = 1700.0f;	//�X�e�[�W�̑傫��(�����`1�ӂ̒���)


	static constexpr int MOVE_POINT = 4;		//�G�̈ړ��|�C���g

	enum class MOVEDIR
	{
		NONE,

		UP,
		LEFT,
		RIGHT,
		DOWN,

	};
	enum class MOVECLOCKDIR 
	{
		NONE,

		CLOCKWISE,
		COUNTERCLOCKWISE,
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
	
	void SetMovePoint(const float& squarSize);
	void SetMoveSpeed(const float& moveSpeed);
	MOVECLOCKDIR SetMoveClockDir(const MOVECLOCKDIR& moveClockDir);
	MOVEDIR SetMoveDir(const MOVEDIR& moveDir);

	void SetDebugDrawPos(const int& pos);
private:

	void EnemyMove(void);
	void Clockwise(void);
	void CounterClockwise(void);

	//�ړ��X�s�[�h
	float moveSpeed_;

	//�ړ�����
	MOVEDIR moveDir_;

	//�ړ�����(�E�A�����)
	MOVECLOCKDIR moveClockDir_;

	//�ړ��|�C���g
	VECTOR movePointPos_[MOVE_POINT];

	int DebugDrawPos;

};
