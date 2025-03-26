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
	static constexpr int MAP_SIZE = 130;											//�~�j�}�b�v�摜�̑傫��
	static constexpr float MAP_POS_X = Application::SCREEN_SIZE_X - MAP_SIZE + 15;	//�~�j�}�b�v��X���W
	static constexpr float MAP_POS_Y = MAP_SIZE;									//�~�j�}�b�v��Y���W
	static constexpr double MAP_EX_RATE = 1.0;										//�~�j�}�b�v�g�嗦
	static constexpr double PLAYER_EX_RATE = 1.0;									//�v���C���[�g�嗦

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
	int mapPlayerImg_;		//�v���C���[�摜

	//�v���C���[�`��
	void DrawPlayer(void);

	//�G�`��
	void DrawEnemy(void);

	//�A�C�e���`��
	void DrawItem(void);

	//����`��
	void DrawVision(void);
};

