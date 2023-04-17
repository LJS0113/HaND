#include "yaBrad.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaInput.h"

namespace ya
{
	Brad::Brad()
	{
	}

	Brad::~Brad()
	{
	}

	void Brad::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		
		// Idle
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Idle\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Idle\\Right", Vector2::Zero, 0.1f);

		// Attack
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Attack1\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Attack1\\Left", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Dive\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Dive\\Left", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Fly_Stomp\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Fly_Stomp\\Left", Vector2::Zero, 0.1f);



		mAnimator->Play(L"BradIdleRight", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-60.0f, -80.0f));

		GameObject::Initialize();
	}

	void Brad::Update()
	{
		GameObject::Update();


		if (Input::GetKeyDown(eKeyCode::I))
		{
			mAnimator->Play(L"BradAttack1Right", false);
		}
		if (Input::GetKeyDown(eKeyCode::O))
		{
			mAnimator->Play(L"BradDiveRight", false);
		}
		if (Input::GetKeyDown(eKeyCode::P))
		{
			mAnimator->Play(L"BradFly_StompRight", false);
		}
	}

	void Brad::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Brad::Release()
	{
		GameObject::Release();
	}

}