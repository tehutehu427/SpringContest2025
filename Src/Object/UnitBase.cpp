#include"../Application.h"
#include"../Utility/AsoUtility.h"
#include "UnitBase.h"

UnitBase::UnitBase()
{
	trans_.modelId = -1;
	trans_.pos = { 0.0f,0.0f,0.0f };
	trans_.scl = { 0.0f,0.0f,0.0f };
	trans_.rot = { 0.0f,0.0f,0.0f };

	radius_ = 0.0f;
	speed_ = 0.0f;

	anim_ = ANIM::NONE;
	atcAnim_ = -1;
	animTotalTime_ = -1;
	stepAnim_ = -1.0f;
	speedAnim_ = 1.0f;
}

UnitBase::~UnitBase()
{
}

void UnitBase::ResetAnim(const ANIM _anim, const float _speed)
{
	if (anim_ == _anim)return;

	//�A�j���[�V�����X�s�[�h�̕ύX
	speedAnim_ = _speed;

	//�f�^�b�`
	//����atcAnim�̏�����
	MV1DetachAnim(trans_.modelId, atcAnim_);

	anim_ = _anim;
	//�A�^�b�`
	//����atcAnim�̑��
	atcAnim_ = MV1AttachAnim(trans_.modelId, animNum_[anim_]);

	animTotalTime_ = MV1GetAttachAnimTotalTime(trans_.modelId, atcAnim_);
	stepAnim_ = 0.0f;

	// �Đ�����A�j���[�V�������Ԃ̐ݒ�
	MV1SetAttachAnimTime(trans_.modelId, atcAnim_, stepAnim_);
}

void UnitBase::Turn(const float _deg, const VECTOR& _axis)
{
	trans_.quaRot =
		trans_.quaRot.Mult(trans_.quaRot, (Quaternion::AngleAxis(AsoUtility::Deg2RadF(_deg), _axis)));
}

void UnitBase::Anim(void)
{
	// �A�j���[�V�����Đ�
	// �o�ߎ��Ԃ̎擾
	float deltaTime = 1.0f / Application::DEFAULT_FPS;
	// �A�j���[�V�������Ԃ̐i�s
	stepAnim_ += (speedAnim_ * deltaTime);
	if (stepAnim_ > animTotalTime_)
	{
		//�A�j���[�V�����I���������i�p����ōs�������߂Ă����j
		FinishAnim();
	}
	// �Đ�����A�j���[�V�������Ԃ̐ݒ�
	MV1SetAttachAnimTime(trans_.modelId, atcAnim_, stepAnim_);
}

void UnitBase::FinishAnim(void)
{
	//���[�v�Đ�
	stepAnim_ = 0.0f;
}
