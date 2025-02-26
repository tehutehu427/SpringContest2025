#include"../Utility/AsoUtility.h"
#include "Player.h"

Player::~Player()
{
}

void Player::Init(void)
{
	//trans_.pos = {0.0f,0.0f,0.0f};
	trans_.pos = AsoUtility::VECTOR_ZERO;
}

void Player::Update(void)
{
}

void Player::Draw(void)
{
}

void Player::Release(void)
{
}
