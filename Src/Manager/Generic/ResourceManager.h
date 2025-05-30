#pragma once
#include <map>
#include <string>
#include "Resource.h"

class ResourceManager
{

public:

	// リソース名
	enum class SRC
	{
		//************************************************************
		// ここに保存しておきたい画像やモデル、音源などの名前を記す
		//************************************************************
		
		/*例*/
		TITLE_LOGO,				//タイトルロゴ
		GAMEOVER_LOGO,			//ゲームオーバー
		GAMECLEAR_LOGO,			//ゲームクリア

		SKY_DOME,				//スカイドーム
		STAGE,					//ステージモデル
		GEM,					//宝石モデル

		//敵関係
		ENEMY,					//敵モデル

		//ミニマップ関係
		MAP_FRAME,				//ミニマップ枠
		MAP_GROUND,				//ミニマップ枠内
		MAP_MASK,				//ミニマップマスク用
		MAP_IMAGE,				//ミニマップ画像
		MAP_PLAYER,				//ミニマップ用プレイヤー
		MAP_ENEMY,				//ミニマップ用敵

		//サウンド
		BGM_TITLE,				//タイトルBGM
		BGM_GAME,				//ゲームBGM
		BGM_GAMEOVER,			//ゲームオーバーBGM
		BGM_GAMECLEAR,			//ゲームクリアBGM

		SE_PUSH,				//決定音
		SE_DAMAGE,				//ダメージ音
		SE_GET,					//取得音
	};

	// 明示的にインステンスを生成する
	static void CreateInstance(void);

	// 静的インスタンスの取得
	static ResourceManager& GetInstance(void);

	// 初期化
	void Init(void);
	//タイトルで使うリソース初期化
	void InitTitle(void);
	//ゲームで使うリソース初期化
	void InitGame(void);
	//ゲームオーバーで使うリソース初期化
	void InitGameOver(void);
	//ゲームクリアで使うリソース初期化
	void InitGameClear(void);

	//プレイヤーが使うリソース
	void ResourcePlayer(void);
	//敵が使うリソース
	void ResourceEnemy(void);

	// 解放(シーン切替時に一旦解放)
	void Release(void);

	// リソースの完全破棄
	void Destroy(void);

	// リソースのロード
	Resource Load(SRC src);

	// リソースの複製ロード(モデル用)
	int LoadModelDuplicate(SRC src);

private:

	// 静的インスタンス
	static ResourceManager* instance_;

	// リソース管理の対象
	std::map<SRC, Resource> resourcesMap_;

	// 読み込み済みリソース
	std::map<SRC, Resource*> loadedMap_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	ResourceManager(void);

	// デストラクタも同様
	~ResourceManager(void) = default;

	// 内部ロード
	Resource* _Load(SRC src);

};

