#include "yaHung.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	Hung::Hung()
	{
	}
	Hung::~Hung()
	{
	}
	void Hung::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Idle\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Idle\\Right", Vector2::Zero, 0.1f);

		mAnimator->Play(L"HungIdleRight", true);

		Collider* collider = AddComponent<Collider>();

		collider->SetCenter(Vector2(-60.0f, -80.0f));
		GameObject::Initialize();
	}
	void Hung::Update()
	{
		GameObject::Update();
	}
	void Hung::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Hung::Release()
	{
		GameObject::Release();
	}
}