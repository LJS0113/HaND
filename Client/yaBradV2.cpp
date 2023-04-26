#include "yaBradV2.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTransform.h"
#include "yaColliderObj.h"
#include "yaObject.h" 

namespace ya
{
	BradV2::BradV2()
		: mbLeft(true)
		, mbRight(false)
	{
	}

	BradV2::~BradV2()
	{
	}

	void BradV2::Initialize()
	{
		mAnimator = AddComponent<Animator>();

		// Idle
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Idle\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Idle\\Right", Vector2::Zero, 0.1f);

		// Intro
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Intro", Vector2::Zero, 0.001f);

		// Move
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Move\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Move\\Right", Vector2::Zero, 0.1f);

		// Death
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Death", Vector2::Zero, 0.1f);

		// Attack
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack1\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack1\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack2\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack2\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack3\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack3\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack4\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack4\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack5\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack5\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack6\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack6\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack3_Alt\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack3_Alt\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack4_Alt\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack4_Alt\\Right", Vector2::Zero, 0.1f);

		mAnimator->Play(L"MonsterBradV2Intro", false);

		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-60.0f, -80.0f));

		GameObject::Initialize();
	}

	void BradV2::Update()
	{
		GameObject::Update();
		switch (mState)
		{
		case ya::BradV2::eBradV2State::Move:
			move();
			break;
		case ya::BradV2::eBradV2State::Intro:
			intro();
			break;
		case ya::BradV2::eBradV2State::Attack:
			attack();
			break;
		case ya::BradV2::eBradV2State::Death:
			death();
			break;
		case ya::BradV2::eBradV2State::Idle:
			idle();
			break;
		default:
			break;
		}
	}

	void BradV2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BradV2::Release()
	{
		GameObject::Release();
	}

	void BradV2::intro()
	{
		if (mAnimator->IsComplete())
		{
			if (mbLeft)
			{
				mAnimator->Play(L"BradV2IdleLeft", true);
				mState = eBradV2State::Idle;
			}
			if (mbRight)
			{
				mAnimator->Play(L"BradV2IdleRight", true);
				mState = eBradV2State::Idle;
			}
		}
	}

	void BradV2::death()
	{
	}

	void BradV2::idle()
	{
		collider->SetCenter(Vector2(-80.0f, -200.0f));
		collider->SetSize(Vector2(170.0f, 200.0f));

	}

	void BradV2::attack()
	{
	}

	void BradV2::move()
	{
	}

} 