#include <EffekseerForDXLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "../../Object/Common/Transform.h"
#include "Camera.h"

Camera::Camera(void)
{
	mode_ = MODE::NONE;
	pos_ = { 0.0f, 0.0f, 0.0f };
	targetPos_ = { 0.0f, 0.0f, 0.0f };
	rot_ = Quaternion::Identity();
}

Camera::~Camera(void)
{
}

void Camera::Init(void)
{
	//�֐��|�C���^�̐ݒ�
	setBeforeDrawMode_.emplace(MODE::NONE, std::bind(&Camera::SetBeforeDrawFollow, this));
	setBeforeDrawMode_.emplace(MODE::FIXED_POINT, std::bind(&Camera::SetBeforeDrawFixedPoint, this));
	setBeforeDrawMode_.emplace(MODE::FREE, std::bind(&Camera::SetBeforeDrawFree, this));
	setBeforeDrawMode_.emplace(MODE::FOLLOW, std::bind(&Camera::SetBeforeDrawFollow, this));
	setBeforeDrawMode_.emplace(MODE::FOLLOW_SPRING, std::bind(&Camera::SetBeforeDrawFollowSpring, this));
	setBeforeDrawMode_.emplace(MODE::FOLLOW_PERSPECTIVE, std::bind(&Camera::SetBeforeDrawFollowPerspective, this));
	setBeforeDrawMode_.emplace(MODE::SHAKE, std::bind(&Camera::SetBeforeDrawShake, this));

	//�J�����̏����ݒ�
	SetDefault();

	moveSpeed_ = 0.0f;

}

void Camera::Update(void)
{
}

void Camera::SetBeforeDraw(void)
{

	//�N���b�v������ݒ肷��(SetDrawScreen�Ń��Z�b�g�����)
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);

	//���[�h�ɂ��ݒ�؂�ւ�
	setBeforeDrawMode_[mode_]();

	//�J�����̐ݒ�(�ʒu�ƒ����_�ɂ�鐧��)
	SetCameraPositionAndTargetAndUpVec(
		pos_, 
		targetPos_, 
		cameraUp_
	);

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
}

void Camera::SetBeforeDrawFixedPoint(void)
{
	//�������Ȃ�
}

void Camera::SetBeforeDrawFree(void)
{
	auto& ins = InputManager::GetInstance();

	ProcessMove();

	Decelerate(MOVE_DEC);

	Move();

}

void Camera::SetBeforeDrawFollow(void)
{
	//�Ǐ]�Ώۂ̈ʒu
	VECTOR followPos = followTransform_->pos;

	//�Ǐ]�Ώۂ̌���
	Quaternion followRot = followTransform_->quaRot;

	//�Ǐ]�Ώۂ���J�����܂ł̑��΍��W
	VECTOR relativeCPos = followRot.PosAxis(RELATIVE_F2C_POS_FOLLOW);

	//�J�����ʒu�̍X�V
	pos_ = VAdd(followPos, relativeCPos);

	//�J�����ʒu���璍���_�܂ł̑��΍��W
	VECTOR relativeTPos = followRot.PosAxis(RELATIVE_C2T_POS);

	//�����_�̍X�V
	targetPos_ = VAdd(pos_, relativeTPos);

	//�J�����̏����
	cameraUp_ = followRot.PosAxis(rot_.GetUp());

}

