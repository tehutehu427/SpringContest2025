#pragma once
#include "SceneBase.h"

class SceneGameOver : public SceneBase
{
public:

    //コンストラクタ
    SceneGameOver();

    //デストラクタ
    ~SceneGameOver() = default;

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

