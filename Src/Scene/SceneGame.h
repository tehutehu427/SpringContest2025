#pragma once
#include "SceneBase.h"

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

    //描画(デバッグ)
    void DrawDebug(void);
};

