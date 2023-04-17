#include "yaElevator.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaTransform.h"

namespace ya
{
	Elevator::Elevator()
	{
	}

	Elevator::~Elevator()
	{
	}

	void Elevator::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Elevator\\In", Vector2(0.0f, 0.0f), 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Elevator\\Out", Vector2(0.0f, 0.0f), 0.05f);
		
		mAnimator->Play(L"PlayerElevatorIn", false);

		GameObject::Initialize();
	}

	void Elevator::Update()
	{
		GameObject::Update();
	}

	void Elevator::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Elevator::Release()
	{
		GameObject::Release();
	}

}