#pragma once
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
#include "yaObject.h"
#include "yaHungAS.h"
#include "yaPlayer.h"

//extern ya::Player* player;

namespace ya
{
	Hung::Hung()
		: mbLeft(true)
		, mbRight(false)
	{
		//gPlayer->
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

		collider = AddComponent<Collider>();

		//mRigidbody = AddComponent<Rigidbody>();
		//mRigidbody->SetMass(1.0f);

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

	}
	void Hung::death()
	{
	}
	void Hung::idle()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		//Vector2 velocity = mRigidbody->GetVelocity();
		std::srand((unsigned int)time(NULL));
		rand = (std::rand() % 3) + 1;

		mTime += Time::DeltaTime();

		if (Input::GetKeyDown(eKeyCode::K))
		{
			mAnimator->Play(L"HungAttackMeleeLeft", false);
			collider->SetCenter(Vector2(-330.0f, -230.0f));
			collider->SetSize(Vector2(430.0f, 230.0f));
			
			mbLeft = true;
			mbRight = false;

			mState = eHungState::Attack;
		}

		if (Input::GetKeyDown(eKeyCode::L))
		{
			mAnimator->Play(L"HungAttackMeleeRight", false);
			collider->SetCenter(Vector2(-100.0f, -230.0f));
			collider->SetSize(Vector2(430.0f, 230.0f));
			
			mbLeft = false;
			mbRight = true;

			mState = eHungState::Attack;
		}

		if (Input::GetKey(eKeyCode::G))
		{
			//mRigidbody->AddForce(Vector2(-500.0f, 0.0f));
			pos.x -= 400.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::J))
		{
			//mRigidbody->AddForce(Vector2(-500.0f, 0.0f));
			pos.x += 400.0f * Time::DeltaTime();
		}


		/*if (mTime > 3.0f)
		{

			switch (rand)
			{
			case 1:
				mAnimator->Play(L"HungAttackSpecialRight", false);
				for (size_t i = 0; i < 4; i++)
				{
					rand = std::rand() % 1023;
					object::Instantiate<HungAS>(Vector2(float(rand), 700.0f), eLayerType::HungAS);
				}
				break;
			case 2:
				mAnimator->Play(L"AttackLassoRightThrow", false);
				collider->SetCenter(Vector2(30.0f, -140.0f));
				collider->SetSize(Vector2(900.0f, 140.0f));
				break;
			case 3:
				mAnimator->Play(L"HungAttackMeleeRight", false);
				break;
			default:
				break;
			}
			mState = eHungState::Attack;
			mTime = 0;
		}*/
		tr->SetPos(pos);
	}
	void Hung::attack()
	{
		if (mAnimator->IsComplete() && mbRight)
		{
			mAnimator->Play(L"HungIdleRight", true);
			collider->SetCenter(Vector2(-90.0f, -140.0f));
			collider->SetSize(Vector2(60.0f, 140.0f));
			mState = eHungState::Idle;
		}
		if (mAnimator->IsComplete() && mbLeft)
		{
			mAnimator->Play(L"HungIdleLeft", true);
			collider->SetCenter(Vector2(30.0f, -140.0f));
			collider->SetSize(Vector2(60.0f, 140.0f));
			mState = eHungState::Idle;
		}
	}
	void Hung::OnCollisionEnter(Collider* other)
	{

	}
	void Hung::OnCollisionStay(Collider* other)
	{
	}
	void Hung::OnCollisionExit(Collider* other)
	{
	}
}