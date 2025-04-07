#include <DxLib.h>
#include"../Utility/AsoUtility.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/System/Collision.h"
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
	trans_.pos = { 0.0f,100.0f,-750.0f };
	prePos_ = trans_.pos;
	//�J��������������
	axis_ = { 0.0f,0.0f,0.0f };

	//�v���C���[�������Ă������
	direction_ == DIRECTION::NORTH;

	//�v���C���[�̔��a
	radius_ = RADIUS;

	speed_ = SPEED;
	prePos_ = trans_.pos;
	itemNum_ = 0;
	hp_ = HP_MAX;

}

void Player::Update(void)
{
	auto& ins = InputManager::GetInstance();

	//�ړ��O���W�ۑ�
	prePos_ = trans_.pos;

	//�k�Ɉړ�
	if (direction_ == DIRECTION::NORTH)
	{
		trans_.pos.z += speed_;
	}
	//��
	if (direction_ == DIRECTION::WEST)
	{
		trans_.pos.x -= speed_;
	}
	//��
	if (direction_ == DIRECTION::EAST )
	{
		trans_.pos.x += speed_;
	}
	//��
	if (direction_ == DIRECTION:: SOUTH)
	{
		trans_.pos.z -= speed_;
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

		if (direction_ == DIRECTION::WEST)
		{
			//�k�̏ꍇ���ɖ߂�
			direction_ = DIRECTION::NORTH;
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
	//�̗̓o�[�\��
	DrawHPBar();

	//�擾��Ύ擾���\��
	DrawGotGem();
}

void Player::Release(void)
{
}

bool Player::CollisionStage(const int& _stageModelId)
{
	auto& col = Collision::GetInstance();

	if (col.IsHitUnitStageObject(_stageModelId, trans_.pos, radius_))
	{
		//���������̂ňړ��O�ɖ߂�
		trans_.pos = prePos_;

		return true;
	}

	return false;
}

void Player::DrawHPBar(void)
{
	DrawBox(5, 5, BAR_POS_X, BAR_POS_Y, 0xffffff, true);

	float subHp = BAR_POS_X * (static_cast<float>(hp_) / static_cast<float>(HP_MAX));

	DrawBox(5 + DIFF_POS
		, 5 + DIFF_POS
		, hp_ == 0 ? 5 + subHp + DIFF_POS : subHp - DIFF_POS
		, BAR_POS_Y - DIFF_POS
		, 0xff0000, true);
}

void Player::DrawGotGem(void)
{
	unsigned int color = 0xdd66dd;

	for (int i = 0; i < ITEM_NUM; i++)
	{
		if (itemNum_ == i)color = 0x444444;

		DrawTriangle(GEM_POS_X + (GEM_SIZE_X + GEM_INTERVAL_POS) * i, GEM_POS_Y - GEM_SIZE_Y,	//�㕔��
			GEM_POS_X + GEM_SIZE_X + (GEM_SIZE_X + GEM_INTERVAL_POS) * i, GEM_POS_Y,			//�E����
			GEM_POS_X - GEM_SIZE_X + (GEM_SIZE_X + GEM_INTERVAL_POS) * i, GEM_POS_Y,			//������
			color, true);

		DrawTriangle(GEM_POS_X + (GEM_SIZE_X + GEM_INTERVAL_POS) * i, GEM_POS_Y + GEM_SIZE_Y,	//������
			GEM_POS_X - GEM_SIZE_X + (GEM_SIZE_X + GEM_INTERVAL_POS) * i, GEM_POS_Y,			//������
			GEM_POS_X + GEM_SIZE_X + (GEM_SIZE_X + GEM_INTERVAL_POS) * i, GEM_POS_Y,			//�E����
			color, true);
	}
}
