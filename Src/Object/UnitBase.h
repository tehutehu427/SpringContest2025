#pragma once

#include<unordered_map>
#include"Common/Transform.h"

class UnitBase
{
public:

	//***********************************************
	//�񋓌^
	//***********************************************

	//�A�j���[�V����
	enum class ANIM
	{
		NONE,	
		IDLE,	//�ҋ@
		WALK,	//����
	};

	//***********************************************
	//�����o�֐�
	//***********************************************

	//�R���X�g���N�^
	UnitBase();
	//�f�X�g���N�^
	virtual ~UnitBase() = 0;

	//������
	virtual void Init(void) = 0;
	//�X�V
	virtual void Update(void) = 0;
	//�`��
	virtual void Draw(void) = 0;
	//���
	virtual void Release(void) = 0;

	//���f�����
	const Transform& GetTransform(void) { return trans_; }

	//�ʒu
	const VECTOR GetPos(void)const { return trans_.pos; };
	//�p�x
	const VECTOR GetRot(void)const { return trans_.rot; };
	//�傫��
	const VECTOR GetScl(void)const { return trans_.scl; };

	//���a
	const float GetRadius(void)const { return radius_; }

	//�A�j���[�V�������Z�b�g
	void ResetAnim(const ANIM _anim, const float _speed);

	/// <summary>
	/// ��]����
	/// </summary>
	/// <param name="_deg">��]����p�x(�f�O���[�p)</param>
	/// <param name="_axis">��]����</param>
	void Turn(const float _deg, const VECTOR& _axis);

protected:

	//***********************************************
	//�����o�ϐ�
	//***********************************************

	//���f���̏��
	Transform trans_;

	//���a
	float radius_;

	//���x
	float speed_;

	//�A�j���[�V����
	ANIM anim_;								//�A�j���X�e�[�g
	std::unordered_map<ANIM, int> animNum_;	//�A�j���[�V�����i���o�[�i�[�z��B
	int atcAnim_;							//�A�^�b�`����A�j�����i�[
	int animTotalTime_;						//�A�j���[�V�����̑��Đ�����
	float stepAnim_;						//�A�j���[�V�����̍Đ�����
	float speedAnim_;						//�A�j���[�V�������x


	//***********************************************
	//�����o�֐�
	//***********************************************

	//�A�j���[�V�����֐�
	void Anim(void);
	//�A�j���[�V�����I�����̓���
	virtual void FinishAnim(void);
};

