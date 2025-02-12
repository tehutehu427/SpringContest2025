#pragma once

class Vector2
{
public:

	int x;
	int y;

	// �R���X�g���N�^
	Vector2(void);

	// �R���X�g���N�^
	Vector2(int vX, int vY);

	// �f�X�g���N�^
	~Vector2(void);

	//���Z

	Vector2 operator+(const Vector2 value)const;
	void operator+=(const Vector2 value);
	Vector2 operator-(const Vector2 value)const;
	void operator-=(const Vector2 value);
	Vector2 operator*(const int value)const;
	void operator*=(const int value);
	Vector2 operator/(const int value)const;
	void operator/=(const int value);
};

class Vector2F
{
public:

	float x;
	float y;

	//�R���X�g���N�^
	Vector2F(void);

	//�R���X�g���N�^
	Vector2F(float vX, float vY);

	//�f�X�g���N�^
	~Vector2F(void);

	//���Z

	Vector2F operator+(const Vector2F value)const;
	void operator+=(const Vector2F value);
	Vector2F operator-(const Vector2F value)const;
	void operator-=(const Vector2F value);
	Vector2F operator*(const float value)const;
	void operator*=(const float value);
	Vector2F operator/(const float value)const;
	void operator/=(const float value);
};