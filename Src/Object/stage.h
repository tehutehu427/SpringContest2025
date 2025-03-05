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
};

