#include "yaHung.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"
#include "yaTransform.h"
#include "yaInput.h"
#include "yaComponent.h"
#include "yaGameObject.h"
#include "yaPlayer.h"
#include "yaLayer.h"
#include "yaScene.h"
#include "yaTime.h"

namespace ya
{
	Hung::Hung()
		: mbLeft(true)
		, mbRight(false)
	{
	}
	Hung::~Hung()
	{
	}
	void Hung::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		// Idlen
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Idle\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Idle\\Right", Vector2::Zero, 0.1f);

		// Attack
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\AttackLasso\\Right\\Throw", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\AttackLasso\\Right\\Success", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\AttackLasso\\Left\\Throw", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\AttackLasso\\Left\\Success", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\AttackMelee\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\AttackMelee\\Right", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\AttackSpecial\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\AttackSpecial\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\AttackSpecial\\FX", Vector2::Zero, 0.1f);

		// Death
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Death", Vector2::Zero, 0.1f);

		// Intro
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Intro\\Start", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Intro\\Loop", Vector2::Zero, 0.1f);

		// Run
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Run\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Run\\Left", Vector2::Zero, 0.1f);

		mAnimator->Play(L"HungIdleLeft", true);
		mState = eHungState::Idle;

		Collider* collider = AddComponent<Collider>();

		//mRigidbody = AddComponent<Rigidbody>();
		//mRigidbody->SetMass(1.0f);

		collider->SetCenter(Vector2(-200.0f,-200.0f));
		collider->SetSize(Vector2(mAnimator->GetSize().x, mAnimator->GetSize().y));

		GameObject::Initialize();

		//Transform* playerTr = mPlayer->GetComponent<Transform>();
	}
	void Hung::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ya::Hung::eHungState::Move:
			move();
			break;
		case ya::Hung::eHungState::Attack:
			attack();
			break;
		case ya::Hung::eHungState::Death:
			death();
			break;
		case ya::Hung::eHungState::Idle:
			idle();
			break;
		default:
			break;
		}
	}
	void Hung::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Hung::Release()
	{
		GameObject::Release();
	}
	void Hung::move()
	{
		Vector2 playerPos =	mPlayer->GetPos();

		int a = 0;
	}
	void Hung::death()
	{
	}
	void Hung::idle()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		//Vector2 velocity = mRigidbody->GetVelocity();
		std::srand((unsigned int)time(NULL));
		rand = (std::rand() % 3) + 1;

		mTime += Time::DeltaTime();


		if (mTime > 3.0f)
		{

			switch (rand)
			{
			case 1:
				mAnimator->Play(L"HungAttackSpecialRight", false);
				rand = (std::rand() % 1023) + 1;

				break;
			case 2:
				mAnimator->Play(L"AttackLassoRightThrow", false);
				break;
			case 3:
				mAnimator->Play(L"HungAttackMeleeRight", false);
				break;
			default:
				break;
			}
			mState = eHungState::Attack;
			mTime = 0;
		}
		tr->SetPos(pos);
	}
	void Hung::attack()
	{
		if (mAnimator->IsComplete() && mbRight)
		{
			mAnimator->Play(L"HungIdleRight", true);
			mState = eHungState::Idle;
		}
		if (mAnimator->IsComplete() && mbLeft)
		{
			mAnimator->Play(L"HungIdleLeft", true);
			mState = eHungState::Idle;
		}
	}
}