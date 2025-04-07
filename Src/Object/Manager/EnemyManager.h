#pragma once
#include<vector>
#include <iostream>
#include <memory>

class Enemy;

class EnemyManager
{
public:
	//***********************************************
	//�萔
	//***********************************************
	////����
	//static constexpr VECTOR MOVE_POS_1 = { -600.0f,100.0f,1500.0f };
	//static constexpr VECTOR MOVE_POS_2 = { 110.0f,100.0f,1500.0f };
	//static constexpr VECTOR MOVE_POS_3 = { 800.0f,100.0f,1500.0f };
	//static constexpr VECTOR MOVE_POS_4 = { -600.0f,100.0f,800.0f };
	////�O��
	//static constexpr VECTOR MOVE_POS_5 = { 800.0f,100.0f,800.0f };
	//static constexpr VECTOR MOVE_POS_6 = { -600.0f,100.0f,200.0f };
	//static constexpr VECTOR MOVE_POS_7 = { 110.0f,100.0f,200.0f };
	//static constexpr VECTOR MOVE_POS_8 = { 800.0f,100.0f,200.0f };

	static constexpr int ENEMY_NUM =2;

	static constexpr float ENEMY1_MOVE_SPEED = 5.0f;		//�ړ����x
	static constexpr float ENEMY2_MOVE_SPEED = 5.0f;		//�ړ����x

	//***********************************************
	//�����o�֐�
	//***********************************************

	//�R���X�g���N�^
	EnemyManager(void);

	// �f�X�g���N�^
	~EnemyManager(void) = default;

	//������
	void Init(void);
	//�X�V
	void Update(void);
	//�`��
	void Draw(void);
	//���
	void Release(void);

	//�G�̎擾
	std::vector<std::shared_ptr<Enemy>> GetEnemys(void) { return enemys_; }
	
	//�G�̐���
	std::shared_ptr<Enemy> EnemyClass(void);

	/// <summary>
	/// �X�e�[�W�Ƃ̏Փ˔���
	/// </summary>
	/// <param name="stageModelId">�X�e�[�W�̃��f��ID</param>
	/// <returns>�����������ǂ���(true:��������)</returns>
	bool CollisionStage(const int& _stageModelId);

private:
	//***********************************************
	//�����o�ϐ�
	//***********************************************

	//�G�N���X�̃C���X�^���X
	//Enemy* enemy_[ENEMY_NUM];
	std::vector<std::shared_ptr<Enemy>>enemys_;

	//�ړ��ʒu
	std::vector<VECTOR>movePos_;

	//***********************************************
	//�����o�֐�
	//***********************************************

	//�G�̐���
	void CreateEnemy(void);

	//�G�̏���
	void EraseEnemy(void);
};

