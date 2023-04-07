#include "yaCuphead.h"
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

namespace ya
{
	Cuphead::Cuphead()
		: mbRight(true)
		, mbLeft(false)
		, attackCount(0)
	{
	}
	Cuphead::~Cuphead()
	{
	}

	void Cuphead::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(400.0f, 400.0f));
		//tr->SetScale(Vector2(1.5f, 1.5f));

		// 기존 컵헤드
		//Image* mImage = Resources::Load<Image>(L"Cuphead", L"..\\Resources\\Cuphead_Stage.bmp");
		mAnimator = AddComponent<Animator>();
		//mAnimator->CreateAnimation(L"FowardRun", mImage, Vector2::Zero, 16, 8, 16, Vector2::Zero, 0.1);
		//mAnimator->CreateAnimation(L"FowardRight", mImage, Vector2(0.0f, 113.0f), 16, 8, 15, Vector2::Zero, 0.1);
		//mAnimator->CreateAnimation(L"Idle", mImage, Vector2(0.0f, 113.0f * 5), 16, 8, 9, Vector2(-50.0f, -50.0f), 0.1);

		// Idle
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Idle\\Idle\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Idle\\Idle\\Left", Vector2::Zero, 0.1f);

		// Run
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Run\\Run\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Run\\Run\\Left", Vector2::Zero, 0.1f);

		//Jump
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Jump\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Jump\\Left", Vector2::Zero, 0.1f);
		// Dash
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Dash\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Dash\\Left", Vector2::Zero, 0.1f);

		// Attack
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack\\Attack1\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack\\Attack2\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack\\Attack3\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack\\Attack4\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack\\Attack1\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack\\Attack2\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack\\Attack3\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Player\\Attack\\Attack4\\Left", Vector2::Zero, 0.1f);
		

		//mAnimator->GetStartEvent(L"IdleIdle") = std::bind(&Cuphead::idleCompleteEvent, this);
		mAnimator->Play(L"IdleRight", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-75.0f, -145.0f));
		collider->SetSize(Vector2(150.0f, 150.0f));

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		mState = eCupheadState::Idle;

		GameObject::Initialize();
	}

	void Cuphead::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ya::Cuphead::eCupheadState::Move:
			move();
			break;
		case ya::Cuphead::eCupheadState::Dash:
			dash();
			break;
		case ya::Cuphead::eCupheadState::Jump:
			jump();
			break;
		case ya::Cuphead::eCupheadState::Shoot:
			shoot();
			break;
		case ya::Cuphead::eCupheadState::Attack:
			attack();
			break;
		case ya::Cuphead::eCupheadState::Death:
			death();
			break;
		case ya::Cuphead::eCupheadState::Idle:
			idle();
			break;
		default:
			break;
		}

	}

	void Cuphead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Cuphead::Release()
	{
		GameObject::Release();

	}
	void Cuphead::OnCollisionEnter(Collider* other)
	{
		int a = 0;
	}

	void Cuphead::OnCollisionStay(Collider* other)
	{

	}

	void Cuphead::OnCollisionExit(Collider* other)
	{

	}

	void Cuphead::move()
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

				velocity.x -= 300.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);

				mAnimator->Play(L"DashLeft", false);
			}
			else if (Input::GetKeyDown(eKeyCode::SPACE))
			{
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y -= 500.0f;

				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);

				if (mbRight)
				{
					mAnimator->Play(L"JumpRight", false);
				}
				if (mbLeft)
				{
					mAnimator->Play(L"JumpLeft", false);
				}
			}

			if (mAnimator->IsComplete() && mbLeft)
			{
				mAnimator->Play(L"RunLeft", true);
			}
			if (mAnimator->IsComplete() && mbRight)
			{
				mAnimator->Play(L"RunRight", true);
			}
			else
			{
				mRigidbody->AddForce(Vector2(-200.0f, 0.0f));
			}
		}
		if (Input::GetKey(eKeyCode::D))
		{
			mbRight = true;
			mbLeft = false;
			if (Input::GetKeyDown(eKeyCode::LSHIFT))
			{
				Vector2 velocity = mRigidbody->GetVelocity();

				velocity.x += 300.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);

				mAnimator->Play(L"DashRight", false);
			}
			else if (Input::GetKeyDown(eKeyCode::SPACE))
			{
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y -= 500.0f;

				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);

				if (mbRight)
				{
					mAnimator->Play(L"JumpRight", false);
				}
				if (mbLeft)
				{
					mAnimator->Play(L"JumpLeft", false);
				}
			}

			if (mAnimator->IsComplete() && mbLeft)
			{
				mAnimator->Play(L"RunLeft", true);
			}
			if (mAnimator->IsComplete() && mbRight)
			{
				mAnimator->Play(L"RunRight", true);
			}
			else
			{
				mRigidbody->AddForce(Vector2(200.0f, 0.0f));
			}
		}
		if (Input::GetKey(eKeyCode::W))
			mRigidbody->AddForce(Vector2(0.0f, -200.0f));

		if (Input::GetKey(eKeyCode::S))
			mRigidbody->AddForce(Vector2(0.0f, +200.0f));

		//// attack
		//if (Input::GetKeyDown(eKeyCode::U))
		//{
		//	mAnimator->Play(L"AttackAttack1", false);
		//	mState = eCupheadState::Attack;
		//}

		//if (Input::GetKeyDown(eKeyCode::I))
		//{
		//	mAnimator->Play(L"AttackAttack2", false);
		//	mState = eCupheadState::Attack;
		//}

		//if (Input::GetKeyDown(eKeyCode::O))
		//{
		//	mAnimator->Play(L"AttackAttack3", false);
		//	mState = eCupheadState::Attack;
		//}

		//if (Input::GetKeyDown(eKeyCode::P))
		//{
		//	mAnimator->Play(L"AttackAttack4", false);
		//	mState = eCupheadState::Attack;
		//}

		if (Input::GetKeyUp(eKeyCode::W)
			|| Input::GetKeyUp(eKeyCode::S)
			|| Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::D))
		{
			if (mbLeft)
				mAnimator->Play(L"IdleLeft", true);
			if (mbRight)
				mAnimator->Play(L"IdleRight", true);
			mState = eCupheadState::Idle;
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::S)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			mState = eCupheadState::Move;
		}

		tr->SetPos(pos);
	}
	void Cuphead::shoot()
	{
		Transform* tr = GetComponent<Transform>();
		if (Input::GetKey(eKeyCode::K))
		{
			object::Instantiate<BaseBullet>(Vector2(400.0f, 400.0f), eLayerType::Bullet);

			/*Scene* curScene = SceneManager::GetActiveScene();
			BaseBullet* bullet = new BaseBullet();
			bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
			curScene->AddGameObeject(bullet, eLayerType::Bullet);*/
		}

	}
	void Cuphead::death()
	{
	}
	void Cuphead::idle()
	{
		if (Input::GetKeyDown(eKeyCode::A))
		{
			mRigidbody->AddForce(Vector2(-200.0f, 0.0f));
			mAnimator->Play(L"RunLeft", true);
			mState = eCupheadState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			mRigidbody->AddForce(Vector2(200.0f, 0.0f));
			//pos.x += 100.0f * Time::DeltaTime();
			mAnimator->Play(L"RunRight", true);
			mState = eCupheadState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mRigidbody->AddForce(Vector2(0.0f, -200.0f));
			mState = eCupheadState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			mRigidbody->AddForce(Vector2(0.0f, +200.0f));
			mState = eCupheadState::Move;
		}

		// jump
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 500.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			if (mbRight)
			{
				mAnimator->Play(L"JumpRight", false);
				mState = eCupheadState::Jump;
			}
			if (mbLeft)
			{
				mAnimator->Play(L"JumpLeft", false);
				mState = eCupheadState::Jump;
			}
		}

		// dash
		if (Input::GetKeyDown(eKeyCode::LSHIFT))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			if (mbRight)
			{
				velocity.x += 300.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
				mAnimator->Play(L"DashRight", false);
				mState = eCupheadState::Dash;
			}
			if (mbLeft)
			{
				velocity.x -= 300.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
				mAnimator->Play(L"DashLeft", false);
				mState = eCupheadState::Dash;
			}
		}

		// attack
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			attackCount++;
			mState = eCupheadState::Attack;
		}

	}

	void Cuphead::dash()
	{
		if (mAnimator->IsComplete() && mbLeft)
		{
			mAnimator->Play(L"IdleLeft", true);
			mState = eCupheadState::Idle;
		}
		if (mAnimator->IsComplete() && mbRight)
		{
			mAnimator->Play(L"IdleRight", true);
			mState = eCupheadState::Idle;
		}
	}

	void Cuphead::jump()
	{
		if (mAnimator->IsComplete() && mbLeft)
		{
			mAnimator->Play(L"IdleLeft", true);
			mState = eCupheadState::Idle;
		}
		if (mAnimator->IsComplete() && mbRight)
		{
			mAnimator->Play(L"IdleRight", true);
			mState = eCupheadState::Idle;
		}
	}

	void Cuphead::attack()
	{
		// 4타 이후에는 다시 1타로 돌아옴
		if (attackCount > 4)
			attackCount = 1;

		if (attackCount == 1 && mbRight)
			mAnimator->Play(L"Attack1Right", false);
		if (attackCount == 2 && mbRight)
			mAnimator->Play(L"Attack2Right", false);
		if (attackCount == 3 && mbRight)
			mAnimator->Play(L"Attack3Right", false);
		if (attackCount == 4 && mbRight)
			mAnimator->Play(L"Attack4Right", false);

		if (attackCount == 1 && mbLeft)
			mAnimator->Play(L"Attack1Left", false);
		if (attackCount == 2 && mbLeft)
			mAnimator->Play(L"Attack2Left", false);
		if (attackCount == 3 && mbLeft)
			mAnimator->Play(L"Attack3Left", false);
		if (attackCount == 4 && mbLeft)
			mAnimator->Play(L"Attack4Left", false);

		mTime += Time::DeltaTime();

		if (mTime > 2.0f)
		{
			mState = eCupheadState::Idle;
		}



		if (Input::GetKey(eKeyCode::W)
			|| Input::GetKey(eKeyCode::A)
			|| Input::GetKey(eKeyCode::S)
			|| Input::GetKey(eKeyCode::D))
		{
			mState = eCupheadState::Move;
		}

	}

	void Cuphead::idleCompleteEvent(/*const Cuphead* this*/)
	{
		int a = 0;
		//mState =
		//Transform* tr = GetComponent<Transform>();
		//Scene* curScene = SceneManager::GetActiveScene();
		//BaseBullet* bullet = new BaseBullet();
		//bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
		//curScene->AddGameObeject(bullet, eLayerType::Bullet);
	}
}
