#pragma once

#include <DxLib.h>
#include "StageModelLoader.h"

class Stage {
private:
    StageModelLoader model_;

public:
    Stage();  // コンストラクタ
    ~Stage(); // デストラクタ

    bool Init();    // 初期化処理
    void Update();  // 更新処理
    void Draw();    // 描画処理
};

