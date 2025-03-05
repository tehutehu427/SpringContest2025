#pragma once

class Enemy;

class EnemyManager
{
public:

	// �C���X�^���X�̐���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static EnemyManager& GetInstance(void);


	//������
	void Init(void);
	//�X�V
	void Update(void);
	//�`��
	void Draw(void);
	//���
	void Release(void);
private:
	//�ÓI�C���X�^���X
	static EnemyManager* instance_;

	//�G�N���X�̃C���X�^���X
	Enemy* enemy_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	EnemyManager(void);

	// �f�X�g���N�^�����l
	~EnemyManager(void) = default;


};

