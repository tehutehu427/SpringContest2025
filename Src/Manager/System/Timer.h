#pragma once
#include"../Generic/SceneManager.h"

class Timer
{
public:

	void Update();
	void Draw();
	void Reset();	//デバッグ用

	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static Timer& GetInstance(void);

	/// <summary>
	/// デルタタイムでカウントアップ
	/// </summary>
	/// <param name="_value">アップさせる値</param>
	void CntUp(float& _value)const;
	
	/// <summary>
	/// デルタタイムでカウントダウン
	/// </summary>
	/// <param name="_value">アップさせる値</param>
	void CntDown(float& _value)const;

private:

	static Timer* instance_;
	
	void ReduceTime(void);

	Timer(void);
	~Timer(void);
};