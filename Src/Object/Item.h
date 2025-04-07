#pragma once

#include"UnitBase.h"

class Item : public UnitBase
{
#define DEBUG_ITEM

public:
	//***********************************************
	//�萔
	//***********************************************

	//���a
	static constexpr float RADIUS = 80.0f;

	//���f���̑傫��
	static constexpr VECTOR SCALE = { 0.05f,0.05f,0.05f };

	//���f���̃��f�����W�p
	static constexpr VECTOR MODEL_POS = { 0.0f,50.0f,0.0f };

	//***********************************************
	//�����o�֐�
	//***********************************************

	//�R���X�g���N�^
	Item(VECTOR& _pos);
	//�f�X�g���N�^
	~Item() = default;

	//������
	void Init(void);
	//�X�V
	void Update(void)override;
	//�`��
	void Draw(void)override;
	//�f�o�b�O�`��
	void DrawDebug(void);
	//���
	void Release(void)override;

private:

};

