#pragma once

#include<memory>
#include "SceneBase.h"
#include"../Application.h"

class SkyDome;
class Stage;
class Player;
class EnemyManager;
class ItemManager;
class MiniMap;

class SceneGame : public SceneBase
{
public:

    //流れるバナーの大きさ
    static constexpr int SCROLL_BANNER_SIZE_X = 600;
    static constexpr int SCROLL_BANNER_SIZE_Y = 200;

    //流れるバナーの出ている時間
    static constexpr float SCROLL_BANNER_TIME = Application::DEFAULT_FPS * 6.0f;


    //コンストラクタ
    SceneGame();

    //デストラクタ
    ~SceneGame() = default;

    //初期化
    void Init(void)override;
    //更新
    void Update(void)override;
    //描画
    void Draw(void)override;
    //解放
    void Release(void)override;

private:

    //スカイドーム
    std::unique_ptr<SkyDome> skyDome_;

    //ステージ
    std::unique_ptr<Stage> stage_;

    //プレイヤー
    std::unique_ptr<Player> player_;

    //敵マネージャー
    std::unique_ptr<EnemyManager> enmMng_;

    //アイテムマネージャー
    std::unique_ptr<ItemManager> itemMng_;

    //ミニマップ
    std::unique_ptr<MiniMap> miniMap_;

    //バナー用
    float scrollBannerPos_;
    float scrollBannerTime_;

    //描画(デバッグ)
    void DrawDebug(void);

    /// <summary>
    /// 流れるバナー
    /// </summary>
    /// <param name=""></param>
    /// <returns>流れ中</returns>
    bool ScrollBanner(void);

    //当たり判定
    void Collision(void);

    //プレイヤーの当たり判定
    void CollisionPlayer(void);
    //プレイヤーの当たり判定
    void CollisionEnemy(void);

    //ゲームのクリア処理
    void GameClear(void);

    //ゲームオーバー処理
    void GameOver(void);
};