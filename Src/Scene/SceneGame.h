#pragma once

#include<memory>
#include "SceneBase.h"

class Stage;
class Player;
class EnemyManager;
class ItemManager;

class SceneGame : public SceneBase
{
public:

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

    //ステージ
    std::unique_ptr<Stage> stage_;

    //プレイヤー
    std::unique_ptr<Player> player_;

    //敵マネージャー
    std::unique_ptr<EnemyManager> enmMng_;

    //アイテムマネージャー
    std::unique_ptr<ItemManager> itemMng_;

    //描画(デバッグ)
    void DrawDebug(void);
};

