#pragma once
#include "Fader.h"
#include "Vector2.h"

class ImageFader:public Fader
{
public:

	//�`��(�����ŉ摜�̏���ǂݍ���)
	void Draw(int img, Vector2 pos, float scl, float angle, bool trans, bool reverse);

};

