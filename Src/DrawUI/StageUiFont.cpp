#include<DxLib.h>
#include"StageUiFont.h"

//�V���O���g���C���X�^���X�̏�����
StageUiFont* StageUiFont::instance_ = nullptr;

//�R���X�g���N�^
StageUiFont::StageUiFont() : fontHanble_(-1), fontSize_(24), fontType_(DX_FONTTYPE_ANTIALIASING_EDGE), fontWeight_(3){}

//�f�X�g���N�^
StageUiFont::~StageUiFont()
{
	if (fontHanble_ != -1 && fontHanble_ != DX_DEFAULT_FONT_HANDLE)
	{
		DeleteFontToHandle(fontHanble_);		//�t�H���g�n���h���̉��
	}
}

//�V���O���g���C���X�^���X�擾
StageUiFont& StageUiFont::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new StageUiFont();
	}
	return *instance_;
}

//�t�H���g������
bool StageUiFont::Init()
{
	int fontFileSize = FileRead_size("�����Ƀt�H���g�t�@�C��(.ttf)�̃t�@�C���p�X");		//�t�H���g�t�@�C���̃T�C�Y
	int fontFileHandle = FileRead_open("�����Ƀt�H���g�t�@�C��(.ttf)�̃t�@�C���p�X");	//�t�H���g�t�@�C�����J��

	//�t�H���g�ǂݍ��ݎ��s����
	if (fontFileSize <= 0 || fontFileHandle == -1)
	{
		OutputDebugString("�t�H���g�t�@�C����������܂���B");
		fontHanble_ = DX_DEFAULT_FONT_HANDLE;
		return false;
	}

	//�t�H���g�f�[�^���������ɓǂݍ���
	void* Buffer = new char[fontFileSize];
	FileRead_read(Buffer, fontFileSize, fontFileHandle);

	DWORD font_num = 0;
	if (AddFontMemResourceEx(Buffer, fontFileSize, NULL, &font_num) == 0)
	{
		OutputDebugString("�t�H���g�t�@�C�����ǂݍ��߂܂���ł����B\n");
		delete[] Buffer;
		fontHanble_ = DX_DEFAULT_FONT_HANDLE;
		return false;
	}

	FileRead_close(fontFileHandle);		//�t�H���g�t�@�C�������
	delete[] Buffer;					//���������

	//�t�H���g�n���h���𐶐�
	fontHanble_ = CreateFontToHandle("�����Ƀt�H���g�t�@�C��(.ttf)�̃t�@�C���p�X", fontSize_, fontWeight_, DX_FONTTYPE_ANTIALIASING_EDGE);
	if (fontHanble_ == -1)
	{
		fontHanble_ = DX_DEFAULT_FONT_HANDLE;
	}
	return(fontHanble_ != DX_DEFAULT_FONT_HANDLE);

}

//�t�H���g�X�V����
void StageUiFont::Update()
{
	if (fontHanble_ != -1 && fontHanble_ != DX_DEFAULT_FONT_HANDLE)
	{
		DeleteFontToHandle(fontHanble_);
	}
	fontHanble_ = CreateFontToHandle("�����Ƀt�H���g�t�@�C��(.ttf)�̃t�@�C���p�X", fontSize_, fontWeight_, fontType_);
	if (fontHanble_ == -1)
	{
		fontHanble_ = DX_DEFAULT_FONT_HANDLE;
	}
}

//�t�H���g�T�C�Y�̐ݒ�
void StageUiFont::SetFontSize(int _fontSize)
{
	if (fontSize_ != _fontSize)
	{
		fontSize_ = _fontSize;
		Update();
	}
}

//�t�H���g�^�C�v�̐ݒ�
void StageUiFont::SetFontType(int _fontType)
{
	if (fontType_ != _fontType)
	{
		fontType_ = _fontType;
		Update();
	}
}

//�t�H���g�����̐ݒ�
void StageUiFont::SetFontWeight(int _fontWeight)
{
	if (fontWeight_ != _fontWeight)
	{
		fontWeight_ = _fontWeight;
		Update();
	}
}

//�e�L�X�g�`��
void StageUiFont::DrawText(int _x, int _y, const char* _text, int _color, int _fontSize, int _fontType, int _fontWeight)
{
	SetFontSize(_fontSize);
	SetFontType(_fontType);
	SetFontWeight(_fontWeight);
	if (fontHanble_ != -1)
	{
		DrawFormatStringToHandle(_x, _y, _color, fontHanble_, _text);
	}
}