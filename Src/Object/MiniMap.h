#pragma once

#include<memory>
#include"../Application.h"
#include"Common/Transform.h"

class Player;
class EnemyManager;
class ItemManager;
class Stage;

class MiniMap
{
public:

	//�~�j�}�b�v
	static constexpr int MAP_SIZE = 130;											//�~�j�}�b�v�摜�̑傫��
	static constexpr float MAP_POS_X = Application::SCREEN_SIZE_X - MAP_SIZE + 15;	//�~�j�}�b�v��X���W
	static constexpr float MAP_POS_Y = MAP_SIZE;									//�~�j�}�b�v��Y���W
	static constexpr double IMAGE_EX_RATE = 1.0;									//�~�j�}�b�v�g�嗦
	static constexpr double MAP_EX_RATE = 0.075;									//�~�j�}�b�v�g�嗦

	//�R���X�g���N�^
	MiniMap(Player* _player, EnemyManager* _eneMng, ItemManager* _itemMng, Stage* _stage);
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
	Stage* stage_;			//�X�e�[�W

	int mapFrameImg_;		//�g�摜
	int mapGroundImg_;		//�g���摜
	int mapImg_;			//�}�b�v�摜
	int mapPlayerImg_;		//�v���C���[�摜
	int mapEnemyImg_;		//�G�摜

	/// <summary>
	/// �Ƃ���ʒu����Ƃ���ʒu�܂ł̑��΋���
	/// </summary>
	/// <param name="_startObj">�J�n�I�u�W�F�N�g�ʒu</param>
	/// <param name="_goalObj">�I���I�u�W�F�N�g�ʒu</param>
	/// <returns>���΋���</returns>
	const VECTOR GetDistance(const VECTOR _startObj, const VECTOR _goalObj)const;

	//�v���C���[�`��
	void DrawPlayer(void);

	//�G�`��
	void DrawEnemy(void);

	//�A�C�e���`��
	void DrawItem(void);

	//����`��
	void DrawVision(void);

	/// <summary>
	/// �Ƃ���_����Ƃ���_�܂ł̈ړ��x�N�g����Ԃ�
	/// </summary>
	/// <param name="_start">�_����</param>
	/// <param name="_goal">��������</param>
	/// <param name="_speed">�ݒ葬�x(���ݒ肾�ƁA�����x�N�g���݂̂�Ԃ�)</param>
	/// <returns>��������܂ł̈ړ��x�N�g��</returns>
	const VECTOR GetMoveVec(const VECTOR _start, const VECTOR _goal, const float _speed = 1.0f)const;

	/// <summary>
	/// �Ƃ���_����Ƃ���_�܂ł̋�����Ԃ�
	/// </summary>
	/// <param name="_start">�J�n�n�_</param>
	/// <param name="_goal">�I���n�_</param>
	/// <returns>����</returns>
	const float CalcDistance(const VECTOR _start, const VECTOR _goal)const;

};

