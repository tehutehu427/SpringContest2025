#include <DxLib.h>
#include"../Utility/AsoUtility.h"
#include"../Manager/Generic/InputManager.h"
#include "Player.h"

//�R���X�g���N�^
Player::Player()
{
	
}

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

	//�v���C���[�������Ă������
	direction_ == DIRECTION::NORTH;

	//�v���C���[�̔��a
	radius_ = SIZE / 2;

}

void Player::Update(void)
{
	auto& ins = InputManager::GetInstance();
	//�k�Ɉړ�
	if (direction_ == DIRECTION::NORTH)
	{
		trans_.pos.z++;
	}
	//��
	if (direction_ == DIRECTION::WEST)
	{
		trans_.pos.x++;
	}
	//��
	if (direction_ == DIRECTION::EAST )
	{
		trans_.pos.x--;
	}
	//��
	if (direction_ == DIRECTION:: SOUTH)
	{
		trans_.pos.z--;
	}


	
	if (ins.IsTrgDown(KEY_INPUT_A))
	{
		if (direction_ == DIRECTION::NORTH)
		{
			//�k�̏ꍇ���ɖ߂�
			direction_ = DIRECTION::WEST;
	    }
		else
		{
		 direction_ = static_cast <DIRECTION>(static_cast <int> (direction_) - 1);
		}

		//�J�����̕�����ς���@�@����]��
		Turn(-90.0f, AsoUtility::AXIS_Y);

	}
  //�E
	if (ins.IsTrgDown(KEY_INPUT_D))
	{

		if (direction_ == DIRECTION::NORTH)
		{
			//�k�̏ꍇ���ɖ߂�
			direction_ = DIRECTION::WEST;
		}
		else
		{
			direction_ = static_cast <DIRECTION>(static_cast <int> (direction_) + 1);
		}

		//�J�����̕�����ς���
		Turn(90.0f, AsoUtility::AXIS_Y);
	}
	//���
	if (ins.IsTrgDown(KEY_INPUT_S))
	{
		if (direction_ == DIRECTION::NORTH || direction_ == DIRECTION::EAST)
		{
			//�k�Ɠ������Ă�Ƃ�
			direction_ = static_cast <DIRECTION>(static_cast <int> (direction_) + 2);
		}
		else
		{
			//��Ɛ������Ă�Ƃ�
			direction_ = static_cast <DIRECTION>(static_cast <int> (direction_) - 2);
		}

		//�J�����̕�����ς���
		Turn(180.0f, AsoUtility::AXIS_Y);
	}
}

void Player::Draw(void)
{
}

void Player::Release(void)
{
}
