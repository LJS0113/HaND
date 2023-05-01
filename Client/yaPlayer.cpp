#pragma once
#include "yaPlayer.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaResources.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaAnimation.h"
#include "yaCollider.h"
#include "yaBaseBullet.h"
#include "yaScene.h"
#include "yaObject.h"
#include "yaRigidbody.h"
#include "yaColliderObj.h"
#include "yaGround.h"

namespace ya
{
	Player* gPlayer = nullptr;

	Player::Player()
		: mbRight(true)
		, mbLeft(false)
		, attackCount(0)
		, hpCount(100)
		, mbMonsterDead(false)
	{
	}
	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		// Idle
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Idle\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Idle\\Left", Vector2::Zero, 0.1f);

		// Run
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Run\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Run\\Left", Vector2::Zero, 0.1f);

		//Jump
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Jump\\Right", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Jump\\Left", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Falling\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Falling\\Left", Vector2::Zero, 0.1f);

		// Elevator
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Elevator\\In", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Elevator\\Out", Vector2::Zero, 0.05f);

		// Dash
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Dash\\Right", Vector2::Zero, 0.03f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Dash\\Left", Vector2::Zero, 0.03f);

		// Death
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Dead_Screen", Vector2::Zero, 0.03f);

		// Attack
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack1\\Right", Vector2::Zero, 0.002f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack2\\Right", Vector2::Zero, 0.005f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack3\\Right", Vector2::Zero, 0.005f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack4\\Right", Vector2::Zero, 0.005f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack1\\Left", Vector2::Zero, 0.002f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack2\\Left", Vector2::Zero, 0.005f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack3\\Left", Vector2::Zero, 0.005f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack4\\Left", Vector2::Zero, 0.005f);

		//mAnimator->GetStartEvent(L"IdleIdle") = std::bind(&Player::idleCompleteEvent, this);
		mAnimator->Play(L"PlayerIdleRight", true);

		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-50.0f, -130.0f));
		collider->SetSize(Vector2(90.0f, 110.0f));

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		mPrevState = ePlayerState::Idle;
		mState = ePlayerState::Idle;
		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();

		if (hpCount == 0)
		{
			mAnimator->Play(L"HaND_ResourcePlayerDead_Screen", false);
			mState = ePlayerState::Death;
		}

		switch (mState)
		{
		case ya::Player::ePlayerState::Move:
			move();
			break;
		case ya::Player::ePlayerState::Dash:
			dash();
			break;
		case ya::Player::ePlayerState::Jump:
			jump();
			break;
		case ya::Player::ePlayerState::Attack:
			attack();
			break;
		case ya::Player::ePlayerState::Death:
			death();
			break;
		case ya::Player::ePlayerState::Idle:
			idle();
			break;
		default:
			break;
		}
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Player::Release()
	{
		GameObject::Release();
	}
	void Player::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::HungAS)
			hpCount -= 10;
		if (other->GetOwner()->GetLayerType() == eLayerType::Stone)
			hpCount -= 10;
		if (other->GetOwner()->GetLayerType() == eLayerType::Lazer)
			hpCount -= 10;
		if (other->GetOwner()->GetLayerType() == eLayerType::MonsterColliderObj)
			hpCount -= 10;
			
	}

	void Player::OnCollisionStay(Collider* other)
	{
		//if (other->GetOwner()->GetLayerType() == eLayerType::Ground)

	}

	void Player::OnCollisionExit(Collider* other)
	{
		//if (other->GetOwner()->GetLayerType() == eLayerType::Ground)

	}

	void Player::move()
	{

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::A))
		{
			mbLeft = true;
			mbRight = false;
			if (Input::GetKeyDown(eKeyCode::LSHIFT))
			{
				Vector2 velocity = mRigidbody->GetVelocity();
				mAnimator->Play(L"PlayerDashLeft", false);
				pos.x -= 300.0f;
				mPrevState = ePlayerState::Move;
				mState = ePlayerState::Dash;

			}
			else if (Input::GetKeyDown(eKeyCode::SPACE))
			{
				if (mbRight)
				{
					mAnimator->Play(L"PlayerJumpRight", false);
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.y -= 800.0f;

					mRigidbody->SetVelocity(velocity);
					mRigidbody->SetGround(false);
					mPrevState = ePlayerState::Move;
					mState = ePlayerState::Jump;
				}
				if (mbLeft)
				{
					mAnimator->Play(L"PlayerJumpLeft", false);
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.y -= 800.0f;

					mRigidbody->SetVelocity(velocity);
					mRigidbody->SetGround(false);
					mPrevState = ePlayerState::Move;
					mState = ePlayerState::Jump;
				}
			}
			else
			{
				pos.x -= 400.0f * Time::DeltaTime();
				mPrevState = ePlayerState::Move;
				mState = ePlayerState::Move;
			}
			if (mAnimator->IsComplete() && mbLeft)
			{
				mAnimator->Play(L"PlayerRunLeft", true);
				mPrevState = ePlayerState::Move;
				mState = ePlayerState::Move;
			}
			if (mAnimator->IsComplete() && mbRight)
			{
				mAnimator->Play(L"PlayerRunRight", true);
				mPrevState = ePlayerState::Move;
				mState = ePlayerState::Move;
			}
		}
		if (Input::GetKey(eKeyCode::D))
		{
			mbRight = true;
			mbLeft = false;
			if (Input::GetKeyDown(eKeyCode::LSHIFT))
			{
				Vector2 velocity = mRigidbody->GetVelocity();
				mAnimator->Play(L"PlayerDashRight", false);
				pos.x += 300.0f;


				mPrevState = ePlayerState::Move;
				mState = ePlayerState::Dash;
			}
			else if (Input::GetKeyDown(eKeyCode::SPACE))
			{
				if (mbRight)
				{
					mAnimator->Play(L"PlayerJumpRight", false);
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.y -= 800.0f;

					mRigidbody->SetVelocity(velocity);
					mRigidbody->SetGround(false);
					mPrevState = ePlayerState::Move;
					mState = ePlayerState::Jump;
				}
				if (mbLeft)
				{
					mAnimator->Play(L"PlayerJumpLeft", false);
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.y -= 800.0f;

					mRigidbody->SetVelocity(velocity);
					mRigidbody->SetGround(false);
					mPrevState = ePlayerState::Move;
					mState = ePlayerState::Jump;
				}
			}
			else
			{
				pos.x += 400.0f * Time::DeltaTime();
				mPrevState = ePlayerState::Move;
				mState = ePlayerState::Move;
			}

			if (mAnimator->IsComplete() && mbLeft)
			{
				mAnimator->Play(L"PlayerRunLeft", true);
				mPrevState = ePlayerState::Move;
				mState = ePlayerState::Move;
			}
			if (mAnimator->IsComplete() && mbRight)
			{
				mAnimator->Play(L"PlayerRunRight", true);
				mPrevState = ePlayerState::Move;
				mState = ePlayerState::Move;
			}
		}
		if (Input::GetKey(eKeyCode::W))
		{
			mRigidbody->AddForce(Vector2(0.0f, -200.0f));
			mPrevState = ePlayerState::Move;
			mState = ePlayerState::Move;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			mRigidbody->AddForce(Vector2(0.0f, +200.0f));
			mPrevState = ePlayerState::Move;
			mState = ePlayerState::Move;
		}

		if (Input::GetKeyUp(eKeyCode::W)
			|| Input::GetKeyUp(eKeyCode::S)
			|| Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::D))
		{
			if (mbLeft)
				mAnimator->Play(L"PlayerIdleLeft", true);
			if (mbRight)
				mAnimator->Play(L"PlayerIdleRight", true);

			mPrevState = ePlayerState::Move;
			mState = ePlayerState::Idle;
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::S)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			mPrevState = ePlayerState::Move;
			mState = ePlayerState::Move;
		}

		// attack
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			attackCount++;
			// 4타 이후에는 다시 1타로 돌아옴
			if (attackCount > 4)
				attackCount = 1;

			if (attackCount == 1)
			{
				if (mbLeft)
				{
					mAnimator->Play(L"PlayerAttack1Left", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-220.0f, -90.0f));
					collider3->SetSize(Vector2(200.0f, 90.0f));
				}
				if (mbRight)
				{
					mAnimator->Play(L"PlayerAttack1Right", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(20.0f, -90.0f));
					collider3->SetSize(Vector2(200.0f, 90.0f));
				}
			}
			if (attackCount == 2)
			{
				if (mbLeft)
				{
					mAnimator->Play(L"PlayerAttack2Left", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-130.0f, -220.0f));
					collider3->SetSize(Vector2(100.0f, 220.0f));
				}
				if (mbRight)
				{
					mAnimator->Play(L"PlayerAttack2Right", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(20.0f, -220.0f));
					collider3->SetSize(Vector2(100.0f, 220.0f));
				}
			}
			if (attackCount == 3)
			{
				if (mbLeft)
				{
					mAnimator->Play(L"PlayerAttack3Left", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-180.0f, -300.0f));
					collider3->SetSize(Vector2(180.0f, 300.0f));
				}
				if (mbRight)
				{
					mAnimator->Play(L"PlayerAttack3Right", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(0.0f, -300.0f));
					collider3->SetSize(Vector2(180.0f, 300.0f));
				}
			}
			if (attackCount == 4)
			{
				if (mbLeft)
				{
					mAnimator->Play(L"PlayerAttack4Left", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-240.0f, -390.0f));
					collider3->SetSize(Vector2(240.0f, 390.0f));
				}
				if (mbRight)
				{
					mAnimator->Play(L"PlayerAttack4Right", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(0.0f, -390.0f));
					collider3->SetSize(Vector2(240.0f, 390.0f));
				}
			}
			mState = ePlayerState::Attack;
		}

		tr->SetPos(pos);
	}
	void Player::death()
	{

	}
	void Player::idle()
	{
		collider->SetCenter(Vector2(-50.0f, -130.0f));
		collider->SetSize(Vector2(90.0f, 110.0f));

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mPrevState = ePlayerState::Idle;
		mState = ePlayerState::Idle;

		if (Input::GetKeyDown(eKeyCode::A))
		{
			pos.x -= 100.0f * Time::DeltaTime();
			mAnimator->Play(L"PlayerRunLeft", true);
			mPrevState = ePlayerState::Idle;
			mState = ePlayerState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			pos.x += 100.0f * Time::DeltaTime();
			mAnimator->Play(L"PlayerRunRight", true);
			mPrevState = ePlayerState::Idle;
			mState = ePlayerState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mRigidbody->AddForce(Vector2(0.0f, -200.0f));
			mPrevState = ePlayerState::Idle;
			mState = ePlayerState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			mRigidbody->AddForce(Vector2(0.0f, +200.0f));
			mPrevState = ePlayerState::Idle;
			mState = ePlayerState::Move;
		}

		// jump
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			if (mbRight)
			{
				mAnimator->Play(L"PlayerJumpRight", false);
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y -= 800.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);

				mState = ePlayerState::Jump;
			}
			if (mbLeft)
			{
				mAnimator->Play(L"PlayerJumpLeft", false);
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y -= 800.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);

				mState = ePlayerState::Jump;
			}
		}

		// dash
		if (Input::GetKeyDown(eKeyCode::LSHIFT))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			if (mbRight)
			{
				mAnimator->Play(L"PlayerDashRight", false);
				pos.x += 300.0f;

				mPrevState = ePlayerState::Idle;
				mState = ePlayerState::Dash;
			}
			if (mbLeft)
			{
				mAnimator->Play(L"PlayerDashLeft", false);
				pos.x -= 300.0f;

				mPrevState = ePlayerState::Idle;
				mState = ePlayerState::Dash;
			}
		}

		// attack
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			attackCount++;
			// 4타 이후에는 다시 1타로 돌아옴
			if (attackCount > 4)
				attackCount = 1;

			if (attackCount == 1)
			{
				if (mbLeft)
				{
					mAnimator->Play(L"PlayerAttack1Left", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-220.0f, -90.0f));
					collider3->SetSize(Vector2(200.0f, 90.0f));
				}
				if (mbRight)
				{ 
					mAnimator->Play(L"PlayerAttack1Right", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(20.0f, -90.0f));
					collider3->SetSize(Vector2(200.0f, 90.0f));
				}
			}
			if (attackCount == 2)
			{
				if (mbLeft)
				{
					mAnimator->Play(L"PlayerAttack2Left", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-130.0f, -220.0f));
					collider3->SetSize(Vector2(100.0f, 220.0f));
				}
				if (mbRight)
				{
					mAnimator->Play(L"PlayerAttack2Right", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(20.0f, -220.0f));
					collider3->SetSize(Vector2(100.0f, 220.0f));
				}
			}
			if (attackCount == 3)
			{
				if (mbLeft)
				{
					mAnimator->Play(L"PlayerAttack3Left", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-180.0f, -300.0f));
					collider3->SetSize(Vector2(180.0f, 300.0f));
				}
				if (mbRight)
				{
					mAnimator->Play(L"PlayerAttack3Right", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(0.0f, -300.0f));
					collider3->SetSize(Vector2(180.0f, 300.0f));
				}
			}
			if (attackCount == 4)
			{
				if (mbLeft)
				{
					mAnimator->Play(L"PlayerAttack4Left", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-240.0f, -390.0f));
					collider3->SetSize(Vector2(240.0f, 390.0f));
				}
				if (mbRight)
				{
					mAnimator->Play(L"PlayerAttack4Right", false);
					colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::ColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(0.0f, -390.0f));
					collider3->SetSize(Vector2(240.0f, 390.0f));
				}
			}
			mState = ePlayerState::Attack;
		}
		tr->SetPos(pos);
	}

	void Player::dash()
	{
		if (mAnimator->IsComplete() && mbLeft)
		{
			mAnimator->Play(L"PlayerIdleLeft", true);
			mPrevState = ePlayerState::Dash;
			mState = ePlayerState::Idle;
		}
		if (mAnimator->IsComplete() && mbRight)
		{
			mAnimator->Play(L"PlayerIdleRight", true);
			mPrevState = ePlayerState::Dash;
			mState = ePlayerState::Idle;
		}

		if (mAnimator->IsComplete() && mbLeft && mPrevState == ePlayerState::Jump)
		{
			mAnimator->Play(L"PlayerFallingLeft", false);
			mPrevState = ePlayerState::Dash;
			mState = ePlayerState::Idle;
		}
		if (mAnimator->IsComplete() && mbRight && mPrevState == ePlayerState::Jump)
		{
			mAnimator->Play(L"PlayerFallingRight", false);
			mPrevState = ePlayerState::Dash;
			mState = ePlayerState::Idle;
		}
		if (Input::GetKey(eKeyCode::W)
			|| Input::GetKey(eKeyCode::A)
			|| Input::GetKey(eKeyCode::S)
			|| Input::GetKey(eKeyCode::D))
		{
			mState = ePlayerState::Move;
		}
	}

	void Player::jump()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (mAnimator->IsComplete() && mbLeft)
		{
			mAnimator->Play(L"PlayerIdleLeft", true);
			mState = ePlayerState::Idle;
		}
		if (mAnimator->IsComplete() && mbRight)
		{
			mAnimator->Play(L"PlayerIdleRight", true);
			mState = ePlayerState::Idle;
		}

		if (Input::GetKeyDown(eKeyCode::LSHIFT) && mbLeft)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			mAnimator->Play(L"PlayerDashLeft", false);

			pos.x -= 300.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			mPrevState = ePlayerState::Jump;
			mState = ePlayerState::Dash;
		}

		if (Input::GetKeyDown(eKeyCode::LSHIFT) && mbRight)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			mAnimator->Play(L"PlayerDashRight", false);
			pos.x += 300.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			mPrevState = ePlayerState::Jump;
			mState = ePlayerState::Dash;
		}
		tr->SetPos(pos);
	}

	void Player::attack()
	{
		// 4타 이후에는 다시 1타로 돌아옴
		if (attackCount > 4)
			attackCount = 1;

		if (mAnimator->IsComplete() && mbLeft)
		{
			mAnimator->Play(L"PlayerIdleLeft", true);
			object::Destory(colObj);
			mState = ePlayerState::Idle;
		}
		if (mAnimator->IsComplete() && mbRight)
		{
			mAnimator->Play(L"PlayerIdleRight", true);
			object::Destory(colObj);
			mState = ePlayerState::Idle;
		}

		if (Input::GetKey(eKeyCode::W)
			|| Input::GetKey(eKeyCode::A)
			|| Input::GetKey(eKeyCode::S)
			|| Input::GetKey(eKeyCode::D))
		{
			object::Destory(colObj);
			mState = ePlayerState::Move;
		}
	}
}
