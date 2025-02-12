#include<DxLib.h>
#include<string>
#include"../Generic/ResourceManager.h"
#include "Timer.h"

Timer* Timer::instance_ = nullptr;

Timer::Timer(void)
{

}

Timer::~Timer(void)
{

}

void Timer::CreateInstance(void)
{
	if (instance_ != nullptr)return;
	instance_ = new Timer();
}

Timer& Timer::GetInstance(void)
{
	return *instance_;
}

void Timer::CntUp(float _value) const
{
	_value += SceneManager::GetInstance().GetDeltaTime();
}

void Timer::CntDown(float _value) const
{
	_value -= SceneManager::GetInstance().GetDeltaTime();
}

void Timer::Update()
{

}

void Timer::Draw()
{

}

void Timer::Reset()
{

}


void Timer::ReduceTime(void)
{

}