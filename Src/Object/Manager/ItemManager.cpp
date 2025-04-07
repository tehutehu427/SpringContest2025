#include<DxLib.h>
#include"../../Manager/System/Timer.h"
#include"../Item.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
}

void ItemManager::Init(void)
{
	spawnPos_.emplace_back(SPAWN_POS_1);
	spawnPos_.emplace_back(SPAWN_POS_2);
	spawnPos_.emplace_back(SPAWN_POS_3);
	spawnPos_.emplace_back(SPAWN_POS_4);
	spawnPos_.emplace_back(SPAWN_POS_5);
	spawnPos_.emplace_back(SPAWN_POS_6);
	spawnPos_.emplace_back(SPAWN_POS_7);
	spawnPos_.emplace_back(SPAWN_POS_8);

	cnt_ = 0.0f;
	spawnNum_ = 0;

	//アイテム生成
	CreateItem();
}

void ItemManager::Update(void)
{
	//アイテムの消去(デバッグ)
	//DebugCountDelete();

	//アイテムの更新
	item_->Update();
}

void ItemManager::Draw(void)
{
	//アイテムの描画
	item_->Draw();
}

void ItemManager::DrawDebug(void)
{
}

void ItemManager::Release(void)
{
	//アイテムの解放
	item_->Release();
	item_.reset();
}

const std::shared_ptr<Item> ItemManager::GetItem(void)
{
	return item_;
}

void ItemManager::CreateItem(void)
{
	//現在の出現番号を保存
	int nowSpawnNum = spawnNum_;

	//リセット
	item_.reset();

	//現在の場所と被らないように
	while (spawnNum_ == nowSpawnNum)
	{
		//ランダム
		spawnNum_ = GetRand(spawnPos_.size() - 1);
	}

	//生成
	item_ = std::make_shared<Item>(spawnPos_[spawnNum_]);
	item_->Init();
}

void ItemManager::DebugCountDelete(void)
{
	//カウントアップ
	Timer::GetInstance().CntUp(cnt_);

	if (cnt_ >= 3.0f)
	{
		//アイテムを新しく生成
		CreateItem();
		
		cnt_ = 0.0f;
	}
}
