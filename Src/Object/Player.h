#pragma once
#include "UnitBase.h"
class Player : public UnitBase
{

	//列挙型
	enum class DIRECTION
	{
		NORTH,
		EAST,
		SOUTH,
		WEST
	};

	

public:

	//プレイヤーサイズ
	static constexpr float RADIUS = 40.0f;
	//プレイヤースピード
	static constexpr float SPEED = 3.0f;

	//体力バー関係
	static constexpr int HP_MAX = 3;			//最大体力
	static constexpr float BAR_POS_X = 300.0f;	//バーのX位置
	static constexpr float BAR_POS_Y = 30.0f;	//バーのY一
	static constexpr float DIFF_POS = 2.0f;		//バー枠との差

	//宝石取得関係
	static constexpr int ITEM_NUM = 5;					//必要宝石取得個数
	static constexpr float GEM_POS_X = 20.0f;			//宝石表示の開始X位置
	static constexpr float GEM_POS_Y = 60.0f;			//宝石表示の開始Y位置
	static constexpr float GEM_SIZE_X = 10.0f;			//宝石の横の大きさ
	static constexpr float GEM_SIZE_Y = 20.0f;			//宝石の縦の大きさ
	static constexpr float GEM_INTERVAL_POS = 15.0f;	//宝石の表示間隔

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

	/// <summary>
	/// ステージとの衝突判定
	/// </summary>
	/// <param name="stageModelId">ステージのモデルID</param>
	/// <returns>当たったかどうか(true:当たった)</returns>
	bool CollisionStage(const int& _stageModelId);

	//アイテム取得数を増加
	void AddItemNum(void) { itemNum_++; }

	//体力を下げる
	void SubHp(void) { hp_--; }

	//アイテム取得数を取得
	const int GetItemNum(void) { return itemNum_; }

	//生存判定
	bool IsAlive(void) { return hp_ > 0; }

	//体力バー描画
	void DrawHPBar(void);

	//宝石取得数描画
	void DrawGotGem(void);

private:
	
	VECTOR axis_;
	DIRECTION direction_;
	
	//アイテム取得数
	int itemNum_;

	//体力
	int hp_;

};

