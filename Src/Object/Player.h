#pragma once
#include "UnitBase.h"
class Player : public UnitBase
{

	//列挙型
	enum class DIRECTION
	{
		FRONT,
		LEFT,
		RIGHT,
		BACK,
		MAX
	};

public:

	//プレイヤーサイズ
	static constexpr int SIZE = 10;
	//プレイヤースピード
	static constexpr int SPEED = 1;


	//コンストラクタ
	Player();
	//デストラクタ
	~Player()override;

	//初期化
	void Init(void)override;
	//更新
	void Update(void)override;
	//描画
	void Draw(void)override;
	//解放
	void Release(void)override;

private:
	
	VECTOR axis_;
	DIRECTION direction_;
	
};

