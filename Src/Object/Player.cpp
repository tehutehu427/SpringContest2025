#include <DxLib.h>
#include"../Utility/AsoUtility.h"
#include "Player.h"

Player::~Player()
{
}

void Player::Init(void)
{
	trans_.pos = {0.0f,0.0f,0.0f};
	trans_.pos = AsoUtility::VECTOR_ZERO;
}

void Player::Update(void)
{

	//移動
	 //前
	if (CheckHitKey(KEY_INPUT_W))
	{
		trans_.pos.z += 1;
	}
	//左
	if (CheckHitKey(KEY_INPUT_A))
	{
		trans_.pos.x += 1;
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
