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
    //四角形１の全方向
    float box1Front = _box1.y - (_box1Range / 2.0f);
    float box1Bottom = _box1.y + (_box1Range / 2.0f);
    float box1Right = _box1.x + (_box1Range / 2.0f);
    float box1Left = _box1.x - (_box1Range / 2.0f);

    //四角形２の全方向
    float box2Front = _box2.y - (_box2Range / 2.0f);
    float box2Bottom = _box2.y + (_box2Range / 2.0f);
    float box2Right = _box2.x + (_box2Range / 2.0f);
    float box2Left = _box2.x - (_box2Range / 2.0f);
    
    return (box1Left < box2Right && box1Right > box2Left &&
        box1Front < box2Bottom && box1Bottom > box2Front);
}

bool Collision::IsHitSpheres(const VECTOR& pos1, float radius1, const VECTOR& pos2, float radius2)
{
    // 球体同士の衝突判定
    bool ret = false;

    // お互いの半径の合計
    float radius = radius1 + radius2;

    // 座標の差からお互いの距離を取る
    VECTOR diff = VSub(pos2, pos1);

    // 三平方の定理で比較(SqrMagnitudeと同じ)
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

    // カプセル球体の中心を繋ぐベクトル
    VECTOR cap1to2 = VSub(capPos2, capPos1);

    // ベクトルを正規化
    VECTOR cap1to2ENor = VNorm(cap1to2);

    // カプセル繋ぎの単位ベクトルと、
    // そのベクトル元から球体へのベクトルの内積を取る
    float dot = VDot(cap1to2ENor, VSub(sphPos, capPos1));

    // 内積で求めた射影距離を使って、カプセル繋ぎ上の座標を取る
    VECTOR capRidePos = VAdd(capPos1, VScale(cap1to2ENor, dot));

    // カプセル繋ぎのベクトルの長さを取る
    float len = AsoUtility::MagnitudeF(cap1to2);

    // 球体がカプセル繋ぎ上にいるか判別するため、比率を取る
    float rate = dot / len;

    VECTOR centerPos;

    // 球体の位置が３エリアに分割されたカプセル形状のどこにいるか判別
    if (rate > 0.0f && rate <= 1.0f)
    {
        // ①球体がカプセル繋ぎ上にいる
        centerPos = VAdd(capPos1, VScale(cap1to2ENor, dot));
    }
    else if (rate > 1.0f)
    {
        // ②球体がカプセルの終点側にいる
        centerPos = capPos2;
    }
    else if (rate < 0.0f)
    {
        // ③球体がカプセルの始点側にいる
        centerPos = capPos1;
    }
    else
    {
        // ここにきてはいけない
    }

    // 球体同士の当たり判定
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

    //衝突判定
    auto info = MV1CollCheck_Sphere(_modelId, -1, _pos, _radius, -1);
    if (info.HitNum > 0)
    {
        ret = true;
    }

    // 検出した地面ポリゴン情報の後始末
    MV1CollResultPolyDimTerminate(info);
    return ret;
}