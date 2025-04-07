#pragma once
#include "UnitBase.h"
class Player : public UnitBase
{

	//�񋓌^
	enum class DIRECTION
	{
		NORTH,
		EAST,
		SOUTH,
		WEST
	};

	

public:

	//�v���C���[�T�C�Y
	static constexpr float RADIUS = 40.0f;
	//�v���C���[�X�s�[�h
	static constexpr float SPEED = 3.0f;

	//�̗̓o�[�֌W
	static constexpr int HP_MAX = 3;			//�ő�̗�
	static constexpr float BAR_POS_X = 300.0f;	//�o�[��X�ʒu
	static constexpr float BAR_POS_Y = 30.0f;	//�o�[��Y��
	static constexpr float DIFF_POS = 2.0f;		//�o�[�g�Ƃ̍�

	//��Ύ擾�֌W
	static constexpr int ITEM_NUM = 5;					//�K�v��Ύ擾��
	static constexpr float GEM_POS_X = 20.0f;			//��Ε\���̊J�nX�ʒu
	static constexpr float GEM_POS_Y = 60.0f;			//��Ε\���̊J�nY�ʒu
	static constexpr float GEM_SIZE_X = 10.0f;			//��΂̉��̑傫��
	static constexpr float GEM_SIZE_Y = 20.0f;			//��΂̏c�̑傫��
	static constexpr float GEM_INTERVAL_POS = 15.0f;	//��΂̕\���Ԋu

	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player()override;

	//������
	void Init(void)override;
	//�X�V
	void Update(void)override;
	//�`��
	void Draw(void)override;
	//���
	void Release(void)override;

	/// <summary>
	/// �X�e�[�W�Ƃ̏Փ˔���
	/// </summary>
	/// <param name="stageModelId">�X�e�[�W�̃��f��ID</param>
	/// <returns>�����������ǂ���(true:��������)</returns>
	bool CollisionStage(const int& _stageModelId);

	//�A�C�e���擾���𑝉�
	void AddItemNum(void) { itemNum_++; }

	//�̗͂�������
	void SubHp(void) { hp_--; }

	//�A�C�e���擾�����擾
	const int GetItemNum(void) { return itemNum_; }

	//��������
	bool IsAlive(void) { return hp_ > 0; }

	//�̗̓o�[�`��
	void DrawHPBar(void);

	//��Ύ擾���`��
	void DrawGotGem(void);

private:
	
	VECTOR axis_;
	DIRECTION direction_;
	
	//�A�C�e���擾��
	int itemNum_;

	//�̗�
	int hp_;

};

