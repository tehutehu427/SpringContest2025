#pragma once

#include <vector>
#include <iostream>
#include <memory>

class Item;

class ItemManager
{
public:
	//***********************************************
	//�萔
	//***********************************************

	static constexpr VECTOR SPAWN_POS_1 = { 100.0f,0.0f,100.0f };
	static constexpr VECTOR SPAWN_POS_2 = { 0.0f,0.0f,100.0f };
	static constexpr VECTOR SPAWN_POS_3 = { -100.0f,0.0f,100.0f };
	static constexpr VECTOR SPAWN_POS_4 = { 100.0f,0.0f,0.0f };
	static constexpr VECTOR SPAWN_POS_5 = { 0.0f,0.0f,0.0f };
	static constexpr VECTOR SPAWN_POS_6 = { -100.0f,0.0f,0.0f };
	static constexpr VECTOR SPAWN_POS_7 = { 100.0f,0.0f,-100.0f };
	static constexpr VECTOR SPAWN_POS_8 = { 0.0f,0.0f,-100.0f };
	static constexpr VECTOR SPAWN_POS_9 = { -10.0f,0.0f,-100.0f };

	//***********************************************
	//�����o�֐�
	//***********************************************

	//�R���X�g���N�^
	ItemManager();
	//�f�X�g���N�^
	~ItemManager() = default;

	//������
	void Init(void);
	//�X�V
	void Update(void);
	//�`��
	void Draw(void);
	//�f�o�b�O�`��
	void DrawDebug(void);
	//���
	void Release(void);

	//�A�C�e���擾
	const std::shared_ptr<Item> GetItem(void);

private:
	//***********************************************
	//�����o�ϐ�
	//***********************************************

	//�A�C�e��
	std::shared_ptr<Item> item_;

	//�o���ʒu
	std::vector<VECTOR> spawnPos_;

	float cnt_;

	//***********************************************
	//�����o�֐�
	//***********************************************

	//�A�C�e���̐���
	void CreateItem(void);

	//�A�C�e���̈��Ԋu�ł̏���(�f�o�b�O)
	void DebugCountDelete(void);
};

