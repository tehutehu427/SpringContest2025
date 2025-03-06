#pragma once

class Enemy;

class EnemyManager
{
public:

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
private:
	//�G�N���X�̃C���X�^���X
	Enemy* enemy_;
};

