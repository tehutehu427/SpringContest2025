#include <DxLib.h>
#include"../Utility/AsoUtility.h"
#include "Player.h"

Player::~Player()
{
}

void Player::Init(void)
{
	//初期化
	trans_.pos = {0.0f,0.0f,0.0f};
	trans_.pos = AsoUtility::VECTOR_ZERO;
	//カメラ方向初期化
	axis_ = { 0.0f,0.0f,0.0f };

	direction_ = DIRECTION::FRONT;
}

void Player::Update(void)
{

	//前に移動
	if (direction_ == DIRECTION::FRONT)
	{
		trans_.pos.z++;
	}
	//左
	if (direction_ == DIRECTION::LEFT)
	{
		trans_.pos.x--;
	}
	//右
	if (direction_ == DIRECTION::RIGHT)
	{
		trans_.pos.x++;
	}
	//後ろ
	if (direction_ == DIRECTION::BACK)
	{
		trans_.pos.z--;
	}


	//移動
	 //前
	if (CheckHitKey(KEY_INPUT_W))
	{
		//FRONTの場合
		if (direction_ == DIRECTION::FRONT)
		{
			Turn(00.0f, axis_);
			trans_.pos.z ++;
		}
		//LEFTの場合
		if (direction_ == DIRECTION::LEFT)
		{
			Turn(-90.0f, axis_);
			trans_.pos.x--;
		}
		//RIGHTの場合
		if (direction_ == DIRECTION::RIGHT)
		{
			Turn(90.0f, axis_);
			trans_.pos.x++;
		}
		//BACKの場合
		if (direction_ == DIRECTION::BACK)
		{
			Turn(180.0f, axis_);
			trans_.pos.z--;
		}

		//方向をFRONT変更
		direction_ == DIRECTION::FRONT;
	}
	//左
	if (CheckHitKey(KEY_INPUT_A))
	{
	
		
		
		//方向をLEFTに変更
		direction_ == DIRECTION::LEFT;
	}
	//右
	if (CheckHitKey(KEY_INPUT_D))
	{
		trans_.pos.x += 1;
	}
	//後ろ
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
