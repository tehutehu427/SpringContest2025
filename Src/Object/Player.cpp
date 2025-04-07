#include <DxLib.h>
#include"../Utility/AsoUtility.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/System/Collision.h"
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
	trans_.pos = { 0.0f,100.0f,-750.0f };
	prePos_ = trans_.pos;
	//カメラ方向初期化
	axis_ = { 0.0f,0.0f,0.0f };

	//プレイヤーが向いている方向
	direction_ == DIRECTION::NORTH;

	//プレイヤーの半径
	radius_ = RADIUS;

	speed_ = SPEED;
	prePos_ = trans_.pos;
	itemNum_ = 0;
	hp_ = HP_MAX;

}

void Player::Update(void)
{
	auto& ins = InputManager::GetInstance();

	//移動前座標保存
	prePos_ = trans_.pos;

	//北に移動
	if (direction_ == DIRECTION::NORTH)
	{
		trans_.pos.z += speed_;
	}
	//西
	if (direction_ == DIRECTION::WEST)
	{
		trans_.pos.x -= speed_;
	}
	//東
	if (direction_ == DIRECTION::EAST )
	{
		trans_.pos.x += speed_;
	}
	//南
	if (direction_ == DIRECTION:: SOUTH)
	{
		trans_.pos.z -= speed_;
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

		if (direction_ == DIRECTION::WEST)
		{
			//北の場合西に戻す
			direction_ = DIRECTION::NORTH;
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
	//体力バー表示
	DrawHPBar();

	//取得宝石取得数表示
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
		//当たったので移動前に戻る
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

		DrawTriangle(GEM_POS_X + (GEM_SIZE_X + GEM_INTERVAL_POS) * i, GEM_POS_Y - GEM_SIZE_Y,	//上部分
			GEM_POS_X + GEM_SIZE_X + (GEM_SIZE_X + GEM_INTERVAL_POS) * i, GEM_POS_Y,			//右部分
			GEM_POS_X - GEM_SIZE_X + (GEM_SIZE_X + GEM_INTERVAL_POS) * i, GEM_POS_Y,			//左部分
			color, true);

		DrawTriangle(GEM_POS_X + (GEM_SIZE_X + GEM_INTERVAL_POS) * i, GEM_POS_Y + GEM_SIZE_Y,	//下部分
			GEM_POS_X - GEM_SIZE_X + (GEM_SIZE_X + GEM_INTERVAL_POS) * i, GEM_POS_Y,			//左部分
			GEM_POS_X + GEM_SIZE_X + (GEM_SIZE_X + GEM_INTERVAL_POS) * i, GEM_POS_Y,			//右部分
			color, true);
	}
}
