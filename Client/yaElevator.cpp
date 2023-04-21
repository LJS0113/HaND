#include "yaElevator.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaTransform.h"
#include "yaCollider.h"

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
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Map\\Elevator\\In", Vector2(0.0f, 0.0f), 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Map\\Elevator\\Out", Vector2(0.0f, 0.0f), 0.05f);
		
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-25.0f, -250.0f));
		collider->SetSize(Vector2(80.0f, 200.0f));

		mAnimator->Play(L"MapElevatorIn", false);

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