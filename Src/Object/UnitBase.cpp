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
	movePow_ = AsoUtility::VECTOR_ZERO;
}

UnitBase::~UnitBase()
{
}


void UnitBase::Turn(const float _deg, const VECTOR& _axis)
{
	trans_.quaRot =
		trans_.quaRot.Mult(trans_.quaRot, (Quaternion::AngleAxis(AsoUtility::Deg2RadF(_deg), _axis)));
}

void UnitBase::InitAnimation(void)
{

}
