#pragma once

#include<unordered_map>
#include<memory>
#include"Common/Transform.h"
#include"Common/AnimationController.h"

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

	//�Q�b�^�[
	//----------------------

	//�ʒu
	const VECTOR& GetPos(void)const { return trans_.pos; }
	//�p�x
	const VECTOR& GetRot(void)const { return trans_.rot; }
	//�傫��
	const VECTOR& GetScl(void)const { return trans_.scl; }
	//�O���W
	const VECTOR& GetPrePos(void)const { return prePos_; }

	//���a
	const float GetRadius(void)const { return radius_; }

	//�Z�b�^�[
	//----------------------

	//�ʒu
	void SetPos(const VECTOR& _pos) { trans_.pos = _pos; }

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

	//�O���W
	VECTOR prePos_;

	//���a
	float radius_;

	//���x
	float speed_;

	//�ړ���
	VECTOR movePow_;

	//�A�j���[�V�����֌W
	std::unique_ptr<AnimationController> anim_;		//�A�j���[�V��������

	//***********************************************
	//�����o�֐�
	//***********************************************

	//�A�j���[�V�������Z�b�g
	virtual void InitAnimation(void);
};

