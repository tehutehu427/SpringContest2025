#pragma once
#include<DxLib.h>
#include<string>

class StageUiFont
{
private:
	static StageUiFont* instance_;    //�V���O���g���C���X�^���X
	int fontHanble_;				  //�t�H���g�n���h��
	int fontSize_;                    //�t�H���g�T�C�Y
	int fontType_;					  //�t�H���g�^�C�v
	int fontWeight_;				  //�t�H���g�̑���
	StageUiFont();					  //�R���X�g���N�^�̓v���C�x�[�g
public:
	//�t�H���g�̒l
	static constexpr int FONT_TYPE_NORMAL = DX_FONTTYPE_NORMAL;                             //�ʏ�̃t�H���g
	static constexpr int FONT_TYPE_EDGE = DX_FONTTYPE_EDGE;                                 //�����t�H���g
	static constexpr int FONT_TYPE_ANTIALIASING = DX_FONTTYPE_ANTIALIASING;                 //�A���`�G�C���A�X�t�H���g
	static constexpr int FONT_TYPE_ANTIALIASING_EDGE = DX_FONTTYPE_ANTIALIASING_EDGE;       //�A���`�G�C���A�X + �����t�H���g

	~StageUiFont();					  //�f�X�g���N�^
	static StageUiFont& GetInstance();//�C���X�^���X�擾
	bool Init();					  //�t�H���g�̏�����
	void Update();					  //�t�H���g�X�V����
	void SetFontSize(int _fontSize);  //�t�H���g�T�C�Y�̐ݒ�	
	void SetFontType(int _fontType);  //�t�H���g�^�C�v�̐ݒ�
	void SetFontWeight(int _fontWeight);//�t�H���g�̑����ݒ�
	void DrawText(int _x, int _y, const char* _text, int _color, int _fontSize, int _fontType, int _fontWeight);//�e�L�X�g�`��
};