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

    //モデルハンドルを返す
    const int GetModelId(void) { return model_.GetModelId(); }
    
    //座標を返す
    const VECTOR& GetPos(void) { return model_.GetPos(); }

    //回転を返す
    const VECTOR& GetRot(void) { return model_.GetRot(); }

    //大きさを返す
    const VECTOR& GetScl(void) { return model_.GetScl(); }

};

