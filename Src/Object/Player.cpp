#include <DxLib.h>
#include"../Utility/AsoUtility.h"
#include "Player.h"

Player::~Player()
{
}

void Player::Init(void)
{
	//������
	trans_.pos = {0.0f,0.0f,0.0f};
	trans_.pos = AsoUtility::VECTOR_ZERO;
	//�J��������������
	axis_ = { 0.0f,0.0f,0.0f };

	direction_ = DIRECTION::FRONT;
}

void Player::Update(void)
{

	//�O�Ɉړ�
	if (direction_ == DIRECTION::FRONT)
	{
		trans_.pos.z++;
	}
	//��
	if (direction_ == DIRECTION::LEFT)
	{
		trans_.pos.x--;
	}
	//�E
	if (direction_ == DIRECTION::RIGHT)
	{
		trans_.pos.x++;
	}
	//���
	if (direction_ == DIRECTION::BACK)
	{
		trans_.pos.z--;
	}


	//�ړ�
	 //�O
	if (CheckHitKey(KEY_INPUT_W))
	{
		//FRONT�̏ꍇ
		if (direction_ == DIRECTION::FRONT)
		{
			Turn(00.0f, axis_);
			trans_.pos.z ++;
		}
		//LEFT�̏ꍇ
		if (direction_ == DIRECTION::LEFT)
		{
			Turn(-90.0f, axis_);
			trans_.pos.x--;
		}
		//RIGHT�̏ꍇ
		if (direction_ == DIRECTION::RIGHT)
		{
			Turn(90.0f, axis_);
			trans_.pos.x++;
		}
		//BACK�̏ꍇ
		if (direction_ == DIRECTION::BACK)
		{
			Turn(180.0f, axis_);
			trans_.pos.z--;
		}

		//������FRONT�ύX
		direction_ == DIRECTION::FRONT;
	}
	//��
	if (CheckHitKey(KEY_INPUT_A))
	{
	
		
		
		//������LEFT�ɕύX
		direction_ == DIRECTION::LEFT;
	}
	//�E
	if (CheckHitKey(KEY_INPUT_D))
	{
		trans_.pos.x += 1;
	}
	//���
	if (CheckHitKey(KEY_INPUT_S))
	{
		trans_.pos.z += 1;
	}
}

void Player::Draw(void)
{
}

void Player::Release(void)
{
}
