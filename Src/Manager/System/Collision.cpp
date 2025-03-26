#include"../../Utility/AsoUtility.h"
#include "Collision.h"

Collision* Collision::instance_ = nullptr;


void Collision::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new Collision();
    }
}

Collision& Collision::GetInstance(void)
{
    return *instance_;
}

void Collision::Init(void)
{
   
}

bool Collision::IsHitBoxes(const Vector2F _box1, const float _box1Range, const Vector2F _box2, const float _box2Range)const
{
    //�l�p�`�P�̑S����
    float box1Front = _box1.y - (_box1Range / 2.0f);
    float box1Bottom = _box1.y + (_box1Range / 2.0f);
    float box1Right = _box1.x + (_box1Range / 2.0f);
    float box1Left = _box1.x - (_box1Range / 2.0f);

    //�l�p�`�Q�̑S����
    float box2Front = _box2.y - (_box2Range / 2.0f);
    float box2Bottom = _box2.y + (_box2Range / 2.0f);
    float box2Right = _box2.x + (_box2Range / 2.0f);
    float box2Left = _box2.x - (_box2Range / 2.0f);
    
    return (box1Left < box2Right && box1Right > box2Left &&
        box1Front < box2Bottom && box1Bottom > box2Front);
}

bool Collision::IsHitSpheres(const VECTOR& pos1, float radius1, const VECTOR& pos2, float radius2)
{
    // ���̓��m�̏Փ˔���
    bool ret = false;

    // ���݂��̔��a�̍��v
    float radius = radius1 + radius2;

    // ���W�̍����炨�݂��̋��������
    VECTOR diff = VSub(pos2, pos1);

    // �O�����̒藝�Ŕ�r(SqrMagnitude�Ɠ���)
    float dis = (diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z);
    if (dis < (radius * radius))
    {
        ret = true;
    }

    return ret;
}

bool Collision::IsHitSphereCapsule(const VECTOR& sphPos, float sphRadius, const VECTOR& capPos1, const VECTOR& capPos2, float capRadius)
{
    bool ret = false;

    // �J�v�Z�����̂̒��S���q���x�N�g��
    VECTOR cap1to2 = VSub(capPos2, capPos1);

    // �x�N�g���𐳋K��
    VECTOR cap1to2ENor = VNorm(cap1to2);

    // �J�v�Z���q���̒P�ʃx�N�g���ƁA
    // ���̃x�N�g�������狅�̂ւ̃x�N�g���̓��ς����
    float dot = VDot(cap1to2ENor, VSub(sphPos, capPos1));

    // ���ςŋ��߂��ˉe�������g���āA�J�v�Z���q����̍��W�����
    VECTOR capRidePos = VAdd(capPos1, VScale(cap1to2ENor, dot));

    // �J�v�Z���q���̃x�N�g���̒��������
    float len = AsoUtility::MagnitudeF(cap1to2);

    // ���̂��J�v�Z���q����ɂ��邩���ʂ��邽�߁A�䗦�����
    float rate = dot / len;

    VECTOR centerPos;

    // ���̂̈ʒu���R�G���A�ɕ������ꂽ�J�v�Z���`��̂ǂ��ɂ��邩����
    if (rate > 0.0f && rate <= 1.0f)
    {
        // �@���̂��J�v�Z���q����ɂ���
        centerPos = VAdd(capPos1, VScale(cap1to2ENor, dot));
    }
    else if (rate > 1.0f)
    {
        // �A���̂��J�v�Z���̏I�_���ɂ���
        centerPos = capPos2;
    }
    else if (rate < 0.0f)
    {
        // �B���̂��J�v�Z���̎n�_���ɂ���
        centerPos = capPos1;
    }
    else
    {
        // �����ɂ��Ă͂����Ȃ�
    }

    // ���̓��m�̓����蔻��
    if (IsHitSpheres(centerPos, capRadius, sphPos, sphRadius))
    {
        ret = true;
    }
    else
    {
        ret = false;
    }

    return ret;
}

const bool Collision::IsHitUnitStageObject(const int& _modelId, const VECTOR& _pos, const float& _radius) const
{
    bool ret = false;

    //�Փ˔���
    auto info = MV1CollCheck_Sphere(_modelId, -1, _pos, _radius, -1);
    if (info.HitNum > 0)
    {
        ret = true;
    }

    // ���o�����n�ʃ|���S�����̌�n��
    MV1CollResultPolyDimTerminate(info);
    return ret;
}