void Camera::SetBeforeDrawFollowSpring(void)
{
	auto& ins = InputManager::GetInstance();

	//C�L�[�����ŃJ������h�炷
	if (ins.IsTrgDown(KEY_INPUT_C))
	{
		currentMode_ = mode_;
		ChangeMode(MODE::SHAKE);
	}

	//�΂˒萔(�΂˂̋���)
	float POW_SPRING = 50.0f;

	//�΂˒萔�i�΂˂̒�R�j
	float dampening = 2.0f * sqrt(POW_SPRING);

	//�f���^�^�C��
	float delta = SceneManager::GetInstance().GetDeltaTime();

	//3D��������l�p
	//delta = 1.0f / 60.0f;

	//�Ǐ]�Ώۂ̈ʒu
	VECTOR followPos = followTransform_->pos;

	//�Ǐ]�Ώۂ̌���
	Quaternion followRot = followTransform_->quaRot;
	VECTOR zero = { 0.0f,0.0f,0.0f };

	//�J�����̕������Œ肷��p
	Quaternion forward = Quaternion::Euler(zero);

	//�Ǐ]�Ώۂ���J�����܂ł̑��΍��W
	VECTOR relativeCPos = forward.PosAxis(RELATIVE_F2C_POS_FOLLOW);

	//���z�ʒu
	VECTOR idealPos = VAdd(followPos, relativeCPos);

	//���ۂƗ��z�̍�
	VECTOR diff = VSub(pos_, idealPos);

	//�� = -�o�l�̋��� �~ �o�l�̐L�� - ��R �~ �J�����̑��x
	VECTOR force = VScale(diff, -POW_SPRING);
	force = VSub(force, VScale(velocity_, dampening));

	//���x�̍X�V
	velocity_ = VAdd(velocity_, VScale(force, delta));

	//�J�����ʒu�̍X�V
	pos_ = VAdd(pos_, VScale(velocity_, delta));

	//�J�����ʒu���璍���_�܂ł̑��΍��W
	VECTOR relativeTPos = forward.PosAxis(RELATIVE_C2T_POS);

	//�����_�̍X�V
	targetPos_ = VAdd(pos_, relativeTPos);

	//�J�����̏����
	cameraUp_ = forward.PosAxis(rot_.GetUp());

}

void Camera::SetBeforeDrawFollowPerspective(void)
{
	//�Ǐ]�Ώۂ̈ʒu
	VECTOR followPos = followTransform_->pos;

	//�Ǐ]�Ώۂ̌���
	Quaternion followRot = followTransform_->quaRot;

	//�J�����ʒu�̍X�V
	pos_ = followPos;

	//�J�����ʒu���璍���_�܂ł̑��΍��W
	VECTOR relativeTPos = followRot.PosAxis(RELATIVE_C2T_POS_FOLLOW_PERSPECTIVE);

	//�����_�̍X�V
	targetPos_ = VAdd(pos_, relativeTPos);

	//�J�����̏����
	cameraUp_ = followRot.PosAxis(rot_.GetUp());
}

void Camera::SetBeforeDrawShake(void)
{
	// ��莞�ԃJ������h�炷
	stepShake_ -= SceneManager::GetInstance().GetDeltaTime();

	if (stepShake_ < 0.0f)
	{
		pos_ = defaultPos_;
		ChangeMode(MODE::FOLLOW_SPRING);
		return;
	}

	// -1.0f�`1.0f
	float f = sinf(stepShake_ * SPEED_SHAKE);

	// -1000.0f�`1000.0f
	f *= 1000.0f;

	// -1000 or 1000
	int d = static_cast<int>(f);

	// 0 or 1
	int shake = d % 2;

	// 0 or 2
	shake *= 2;

	// -1 or 1
	shake -= 1;

	// �ړ���
	VECTOR velocity = VScale(shakeDir_, (float)(shake)*WIDTH_SHAKE);

	// �ړ�����W
	 pos_ = VAdd(defaultPos_, velocity);

	//float pow = WIDTH_SHAKE * sinf(stepShake_ * SPEED_SHAKE);
	//VECTOR velocity = VScale(shakeDir_, pow);
	//VECTOR newPos = VAdd(defaultPos_, velocity);
	//pos_ = newPos;

}

void Camera::Draw(void)
{
}

void Camera::Release(void)
{
}

VECTOR Camera::GetPos(void) const
{
	return pos_;
}

void Camera::ChangeMode(MODE mode)
{

	//�J�����̏����ݒ�
	//�J������h�炷�O�̈ʒu�ŗh���悤�ɂ��������ߊO���Ă���
	//SetDefault();
	
	//�J�������[�h�̕ύX
  	mode_ = mode;

	//�ύX���̏���������
	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		break;
	case Camera::MODE::FREE:
		break;
	case Camera::MODE::FOLLOW:
		break;
	case Camera::MODE::FOLLOW_SPRING:
		break;
	case Camera::MODE::SHAKE:
		stepShake_ = TIME_SHAKE;
		shakeDir_ = VNorm({ 0.7f, 0.7f ,0.0f });
		defaultPos_ = pos_;
	}

}

const void Camera::SetFollow(const Transform* follow)
{
	followTransform_ = follow;
}

void Camera::SetPos(const VECTOR& pos, const VECTOR& target)
{
	pos_ = pos;
	targetPos_ = target;
}

