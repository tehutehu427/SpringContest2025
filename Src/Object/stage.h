#pragma once

#include <DxLib.h>
#include "StageModelLoader.h"

class Stage {
private:
    StageModelLoader model_;

public:
    Stage();  // �R���X�g���N�^
    ~Stage(); // �f�X�g���N�^

    bool Init();    // ����������
    void Update();  // �X�V����
    void Draw();    // �`�揈��

    //���f���n���h����Ԃ�
    const int GetModelId(void) { return model_.GetModelId(); }
    
    //���W��Ԃ�
    const VECTOR& GetPos(void) { return model_.GetPos(); }

    //��]��Ԃ�
    const VECTOR& GetRot(void) { return model_.GetRot(); }

    //�傫����Ԃ�
    const VECTOR& GetScl(void) { return model_.GetScl(); }

};

