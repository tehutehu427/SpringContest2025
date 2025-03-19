#pragma once
#include <string>
#include<windows.h>

//#define DEBUG_SCREEN

class Application
{

public:
#ifdef DEBUG_SCREEN
	static constexpr int SCREEN_SIZE_X = 800;
	static constexpr int SCREEN_SIZE_Y = 600;
	// スクリーンサイズ

	//static constexpr int SCREEN_SIZE_X = 1920;
	//static constexpr int SCREEN_SIZE_Y = 1080;
#endif // DEBUG_SCREEN

	static constexpr int DEFA_SCREEN_SIZE_X = 1920;
	static constexpr int DEFA_SCREEN_SIZE_Y = 1080;

	static constexpr int SCREEN_SIZE_X = 800;
	static constexpr int SCREEN_SIZE_Y = 600;

	//FPS
	static constexpr int DEFAULT_FPS = 60;
	static constexpr float FRAME_RATE = 1000 / 60;

	// データパス関連
	//-------------------------------------------
	static const std::string PATH_IMAGE;
	static const std::string PATH_MODEL;
	static const std::string PATH_EFFECT;
	static const std::string PATH_TEXT;
	static const std::string PATH_FONT;
	static const std::string PATH_JSON;
	static const std::string PATH_BGM;
	static const std::string PATH_SE;
	//-------------------------------------------

	// 明示的にインステンスを生成する
	static void CreateInstance(void);

	// 静的インスタンスの取得
	static Application& GetInstance(void);

	// 初期化
	void Init(void);

	// ゲームループの開始
	void Run(void);

	// リソースの破棄
	void Destroy(void);

	// 初期化成功／失敗の判定
	bool IsInitFail(void) const;

	// 解放成功／失敗の判定
	bool IsReleaseFail(void) const;

private:

	// 静的インスタンス
	static Application* instance_;

	// 初期化失敗
	bool isInitFail_;

	// 解放失敗
	bool isReleaseFail_;

	//エフェクシアの初期化
	void InitEffekseer(void);

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	Application(void);

	// コピーコンストラクタも同様
	Application(const Application&);

	// デストラクタも同様
	~Application(void) = default;

	//フレームレート関連
	//---------------------------------
	int currentFrame_;	//現在のフレームを保存
	int lastFrame_;		//最後に実行したフレームを保存

	int frameCnt_ = 0;				//フレームカウント用
	int updateFrameRateTime_ = 0;	//フレームレートを更新した時間

	float frameRate_ = 0.f;			//フレームレート(表示用)

	bool isDrawFrameRate_ = false;	//フレームレートの表示フラグ(true:表示)

	//フレームレート計算
	void CalcFrameRate();

	//フレームレート表示(デバッグ用)
	void DrawFrameRate();
};