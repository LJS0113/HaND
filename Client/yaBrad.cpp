#pragma once
#include "yaBrad.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaTransform.h"
#include "yaPlayer.h"
#include "yaObject.h"
#include "yaStone.h"
#include "yaColliderObj.h"

namespace ya
{
	Brad::Brad()
		: mbLeft(true)
		, mbRight(false)
		, mAttackDelay(0.0f)
		, mflyTime(0.0f)
		, mfallingTime(0.0f)
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

		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Intro\\Intro", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Intro\\Desk", Vector2::Zero, 0.01f);

		// Attack
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Attack1\\Right", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Attack1\\Left", Vector2::Zero, 0.01f);

		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Dive\\Right", Vector2::Zero, 0.007f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Dive\\Left", Vector2::Zero, 0.007f);

		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Fly_Stomp\\Right", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Fly_Stomp\\Left", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Fly_Stomp_To_Idle\\Right", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\Fly_Stomp_To_Idle\\Left", Vector2::Zero, 0.01f);

		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\SpinAir", Vector2::Zero, 0.01f);

		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\End", Vector2::Zero, 0.01f);

		mAnimator->Play(L"BradIntroIntro", false);
		mState = eBradState::Intro;
		collider = AddComponent<Collider>();
		collider->SetSize(Vector2::Zero);
		GameObject::Initialize();
	}

	void Brad::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ya::Brad::eBradState::Intro:
			intro();
			break;
		case ya::Brad::eBradState::Move:
			move();
			break;
		case ya::Brad::eBradState::Attack:
			attack();
			break;
		case ya::Brad::eBradState::Death:
			death();
			break;
		case ya::Brad::eBradState::Idle:
			idle();
			break;
		case ya::Brad::eBradState::DiveAttack:
			diveAttack();
			break;
		case ya::Brad::eBradState::Attack1:
			attack1();
			break;
		case ya::Brad::eBradState::Fly:
			fly();
			break;
		case ya::Brad::eBradState::SpinAir:
			spinAir();
			break;
		case ya::Brad::eBradState::FlyToIdle:
			flyToIdle();
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

	void Brad::intro()
	{
		if (mAnimator->IsComplete())
		{
			mAnimator->Play(L"BradIdleLeft", true);
			mState = eBradState::Idle;
		}
	}

	void Brad::death()
	{
	}

	void Brad::idle()
	{
		collider->SetCenter(Vector2(-80.0f, -200.0f));
		collider->SetSize(Vector2(170.0f, 200.0f));

		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		std::srand((unsigned int)time(NULL));
		rand = (std::rand() % 3) + 1;
		mTime += Time::DeltaTime();

		// �׽�Ʈ��
		if (Input::GetKeyDown(eKeyCode::K))
		{
			mAnimator->Play(L"BradAttack1Left", false);
			colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
			collider3 = colObj->GetComponent<Collider>();
			mState = eBradState::Attack1;
		}

		// ���Ͱ� �÷��̾�� �����ʿ� ������, ������ �ٶ󺸰� �������� �̵�.
		if (monsterPos.x > playerPos.x)
		{
			mbLeft = true;
			mbRight = false;

			if (mTime > 2.0f)
			{
				switch (rand)
				{
				case 1:
					mAnimator->Play(L"BradAttack1Left", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-330.0f, -230.0f));
					collider3->SetSize(Vector2(430.0f, 230.0f));
					mState = eBradState::Attack1;
					break;
				case 2:
					mAttackDelay += Time::DeltaTime();
					mAnimator->Play(L"BradDiveLeft", false);
					mState = eBradState::DiveAttack;
					break;
				case 3:
					mAnimator->Play(L"BradFly_StompLeft", false);
					mState = eBradState::Fly;
					break;
				default:
					break;
				}
				mTime = 0;
			}
		}

		// ���Ͱ� �÷��̾�� ���ʿ� ���� ��, �������� �ٶ󺸰� ���������� �̵�.
		if (monsterPos.x < playerPos.x)
		{
			mbLeft = false;
			mbRight = true;

			if (mTime > 3.0f)
			{
				switch (rand)
				{
				case 1:
					mAnimator->Play(L"BradAttack1Right", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
					collider3 = colObj->GetComponent<Collider>();
					mState = eBradState::Attack1;
					break;
				case 2:
					mAnimator->Play(L"BradDiveRight", false);
					mState = eBradState::DiveAttack;
					break;
				case 3:
					mAnimator->Play(L"BradFly_StompRight", false);
					mState = eBradState::Fly;
					break;
				default:
					break;
				}
				mTime = 0;
			}
		}
		tr->SetPos(monsterPos);
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

	}

	void Brad::move()
	{
	}

	void Brad::diveAttack()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();
		mTime += Time::DeltaTime();

		if (mTime > 1.0f)
		{
			if (mbLeft)
			{
				if (monsterPos.x > 300)
					monsterPos.x -= 300.0f * Time::DeltaTime();
			}

			if (mbRight)
			{
				if (monsterPos.x < 1300)
					monsterPos.x += 300.0f * Time::DeltaTime();
			}
		}
		if (mAnimator->IsComplete() && mbLeft)
		{
			mAnimator->Play(L"BradIdleLeft", true);
			mState = eBradState::Idle;
			mTime = 0;
		}
		if (mAnimator->IsComplete() && mbRight)
		{
			mAnimator->Play(L"BradIdleRight", true);
			mState = eBradState::Idle;
			mTime = 0;
		}


		tr->SetPos(monsterPos);
	}
	void Brad::attack1()
	{
		Transform* tr = GetComponent<Transform>();

		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		if (mbLeft)
		{
			if (monsterPos.x > 200)
				monsterPos.x -= 200.0f * Time::DeltaTime();
			collider3->SetCenter(Vector2(-330.0f, -230.0f));
			collider3->SetSize(Vector2(180.0f, 300.0f));
		}
		if (mbRight)
		{
			if (monsterPos.x < 1400)
				monsterPos.x += 200.0f * Time::DeltaTime();
			collider3->SetCenter(Vector2(-330.0f, -230.0f));
			collider3->SetSize(Vector2(180.0f, 300.0f));
		}
		if (mAnimator->IsComplete())
		{
			if (mbLeft)
			{
				mAnimator->Play(L"BradIdleLeft", true);
				object::Destory(colObj);
				mState = eBradState::Idle;
			}
			if (mbRight)
			{
				mAnimator->Play(L"BradIdleRight", true);
				object::Destory(colObj);
				mState = eBradState::Idle;
			}
		}
		tr->SetPos(monsterPos);
	}
	void Brad::fly()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();
		monsterPos.y -= 1300.0f * Time::DeltaTime();

		if (mAnimator->IsComplete())
		{
			mAnimator->Play(L"MonsterBradSpinAir", true);
			mState = eBradState::SpinAir;
		}
		tr->SetPos(monsterPos);
	}
	void Brad::spinAir()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		mflyTime += Time::DeltaTime();
		mAttackDelay += Time::DeltaTime();
		if (mflyTime > 5.0f)
		{
			if (mbLeft)
			{
				mAnimator->Play(L"BradFly_Stomp_To_IdleLeft", false);
				mState = eBradState::FlyToIdle;
				mflyTime = 0.0f;
			}
			if (mbRight)
			{
				mAnimator->Play(L"BradFly_Stomp_To_IdleRight", false);
				mState = eBradState::FlyToIdle;
				mflyTime = 0.0f;
			}
		}

		if (mbLeft)
		{
			monsterPos.x -= 300.0f * Time::DeltaTime();

			if (mAttackDelay > 0.5f) 
			{
				object::Instantiate<Stone>(Vector2(monsterPos.x, monsterPos.y), eLayerType::Stone);
				mAttackDelay = 0.0f;
			}
		}
		if (mbRight)
		{
			monsterPos.x += 300.0f * Time::DeltaTime();
			if (mAttackDelay > 0.5f)
			{
				object::Instantiate<Stone>(Vector2(monsterPos.x, monsterPos.y), eLayerType::Stone);
				mAttackDelay = 0.0f;
			}
		}


		// ���������� �̵�
		if (monsterPos.x < 300.0f)
		{
			mbLeft = false;
			mbRight = true;
		}

		// �������� �̵�
		if (monsterPos.x > 1300.0f)
		{
			mbLeft = true;
			mbRight = false;
		}

		tr->SetPos(monsterPos);
	}
	void Brad::flyToIdle()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		monsterPos.y += 500.0f * Time::DeltaTime();
		if (mAnimator->IsComplete() && monsterPos.y > 800.0f)
		{
			if (mbLeft)
			{
				mAnimator->Play(L"BradIdleLeft", true);
				mState = eBradState::Idle;
			}
			if (mbRight)
			{
				mAnimator->Play(L"BradIdleRight", true);
				mState = eBradState::Idle;
			}
		}
		tr->SetPos(monsterPos);
	}
}