void Camera::SetDefault(void)
{

	//�J�����̏����ݒ�
	pos_ = DEFAULT_CAMERA_POS;

	//�����_
	targetPos_ = VAdd(pos_, RELATIVE_C2T_POS);

	//�J�����̏����
	cameraUp_ = { 0.0f, 1.0f, 0.0f };

	//�J������X���ɌX���Ă��邪�A
	//���̌X������Ԃ��p�x�[���A�X�������Ƃ���
	rot_ = Quaternion::Identity();

	velocity_ = AsoUtility::VECTOR_ZERO;

}

void Camera::ProcessMove(void)
{
	auto& ins = InputManager::GetInstance();

	//�ړ�
	if (ins.IsNew(KEY_INPUT_W)) { moveDir_ = AsoUtility::DIR_F; Accele(MOVE_ACC); }
	if (ins.IsNew(KEY_INPUT_S)) { moveDir_ = AsoUtility::DIR_B; Accele(MOVE_ACC); }
	if (ins.IsNew(KEY_INPUT_A)) { moveDir_ = AsoUtility::DIR_L; Accele(MOVE_ACC); }
	if (ins.IsNew(KEY_INPUT_D)) { moveDir_ = AsoUtility::DIR_R; Accele(MOVE_ACC); }

	//��]���Ɨʂ����߂�
	const float ROT_POW = 1.0f;
	VECTOR axisDeg = AsoUtility::VECTOR_ZERO;
	if (ins.IsNew(KEY_INPUT_UP)) { axisDeg.x = -1.0f; }
	if (ins.IsNew(KEY_INPUT_DOWN)) { axisDeg.x = 1.0f; }
	if (ins.IsNew(KEY_INPUT_LEFT)) { axisDeg.y = -1.0f; }
	if (ins.IsNew(KEY_INPUT_RIGHT)) { axisDeg.y = 1.0f; }


	//�J�������W�𒆐S�Ƃ��āA�����_����]������
	if (!AsoUtility::EqualsVZero(axisDeg))
	{
		//����̉�]�ʂ�����
		Quaternion rotPow;
		rotPow = rotPow.Mult(
			Quaternion::AngleAxis(
				AsoUtility::Deg2RadF(axisDeg.z), AsoUtility::AXIS_Z));
		rotPow = rotPow.Mult(
			Quaternion::AngleAxis(
				AsoUtility::Deg2RadF(axisDeg.x), AsoUtility::AXIS_X));
		rotPow = rotPow.Mult(
			Quaternion::AngleAxis(
				AsoUtility::Deg2RadF(axisDeg.y), AsoUtility::AXIS_Y));

		//�J�����̉�]�̍���̉�]�ʂ�������i�����j
		rot_ = rot_.Mult(rotPow);

		//�����_�̑��΍��W����]������
		VECTOR rotLocalPos = rot_.PosAxis(RELATIVE_C2T_POS);

		//�����_�X�V
		targetPos_ = VAdd(pos_, rotLocalPos);

		//�J�����̏�����X�V
		cameraUp_ = rot_.GetUp();
	}
}

void Camera::Move(void)
{
	//�ړ�����
	if (!AsoUtility::EqualsVZero(moveDir_))
	{
		//�ړ� = ���W + �ړ���
		//�ړ��� = ���� * �X�s�[�h 

		//���͂��ꂽ�������J�����̉�]�����g���āA
		//�J�����̐i�s�����ɕϊ�����
		VECTOR direction = rot_.PosAxis(moveDir_);

		//�ړ���
		VECTOR movePow = VScale(direction, moveSpeed_);

		//�ړ�����
		pos_ = VAdd(pos_, movePow);

		targetPos_ = VAdd(targetPos_, movePow);
	}
}

void Camera::Accele(float speed)
{
	moveSpeed_ += speed;

	//���x����(�E����)
	if (moveSpeed_ > MAX_MOVE_SPEED)
	{
		moveSpeed_ = MAX_MOVE_SPEED;
	}

	//���x����(������)
	if (moveSpeed_ < -MAX_MOVE_SPEED)
	{
		moveSpeed_ = -MAX_MOVE_SPEED;
	}
}

void Camera::Decelerate(float speed)
{
	//�E�����̈ړ�������������
	if (moveSpeed_ > 0.0f)
	{
		moveSpeed_ -= speed;
		if (moveSpeed_ < 0.0f)
		{
			moveSpeed_ = 0.0f;
		}
	}

	//�������̈ړ�������������
	if (moveSpeed_ < 0.0f)
	{
		moveSpeed_ += speed;
		if (moveSpeed_ > 0.0f)
		{
			moveSpeed_ = 0.0f;
		}
	}
}