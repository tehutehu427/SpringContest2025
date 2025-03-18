#pragma once

#include<memory>
#include"Common/Transform.h"

class Player;
class EnemyManager;
class ItemManager;

class MiniMap
{
public:
	//�R���X�g���N�^
	MiniMap(Player* _player, EnemyManager* _eneMng, ItemManager* _itemMng);
	//�f�X�g���N�^
	~MiniMap();
	
	//������
	void Init(void);
	//�X�V
	void Update(void);
	//�`��
	void Draw(void);
	//���
	void Release(void);

private:

	Player* player_;
	EnemyManager* eneMng_;
	ItemManager* itemMng_;
};

