#pragma once
#include "yaBrad.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaTransform.h"
#include "yaPlayer.h"
#include "yaObject.h"

namespace ya
{
	Brad::Brad()
		: mbLeft(true)
		, mbRight(false)
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

		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Intro\\Intro", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Intro\\Desk", Vector2::Zero, 0.1f);

		// Attack
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Attack1\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Attack1\\Left", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Dive\\Right\\Anticipation", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Dive\\Right\\Loop", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Dive\\Right\\End", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Dive\\Left\\Anticipation", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Dive\\Left\\Loop", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Dive\\Left\\End", Vector2::Zero, 0.1f);

		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Fly_Stomp\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Fly_Stomp\\Left", Vector2::Zero, 0.1f);

		mAnimator->Play(L"BradIntroIntro", false);


		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-80.0f, -200.0f));
		collider->SetSize(Vector2(170.0f, 200.0f));

		GameObject::Initialize();
	}

	void Brad::Update()
	{
		GameObject::Update();
		if (mAnimator->IsComplete())
		{
			mAnimator->Play(L"BradIdleLeft", true);
			mState = eBradState::Idle;
		}
		GameObject::Update();

		switch (mState)
		{
		case ya::Brad::eBradState::Attack:
			attack();
			break;
		case ya::Brad::eBradState::Death:
			death();
			break;
		case ya::Brad::eBradState::Idle:
			idle();
			break;
		default:
			break;
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


	void Brad::death()
	{
	}

	void Brad::idle()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		std::srand((unsigned int)time(NULL));
		rand = (std::rand() % 3) + 1;

		mTime += Time::DeltaTime();

		// 몬스터가 플레이어보다 오른쪽에 있을때, 왼쪽을 바라보고 왼쪽으로 이동.
		if (monsterPos.x > playerPos.x)
		{
			mbLeft = true;
			mbRight = false;
			monsterPos.x -= 200 * Time::DeltaTime();
			//mAnimator->Play(L"HungRunLeft", true);

			if (mTime > 2.0f)
			{
				switch (rand)
				{
				case 1:
					mAnimator->Play(L"BradAttack1Left", false);

					break;
				case 2:
					mAnimator->Play(L"BradDiveLeft", false);
					collider->SetCenter(Vector2(-420.0f, -140.0f));
					collider->SetSize(Vector2(320.0f, 140.0f));
					break;
				case 3:
					mAnimator->Play(L"BradFly_StompLeft", false);
					collider->SetCenter(Vector2(-330.0f, -230.0f));
					collider->SetSize(Vector2(430.0f, 230.0f));
					break;
				default:
					break;
				}
				mState = eBradState::Attack;
				mTime = 0;
			}

		}
		// 몬스터가 플레이어보다 왼쪽에 있을 때, 오른쪽을 바라보고 오른쪽으로 이동.
		if (monsterPos.x < playerPos.x)
		{
			monsterPos.x += 200 * Time::DeltaTime();
			//mAnimator->Play(L"HungRunRight", true);
			if (monsterPos.x > playerPos.x)
				return;

			if (mTime > 3.0f)
			{
				switch (rand)
				{
				case 1:
					mAnimator->Play(L"BradAttack1Right", false);
					break;
				case 2:
					mAnimator->Play(L"BradDiveRight", false);
					collider->SetCenter(Vector2(100.0f, -140.0f));
					collider->SetSize(Vector2(320.0f, 140.0f));
					break;
				case 3:
					mAnimator->Play(L"BradFly_StompRight", false);
					collider->SetCenter(Vector2(-100.0f, -230.0f));
					collider->SetSize(Vector2(430.0f, 230.0f));
					break;
				default:
					break;
				}
				mState = eBradState::Attack;
				mTime = 0;
			}
		}

		tr->SetPos(monsterPos);











		//Transform* tr = GetComponent<Transform>();
		//Vector2 monsterPos = tr->GetPos();

		//Transform* playTr = gPlayer->GetComponent<Transform>();
		//Vector2 playerPos = playTr->GetPos();

		//mTime += Time::DeltaTime();

		//tr->SetPos(monsterPos);


		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos();

		////Vector2 velocity = mRigidbody->GetVelocity();
		//std::srand((unsigned int)time(NULL));
		//rand = (std::rand() % 3) + 1;

		//mTime += Time::DeltaTime();


		//if (mTime > 3.0f)
		//{
		//	switch (rand)
		//	{
		//	case 1:
		//		mAnimator->Play(L"BradAttack1Left", false);
		//		break;
		//	case 2:
		//		mAnimator->Play(L"BradDiveLeft", false);

		//		break;
		//	case 3:
		//		mAnimator->Play(L"BradFly_StompLeft", false);
		//		break;
		//	default:
		//		break;
		//	}
		//	mState = eBradState::Attack;
		//	mTime = 0;
		//}
		//tr->SetPos(pos);
	}

	void Brad::attack()
	{

		if (mAnimator->IsComplete() && mbRight)
		{
			mAnimator->Play(L"BradIdleRight", true);
			collider->SetCenter(Vector2(-90.0f, -140.0f));
			collider->SetSize(Vector2(60.0f, 140.0f));
			mState = eBradState::Idle;
		}
		if (mAnimator->IsComplete() && mbLeft)
		{
			mAnimator->Play(L"BradIdleLeft", true);
			collider->SetCenter(Vector2(30.0f, -140.0f));
			collider->SetSize(Vector2(60.0f, 140.0f));
			mState = eBradState::Idle;
		}

		if (mAnimator->IsComplete() && mbRight)
		{
			mAnimator->Play(L"BradIdleRight", true);
			mState = eBradState::Idle;
		}
		if (mAnimator->IsComplete() && mbLeft)
		{
			mAnimator->Play(L"BradIdleLeft", true);
			mState = eBradState::Idle;
		}
	}
}