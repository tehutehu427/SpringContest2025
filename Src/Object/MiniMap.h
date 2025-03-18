#pragma once

#include<memory>
#include"../Application.h"
#include"Common/Transform.h"

class Player;
class EnemyManager;
class ItemManager;

class MiniMap
{
public:

	//�~�j�}�b�v
	static constexpr int MAP_SIZE = 100;										//�~�j�}�b�v�摜�̑傫��
	static constexpr float MAP_POS_X = Application::SCREEN_SIZE_X - MAP_SIZE;	//�~�j�}�b�v��X���W
	static constexpr float MAP_POS_Y = Application::SCREEN_SIZE_Y - MAP_SIZE;	//�~�j�}�b�v��Y���W

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

	Player* player_;		//�v���C���[
	EnemyManager* eneMng_;	//�G
	ItemManager* itemMng_;	//�A�C�e��

	int mapFrameImg_;		//�g�摜
	int mapGroundImg_;		//�g���摜
};

