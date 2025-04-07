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

	//�A�C�e������
	CreateItem();
}

void ItemManager::Update(void)
{
	//�A�C�e���̏���(�f�o�b�O)
	//DebugCountDelete();

	//�A�C�e���̍X�V
	item_->Update();
}

void ItemManager::Draw(void)
{
	//�A�C�e���̕`��
	item_->Draw();
}

void ItemManager::DrawDebug(void)
{
}

void ItemManager::Release(void)
{
	//�A�C�e���̉��
	item_->Release();
	item_.reset();
}

const std::shared_ptr<Item> ItemManager::GetItem(void)
{
	return item_;
}

void ItemManager::CreateItem(void)
{
	//���݂̏o���ԍ���ۑ�
	int nowSpawnNum = spawnNum_;

	//���Z�b�g
	item_.reset();

	//���݂̏ꏊ�Ɣ��Ȃ��悤��
	while (spawnNum_ == nowSpawnNum)
	{
		//�����_��
		spawnNum_ = GetRand(spawnPos_.size() - 1);
	}

	//����
	item_ = std::make_shared<Item>(spawnPos_[spawnNum_]);
	item_->Init();
}

void ItemManager::DebugCountDelete(void)
{
	//�J�E���g�A�b�v
	Timer::GetInstance().CntUp(cnt_);

	if (cnt_ >= 3.0f)
	{
		//�A�C�e����V��������
		CreateItem();
		
		cnt_ = 0.0f;
	}
}
