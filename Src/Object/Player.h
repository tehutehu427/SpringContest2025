#pragma once
#include "UnitBase.h"
class Player : public UnitBase
{

	//�񋓌^
	enum class DIRECTION
	{
		FRONT,
		LEFT,
		RIGHT,
		BACK,
		MAX
	};

public:

	//�v���C���[�T�C�Y
	static constexpr int SIZE = 10;
	//�v���C���[�X�s�[�h
	static constexpr int SPEED = 1;


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

private:
	
	VECTOR axis_;
	DIRECTION direction_;
	
};

