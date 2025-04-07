#pragma once

#include<memory>
#include "SceneBase.h"

class titleUi;

class SceneGameClear : public SceneBase
{
public:

    //コンストラクタ
    SceneGameClear();

    //デストラクタ
    ~SceneGameClear() = default;

    //初期化
    void Init(void)override;
    //更新
    void Update(void)override;
    //描画
    void Draw(void)override;
    //解放
    void Release(void)override;

private:

    //ゲームオーバーロゴ
    int logo_;

    //UI
    std::unique_ptr<titleUi> ui_;

    //描画(デバッグ)
    void DrawDebug(void);
};

