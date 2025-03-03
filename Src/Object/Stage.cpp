#include<DxLib.h>
#include"../Utility/AsoUtility.h"
#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init(void)
{
	//�ϐ��̏�����
	trans_ = Transform();
	//trans_.modelId = 
	trans_.quaRot = Quaternion();
	trans_.quaRotLocal = Quaternion::AngleAxis(AsoUtility::Deg2RadF(180.0f), AsoUtility::AXIS_Y);

	//���f������
	trans_.Update();
}

void Stage::Update(void)
{
	//���f������
	trans_.Update();
}

void Stage::Draw(void)
{
	//���f���`��
	MV1DrawModel(trans_.modelId);
}

void Stage::Release(void)
{
}
