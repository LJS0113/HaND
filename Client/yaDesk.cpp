#include "yaDesk.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTime.h"

namespace ya
{
	Desk::Desk()
		: mTime(0.0f)
	{
	}
	Desk::~Desk()
	{
	}
	void Desk::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Intro\\Desk", Vector2(0.0f, 0.0f), 0.1f);
		mAnimator->Play(L"BradIntroDesk", false);

		GameObject::Initialize();
	}

	void Desk::Update()
	{
		GameObject::Update();


	}
	void Desk::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Desk::Release()
	{
		GameObject::Release();
	}
	void Desk::OnCollisionEnter(Collider* other)
	{
	}
	void Desk::OnCollisionStay(Collider* other)
	{
	}
	void Desk::OnCollisionExit(Collider* other)
	{
	}
	void Desk::play()
	{
	}
}