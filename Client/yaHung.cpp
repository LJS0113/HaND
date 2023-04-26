#pragma once
#include "yaHung.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaRigidbody.h"
#include "yaTransform.h"
#include "yaInput.h"
#include "yaComponent.h"
#include "yaGameObject.h"
#include "yaLayer.h"
#include "yaScene.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaHungAS.h"
#include "yaPlayer.h"
#include "yaColliderObj.h"

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

		// Idle
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Idle\\Left", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Idle\\Right", Vector2::Zero, 0.05f);

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
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Run\\Right", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\Run\\Left", Vector2::Zero, 0.05f);

		mAnimator->Play(L"HungIntroStart", false);
		mState = eHungState::Intro;

		collider = AddComponent<Collider>();

		collider->SetCenter(Vector2(30.0f, -140.0f));
		collider->SetSize(Vector2(60.0f, 140.0f));

		GameObject::Initialize();
	}
	void Hung::Update()
	{
		GameObject::Update();
		
		switch (mState)
		{
		case ya::Hung::eHungState::Move:
			move();
			break;
		case ya::Hung::eHungState::Intro:
			intro();
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
		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		std::srand((unsigned int)time(NULL));
		rand = (std::rand() % 3) + 1;

		mTime += Time::DeltaTime();

		if (mbLeft && (monsterPos.x < playerPos.x))
		{
			mbLeft = false;
			mbRight = true;

			mAnimator->Play(L"HungRunRight", true);
			collider->SetCenter(Vector2(-90.0f, -140.0f));
			collider->SetSize(Vector2(60.0f, 140.0f));
			mState = eHungState::Move;
		}
		if (mbRight && (monsterPos.x > playerPos.x))
		{
			mbLeft = true;
			mbRight = false;

			mAnimator->Play(L"HungRunLeft", true);
			collider->SetCenter(Vector2(30.0f, -140.0f));
			collider->SetSize(Vector2(60.0f, 140.0f));
			mState = eHungState::Move;
		}

		// 몬스터가 플레이어보다 오른쪽에 있을때, 왼쪽을 바라보고 왼쪽으로 이동.
		if (monsterPos.x > playerPos.x)
		{
			mbLeft = true;
			mbRight = false;
			monsterPos.x -= 200 * Time::DeltaTime();

			if (mTime > 2.0f)
			{
				switch (rand)
				{
				case 1:
					mAnimator->Play(L"HungAttackSpecialLeft", false);
					for (size_t i = 0; i < 4; i++)
					{
						rand = std::rand() % 1023;
						object::Instantiate<HungAS>(Vector2(float(rand), 1200.0f), eLayerType::HungAS);
					}
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-180.0f, -240.0f));
					collider3->SetSize(Vector2(230.0f, 250.0f));
					break;
				case 2:
					mAnimator->Play(L"AttackLassoLeftThrow", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-420.0f, -140.0f));
					collider3->SetSize(Vector2(320.0f, 140.0f));
					break;
				case 3:
					mAnimator->Play(L"HungAttackMeleeLeft", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-330.0f, -230.0f));
					collider3->SetSize(Vector2(430.0f, 230.0f));
					break;
				default:
					break;
				}
				mState = eHungState::Attack;
				mTime = 0;
			}
		}
		// 몬스터가 플레이어보다 왼쪽에 있을 때, 오른쪽을 바라보고 오른쪽으로 이동.
		if (monsterPos.x < playerPos.x)
		{
			mbLeft = false;
			mbRight = true;
			monsterPos.x += 200 * Time::DeltaTime();
			//mAnimator->Play(L"HungRunRight", true);
			if (monsterPos.x > playerPos.x)
				return;

			if (mTime > 3.0f)
			{
				switch (rand)
				{
				case 1:
					mAnimator->Play(L"HungAttackSpecialRight", false);
					for (size_t i = 0; i < 4; i++)
					{
						rand = std::rand() % 1023;
						object::Instantiate<HungAS>(Vector2(float(rand), 1200.0f), eLayerType::HungAS);
					}
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-50.0f, -240.0f));
					collider3->SetSize(Vector2(230.0f, 250.0f));
					break;
				case 2:
					mAnimator->Play(L"AttackLassoRightThrow", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(100.0f, -140.0f));
					collider3->SetSize(Vector2(320.0f, 140.0f));
					break;
				case 3:
					mAnimator->Play(L"HungAttackMeleeRight", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-100.0f, -230.0f));
					collider3->SetSize(Vector2(430.0f, 230.0f));
					break;
				default:
					break;
				}
				mState = eHungState::Attack;
				mTime = 0;
			}
		}
		tr->SetPos(monsterPos);
	}
	void Hung::death()
	{
	}
	void Hung::idle()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		mTime += Time::DeltaTime();
		if (mTime > 1.0f)
		{
			if (monsterPos.x > playerPos.x)
			{
				mbLeft = true;
				mbRight = false;
				collider->SetCenter(Vector2(30.0f, -140.0f));
				collider->SetSize(Vector2(60.0f, 140.0f));
				mAnimator->Play(L"HungRunLeft", true);
				mState = eHungState::Move;
			}
			if (monsterPos.x < playerPos.x)
			{
				mbLeft = false;
				mbRight = true;
				collider->SetCenter(Vector2(-90.0f, -140.0f));
				collider->SetSize(Vector2(60.0f, 140.0f));
				mAnimator->Play(L"HungRunRight", true);
				mState = eHungState::Move;
			}
			mTime = 0.0f;
		}
		tr->SetPos(monsterPos);
	}
	void Hung::attack()
	{
		if (mAnimator->IsComplete() && mbRight)
		{
			object::Destory(colObj);
			mAnimator->Play(L"HungIdleRight", true);
			collider->SetCenter(Vector2(-90.0f, -140.0f));
			collider->SetSize(Vector2(60.0f, 140.0f));
			mState = eHungState::Idle;
		}
		if (mAnimator->IsComplete() && mbLeft)
		{
			object::Destory(colObj);
			mAnimator->Play(L"HungIdleLeft", true); 
			collider->SetCenter(Vector2(30.0f, -140.0f));
			collider->SetSize(Vector2(60.0f, 140.0f));
			mState = eHungState::Idle;
		}
	}
	void Hung::intro()
	{
		if (mAnimator->IsComplete())
		{
			if (mbLeft)
			{
				mAnimator->Play(L"HungIdleLeft", true);
				collider->SetCenter(Vector2(30.0f, -140.0f));
				collider->SetSize(Vector2(60.0f, 140.0f));
				mState = eHungState::Idle;
			}
			if (mbRight)
			{
				mAnimator->Play(L"HungIdleRight", true);
				collider->SetCenter(Vector2(-90.0f, -140.0f));
				collider->SetSize(Vector2(60.0f, 140.0f));
				mState = eHungState::Idle;
			}
		}
	}
	void Hung::OnCollisionEnter(Collider* other)
	{
		int a = 0;
	}
	void Hung::OnCollisionStay(Collider* other)
	{
	}
	void Hung::OnCollisionExit(Collider* other)
	{
	}
}