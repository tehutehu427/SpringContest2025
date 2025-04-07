#include <DxLib.h>
#include"../Utility/AsoUtility.h"
#include"../Manager/Generic/InputManager.h"
#include "Player.h"

//コンストラクタ
Player::Player()
{
	
}

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

	//プレイヤーが向いている方向
	direction_ == DIRECTION::NORTH;

	//プレイヤーの半径
	radius_ = SIZE / 2;

}

void Player::Update(void)
{
	auto& ins = InputManager::GetInstance();
	//北に移動
	if (direction_ == DIRECTION::NORTH)
	{
		trans_.pos.z++;
	}
	//西
	if (direction_ == DIRECTION::WEST)
	{
		trans_.pos.x++;
	}
	//東
	if (direction_ == DIRECTION::EAST )
	{
		trans_.pos.x--;
	}
	//南
	if (direction_ == DIRECTION:: SOUTH)
	{
		trans_.pos.z--;
	}


	
	if (ins.IsTrgDown(KEY_INPUT_A))
	{
		if (direction_ == DIRECTION::NORTH)
		{
			//北の場合西に戻す
			direction_ = DIRECTION::WEST;
	    }
		else
		{
		 direction_ = static_cast <DIRECTION>(static_cast <int> (direction_) - 1);
		}

		//カメラの方向を変える　　↓回転軸
		Turn(-90.0f, AsoUtility::AXIS_Y);

	}
  //右
	if (ins.IsTrgDown(KEY_INPUT_D))
	{

		if (direction_ == DIRECTION::NORTH)
		{
			//北の場合西に戻す
			direction_ = DIRECTION::WEST;
		}
		else
		{
			direction_ = static_cast <DIRECTION>(static_cast <int> (direction_) + 1);
		}

		//カメラの方向を変える
		Turn(90.0f, AsoUtility::AXIS_Y);
	}
	//後ろ
	if (ins.IsTrgDown(KEY_INPUT_S))
	{
		if (direction_ == DIRECTION::NORTH || direction_ == DIRECTION::EAST)
		{
			//北と東向いてるとき
			direction_ = static_cast <DIRECTION>(static_cast <int> (direction_) + 2);
		}
		else
		{
			//南と西向いてるとき
			direction_ = static_cast <DIRECTION>(static_cast <int> (direction_) - 2);
		}

		//カメラの方向を変える
		Turn(180.0f, AsoUtility::AXIS_Y);
	}
}

void Player::Draw(void)
{
}

void Player::Release(void)
{
}
