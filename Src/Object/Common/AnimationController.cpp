#include <DxLib.h>
#include "../../Manager/Generic/SceneManager.h"
#include "AnimationController.h"

AnimationController::AnimationController(int modelId)
{
	modelId_ = modelId;

	playType_ = -1;
	isLoop_ = false;

	isStop_ = false;
	switchLoopReverse_ = 0.0f;
	endLoopSpeed_ = 0.0f;
	stepEndLoopStart_ = 0.0f;
	stepEndLoopEnd_ = 0.0f;
}

AnimationController::~AnimationController(void)
{
	for (const auto& anim : animations_)
	{
		MV1DeleteModel(anim.second.model);
	}
}

void AnimationController::Add(int type, const std::string& path, float speed)
{

	Animation anim;

	anim.model = MV1LoadModel(path.c_str());
	anim.animIndex = type;
	anim.speed = speed;

	if (animations_.count(type) == 0)
	{
		// ����ւ�
		animations_.emplace(type, anim);
	}
	else
	{
		// �ǉ�
		animations_[type].model = anim.model;
		animations_[type].animIndex = anim.animIndex;
		animations_[type].attachNo = anim.attachNo;
		animations_[type].totalTime = anim.totalTime;
	}

}

void AnimationController::Play(int type, bool isLoop, 
	float startStep, float endStep, bool isStop, bool isForce)
{

	if (playType_ != type || isForce) {

		if (playType_ != -1)
		{
			// ���f������A�j���[�V�������O��
			playAnim_.attachNo = MV1DetachAnim(modelId_, playAnim_.attachNo);
		}

		// �A�j���[�V������ʂ�ύX
		playType_ = type;
		playAnim_ = animations_[type];

		// ������
		playAnim_.step = startStep;

		// ���f���ɃA�j���[�V������t����
		int animIdx = 0;
		if (MV1GetAnimNum(playAnim_.model) > 1)
		{
			// �A�j���[�V�����������ۑ�����Ă�����A�ԍ�1���w��
			animIdx = 1;
		}
		playAnim_.attachNo = MV1AttachAnim(modelId_, animIdx, playAnim_.model);

		// �A�j���[�V���������Ԃ̎擾
		if (endStep > 0.0f)
		{
			playAnim_.totalTime = endStep;
		}
		else
		{
			playAnim_.totalTime = MV1GetAttachAnimTotalTime(modelId_, playAnim_.attachNo);
		}

		// �A�j���[�V�������[�v
		isLoop_ = isLoop;

		// �A�j���[�V�������Ȃ�
		isStop_ = isStop;

		stepEndLoopStart_ = -1.0f;
		stepEndLoopEnd_ = -1.0f;
		switchLoopReverse_ = 1.0f;
	}

}

void AnimationController::Update(void)
{

	// �o�ߎ��Ԃ̎擾
	float deltaTime = SceneManager::GetInstance().GetDeltaTime();

	if (!isStop_)
	{
		// �Đ�
		playAnim_.step += (deltaTime * playAnim_.speed * switchLoopReverse_);

		// �A�j���[�V�����I������
		bool isEnd = false;
		if (switchLoopReverse_ > 0.0f)
		{
			// �ʏ�Đ��̏ꍇ
			if (playAnim_.step > playAnim_.totalTime)
			{
				isEnd = true;
			}
		}
		else
		{
			// �t�Đ��̏ꍇ
			if (playAnim_.step < playAnim_.totalTime)
			{
				isEnd = true;
			}
		}

		if (isEnd)
		{
			// �A�j���[�V�������I��������
			if (isLoop_)
			{
				// ���[�v�Đ�
				if (stepEndLoopStart_ > 0.0f)
				{
					// �A�j���[�V�����I����̎w��t���[���Đ�
					switchLoopReverse_ *= -1.0f;
					if (switchLoopReverse_ > 0.0f)
					{
						playAnim_.step = stepEndLoopStart_;
						playAnim_.totalTime = stepEndLoopEnd_;
					}
					else
					{
						playAnim_.step = stepEndLoopEnd_;
						playAnim_.totalTime = stepEndLoopStart_;
					}
					playAnim_.speed = endLoopSpeed_;
					
				}
				else
				{
					// �ʏ�̃��[�v�Đ�
					playAnim_.step = 0.0f;
				}
			}
			else
			{
				// ���[�v���Ȃ�
				playAnim_.step = playAnim_.totalTime;
			}

		}

	}

	// �A�j���[�V�����ݒ�
	MV1SetAttachAnimTime(modelId_, playAnim_.attachNo, playAnim_.step);

}

void AnimationController::SetEndLoop(float startStep, float endStep, float speed)
{
	stepEndLoopStart_ = startStep;
	stepEndLoopEnd_ = endStep;
	endLoopSpeed_ = speed;
}

int AnimationController::GetPlayType(void) const
{
	return playType_;
}

bool AnimationController::IsEnd(void) const
{

	bool ret = false;

	if (isLoop_)
	{
		// ���[�v�ݒ肳��Ă���Ȃ�A
		// �������ŏI�����Ȃ���Ԃ�
		return ret;
	}

	if (playAnim_.step >= playAnim_.totalTime)
	{
		// �Đ����Ԃ��߂�����true
		return true;
	}

	return ret;

}
