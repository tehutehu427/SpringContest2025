#pragma once
#include<vector>
#include <iostream>
#include <memory>

class Enemy;

class EnemyManager
{
public:
	static constexpr int ENEMY_NUM =2;

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
	Enemy* EnemyClass(void);

private:
	//�G�N���X�̃C���X�^���X
	//Enemy* enemy_[ENEMY_NUM];
	std::vector<Enemy*>enemys_;


	void CreateEnemy(void);
	void EraseEnemy(void);
};

