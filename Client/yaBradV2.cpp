#pragma once
#include "yaBradV2.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTransform.h"
#include "yaColliderObj.h"
#include "yaObject.h" 
#include "yaLazer.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaMonsterColliderObj.h"

namespace ya
{
	BradV2::BradV2()
		: mTime(0.0f)
		, mbLeft(true)
		, mbRight(false)
		, mMovementTime(0.0f)
		, hpCount(100)
	{
	}

	BradV2::~BradV2()
	{
	}

	void BradV2::Initialize()
	{
		mAnimator = AddComponent<Animator>();

		// Idle
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Idle\\Left", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Idle\\Right", Vector2::Zero, 0.01f);

		// Intro
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Intro", Vector2::Zero, 0.0001f);

		// Move
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Move\\Left", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Move\\Right", Vector2::Zero, 0.01f);

		// Death
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Death", Vector2::Zero, 0.01f);

		// Attack
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack1\\Left", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack1\\Right", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack2\\Left", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack2\\Right", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack3\\Slice\\Left", Vector2::Zero, 0.001f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack3\\Slice\\Right", Vector2::Zero, 0.001f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack3\\Punch\\Left", Vector2::Zero, 0.001f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack3\\Punch\\Right", Vector2::Zero, 0.001f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack5\\Ready\\Left", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack5\\Ready\\Right", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack5\\Fire\\Left", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack5\\Fire\\Right", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack6\\Ready\\Left", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack6\\Ready\\Right", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack6\\Fire\\Left", Vector2::Zero, 0.01f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Attack6\\Fire\\Right", Vector2::Zero, 0.01f);

		mAnimator->Play(L"MonsterBradV2Intro", false);

		collider = AddComponent<Collider>();
		collider->SetSize(Vector2::Zero);

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
		case ya::BradV2::eBradV2State::Attack1:
			attack1();
			break;
		case ya::BradV2::eBradV2State::Attack2:
			attack2();
			break;
		case ya::BradV2::eBradV2State::Attack3_Slice:
			attack3_slice();
			break;
		case ya::BradV2::eBradV2State::Attack3_Punch:
			attack3_punch();
			break;
		case ya::BradV2::eBradV2State::Attack5_Ready:
			attack5_ready();
			break;
		case ya::BradV2::eBradV2State::Attack5_Fire:
			attack5_fire();
			break;
		case ya::BradV2::eBradV2State::Attack6_Ready:
			attack6_ready();
			break;
		case ya::BradV2::eBradV2State::Attack6_Fire:
			attack6_fire();
			break;
		default:
			break;
		}

		//	attack1 �������
		//	attack2 ������ġ �� �ֵθ���
		//	attack3 �ؽ����̽�2�� �� ���� �ĵη��б�
		//	attack5 �� ���̽��� ������ �극������ ����
		//	attack6 ��� �ֵθ��� ������
	}

	void BradV2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BradV2::Release()
	{
		GameObject::Release();
	}

	void BradV2::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::ColliderObj)
			hpCount -= 10;
	}

	void BradV2::OnCollisionStay(Collider* other)
	{
	}

	void BradV2::OnCollisionExit(Collider* other)
	{
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
		if (hpCount == 0)
		{
			mAnimator->Play(L"MonsterBradV2Death", false);
			mState = eBradV2State::Death;
		}

		collider->SetCenter(Vector2(-90.0f, -240.0f));
		collider->SetSize(Vector2(180.0f, 250.0f));

		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		std::srand((unsigned int)time(NULL));
		rand = (std::rand() % 5) + 1;
		mTime += Time::DeltaTime();

		// �׽�Ʈ��
		if (Input::GetKeyDown(eKeyCode::K))
		{
			mbLeft = true;
			mbRight = false;
			mAnimator->Play(L"BradV2Attack1Left", false);
			colObj = object::Instantiate<MonsterColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::MonsterColliderObj);
			collider3 = colObj->GetComponent<Collider>();
			mState = eBradV2State::Attack1;
		}
		// �׽�Ʈ��
		if (Input::GetKeyDown(eKeyCode::L))
		{
			mbLeft = false;
			mbRight = true;
			mAnimator->Play(L"BradV2Attack1Right", false);
			colObj = object::Instantiate<MonsterColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::MonsterColliderObj);
			collider3 = colObj->GetComponent<Collider>();
			mState = eBradV2State::Attack1;
		}


		//if (mTime > 1.0f)
		//{
		//	if (monsterPos.x > playerPos.x)
		//	{
		//		mbLeft = true;
		//		mbRight = false;
		//		collider->SetCenter(Vector2(-90.0f, -240.0f));
		//		collider->SetSize(Vector2(180.0f, 250.0f));
		//		mAnimator->Play(L"BradV2MoveLeft", true);
		//		mState = eBradV2State::Move;
		//	}
		//	if (monsterPos.x < playerPos.x)
		//	{
		//		mbLeft = false;
		//		mbRight = true;
		//		collider->SetCenter(Vector2(-90.0f, -240.0f));
		//		collider->SetSize(Vector2(180.0f, 250.0f));
		//		mAnimator->Play(L"BradV2MoveRight", true);
		//		mState = eBradV2State::Move;
		//	}
		//	mTime = 0.0f;
		//}

#pragma region idle_attack
		//// ���Ͱ� �÷��̾�� �����ʿ� ������, ������ �ٶ󺸰� �������� �̵�.
		//if (monsterPos.x > playerPos.x)
		//{
		//	mbLeft = true;
		//	mbRight = false;

		//	if (mTime > 2.0f)
		//	{
		//		switch (rand)
		//		{
		//		case 1:
		//			mAnimator->Play(L"BradV2Attack1Left", false);
		//			colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
		//			collider3 = colObj->GetComponent<Collider>();
		//			collider3->SetCenter(Vector2(-330.0f, -230.0f));
		//			collider3->SetSize(Vector2(430.0f, 230.0f));
		//			mState = eBradV2State::Attack1;
		//			break;
		//		case 2:
		//			mAnimator->Play(L"BradV2Attack2Left", false);
		//			colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
		//			collider3 = colObj->GetComponent<Collider>();
		//			collider3->SetCenter(Vector2(-330.0f, -230.0f));
		//			collider3->SetSize(Vector2(430.0f, 230.0f));
		//			mState = eBradV2State::Attack2;
		//			break;
		//		case 3:
		//			mAnimator->Play(L"Attack3SliceLeft", false);
		//			colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
		//			collider3 = colObj->GetComponent<Collider>();
		//			collider3->SetCenter(Vector2(-330.0f, -230.0f));
		//			collider3->SetSize(Vector2(430.0f, 230.0f));
		//			mState = eBradV2State::Attack3_Slice;
		//			break;
		//		case 4:
		//			mAnimator->Play(L"Attack5ReadyLeft", false);
		//			mState = eBradV2State::Attack5_Ready;
		//			break;
		//		case 5:
		//			mAnimator->Play(L"Attack6ReadyLeft", false);
		//			colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
		//			collider3 = colObj->GetComponent<Collider>();
		//			collider3->SetCenter(Vector2(-330.0f, -230.0f));
		//			collider3->SetSize(Vector2(430.0f, 230.0f));
		//			mState = eBradV2State::Attack6_Ready;
		//			break;
		//		default:
		//			break;
		//		}
		//		mTime = 0;
		//	}
		//}

		//// ���Ͱ� �÷��̾�� ���ʿ� ���� ��, �������� �ٶ󺸰� ���������� �̵�.
		//if (monsterPos.x < playerPos.x)
		//{
		//	mbLeft = false;
		//	mbRight = true;

		//	if (mTime > 2.0f)
		//	{
		//		switch (rand)
		//		{
		//		case 1:
		//			mAnimator->Play(L"BradV2Attack1Right", false);
		//			colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
		//			collider3 = colObj->GetComponent<Collider>();
		//			collider3->SetCenter(Vector2(-330.0f, -230.0f));
		//			collider3->SetSize(Vector2(430.0f, 230.0f));
		//			mState = eBradV2State::Attack1;
		//			break;
		//		case 2:
		//			mAnimator->Play(L"BradV2Attack2Right", false);
		//			colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
		//			collider3 = colObj->GetComponent<Collider>();
		//			collider3->SetCenter(Vector2(-330.0f, -230.0f));
		//			collider3->SetSize(Vector2(430.0f, 230.0f));
		//			mState = eBradV2State::Attack2;
		//			break;
		//		case 3:
		//			mAnimator->Play(L"Attack3SliceRight", false);
		//			colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
		//			collider3 = colObj->GetComponent<Collider>();
		//			collider3->SetCenter(Vector2(-330.0f, -230.0f));
		//			collider3->SetSize(Vector2(430.0f, 230.0f));
		//			mState = eBradV2State::Attack3_Slice;
		//			break;
		//		case 4:
		//			mAnimator->Play(L"Attack5ReadyRight", false);
		//			mState = eBradV2State::Attack5_Ready;
		//			break;
		//		case 5:
		//			mAnimator->Play(L"Attack6ReadyRight", false);
		//			colObj = object::Instantiate<ColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::Collider);
		//			collider3 = colObj->GetComponent<Collider>();
		//			collider3->SetCenter(Vector2(-330.0f, -230.0f));
		//			collider3->SetSize(Vector2(430.0f, 230.0f));
		//			mState = eBradV2State::Attack6_Ready;
		//			break;
		//		default:
		//			break;
		//		}
		//		mTime = 0;
		//	}
		//}
#pragma endregion idle_attack

		tr->SetPos(monsterPos);
	}

	void BradV2::attack()
	{
		if (mAnimator->IsComplete() && mbRight)
		{
			object::Destory(colObj);
			mAnimator->Play(L"BradV2IdleRight", true);
			collider->SetCenter(Vector2(-90.0f, -140.0f));
			collider->SetSize(Vector2(60.0f, 140.0f));
			mState = eBradV2State::Idle;
		}
		if (mAnimator->IsComplete() && mbLeft)
		{
			object::Destory(colObj);
			mAnimator->Play(L"BradV2IdleLeft", true);
			collider->SetCenter(Vector2(30.0f, -140.0f));
			collider->SetSize(Vector2(60.0f, 140.0f));
			mState = eBradV2State::Idle;
		}
	}

	void BradV2::move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		std::srand((unsigned int)time(NULL));
		rand = (std::rand() % 5) + 1;

		mTime += Time::DeltaTime();

		// ������ȯ
		if (mbLeft && (monsterPos.x < playerPos.x))
		{
			mbLeft = false;
			mbRight = true;

			mAnimator->Play(L"BradV2MoveRight", true);
			collider->SetCenter(Vector2(-90.0f, -240.0f));
			collider->SetSize(Vector2(180.0f, 250.0f));
			mState = eBradV2State::Move;
		}
		if (mbRight && (monsterPos.x > playerPos.x))
		{
			mbLeft = true;
			mbRight = false;

			mAnimator->Play(L"BradV2MoveLeft", true);
			collider->SetCenter(Vector2(-90.0f, -240.0f));
			collider->SetSize(Vector2(180.0f, 250.0f));
			mState = eBradV2State::Move;
		}

		// ���Ͱ� �÷��̾�� �����ʿ� ������, ������ �ٶ󺸰� �������� �̵�.
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
					mAnimator->Play(L"BradV2Attack1Left", false);
					colObj = object::Instantiate<MonsterColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::MonsterColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-330.0f, -230.0f));
					collider3->SetSize(Vector2(430.0f, 230.0f));
					mState = eBradV2State::Attack1;
					break;
				case 2:
					mAnimator->Play(L"BradV2Attack2Left", false);
					colObj = object::Instantiate<MonsterColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::MonsterColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-330.0f, -230.0f));
					collider3->SetSize(Vector2(430.0f, 230.0f));
					mState = eBradV2State::Attack2;
					break;
				case 3:
					mAnimator->Play(L"Attack3SliceLeft", false);
					colObj = object::Instantiate<MonsterColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::MonsterColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-330.0f, -230.0f));
					collider3->SetSize(Vector2(430.0f, 230.0f));
					mState = eBradV2State::Attack3_Slice;
					break;
				case 4:
					mAnimator->Play(L"Attack5ReadyLeft", false);
					mState = eBradV2State::Attack5_Ready;
					break;
				case 5:
					mAnimator->Play(L"Attack6ReadyLeft", false);
					colObj = object::Instantiate<MonsterColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::MonsterColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-330.0f, -230.0f));
					collider3->SetSize(Vector2(430.0f, 230.0f));
					mState = eBradV2State::Attack6_Ready;
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
			monsterPos.x += 200 * Time::DeltaTime();
			if (monsterPos.x > playerPos.x)
				return;

			if (mTime > 3.0f)
			{
				switch (rand)
				{
				case 1:
					mAnimator->Play(L"BradV2Attack1Right", false);
					colObj = object::Instantiate<MonsterColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::MonsterColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-330.0f, -230.0f));
					collider3->SetSize(Vector2(430.0f, 230.0f));
					mState = eBradV2State::Attack1;
					break;
				case 2:
					mAnimator->Play(L"BradV2Attack2Right", false);
					colObj = object::Instantiate<MonsterColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::MonsterColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-330.0f, -230.0f));
					collider3->SetSize(Vector2(430.0f, 230.0f));
					mState = eBradV2State::Attack2;
					break;
				case 3:
					mAnimator->Play(L"Attack3SliceRight", false);
					colObj = object::Instantiate<MonsterColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::MonsterColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-330.0f, -230.0f));
					collider3->SetSize(Vector2(430.0f, 230.0f));
					mState = eBradV2State::Attack3_Slice;
					break;
				case 4:
					mAnimator->Play(L"Attack5ReadyRight", false);
					mState = eBradV2State::Attack5_Ready;
					break;
				case 5:
					mAnimator->Play(L"Attack6ReadyRight", false);
					colObj = object::Instantiate<MonsterColliderObj>(Vector2(tr->GetPos().x, tr->GetPos().y), eLayerType::MonsterColliderObj);
					collider3 = colObj->GetComponent<Collider>();
					collider3->SetCenter(Vector2(-330.0f, -230.0f));
					collider3->SetSize(Vector2(430.0f, 230.0f));
					mState = eBradV2State::Attack6_Ready;
					break;
				default:
					break;
				}
				mTime = 0;
			}
		}
		tr->SetPos(monsterPos);
	}

	void BradV2::attack1()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		mMovementTime += Time::DeltaTime();

		if (mbLeft)
		{
			monsterPos.x -= 200 * Time::DeltaTime();
			collider3->SetCenter(Vector2((-200.0f * mMovementTime) - 130.0f, -120.0f));
			collider3->SetSize(Vector2(270.0f, 120.0f));
		}
		if (mbRight)
		{
			monsterPos.x += 200 * Time::DeltaTime();
			collider3->SetCenter(Vector2((200.0f * mMovementTime) - 130.0f, -120.0f));
			collider3->SetSize(Vector2(270.0f, 120.0f));
		}

		if (mAnimator->IsComplete() && mbRight)
		{
			object::Destory(colObj);
			mAnimator->Play(L"BradV2IdleRight", true);
			mState = eBradV2State::Idle;
			mMovementTime = 0.0f;
		}
		if (mAnimator->IsComplete() && mbLeft)
		{
			object::Destory(colObj);
			mAnimator->Play(L"BradV2IdleLeft", true);
			mState = eBradV2State::Idle;
			mMovementTime = 0.0f;
		}
		tr->SetPos(monsterPos);
	}

	void BradV2::attack2()
	{
		if (mAnimator->IsComplete() && mbRight)
		{
			object::Destory(colObj);
			mAnimator->Play(L"BradV2IdleRight", true);
			collider->SetCenter(Vector2(-90.0f, -240.0f));
			collider->SetSize(Vector2(180.0f, 250.0f));
			mState = eBradV2State::Idle;
		}
		if (mAnimator->IsComplete() && mbLeft)
		{
			object::Destory(colObj);
			mAnimator->Play(L"BradV2IdleLeft", true);
			collider->SetCenter(Vector2(-90.0f, -240.0f));
			collider->SetSize(Vector2(180.0f, 250.0f));
			mState = eBradV2State::Idle;
		}
	}

	void BradV2::attack3_slice()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		if (mbLeft)
		{
			monsterPos.x -= 200 * Time::DeltaTime();
		}
		if (mbRight)
		{
			monsterPos.x += 200 * Time::DeltaTime();
		}

		if (mAnimator->IsComplete() && mbRight)
		{
			mAnimator->Play(L"Attack3PunchRight", false);
			collider->SetCenter(Vector2(-90.0f, -240.0f));
			collider->SetSize(Vector2(180.0f, 250.0f));
			mState = eBradV2State::Attack3_Punch;
		}
		if (mAnimator->IsComplete() && mbLeft)
		{
			mAnimator->Play(L"Attack3PunchLeft", false);
			collider->SetCenter(Vector2(-90.0f, -240.0f));
			collider->SetSize(Vector2(180.0f, 250.0f));
			mState = eBradV2State::Attack3_Punch;
		}
		tr->SetPos(monsterPos);
	}

	void BradV2::attack3_punch()
	{
		if (mAnimator->IsComplete() && mbRight)
		{
			object::Destory(colObj);
			mAnimator->Play(L"BradV2IdleRight", true);
			collider->SetCenter(Vector2(-90.0f, -240.0f));
			collider->SetSize(Vector2(180.0f, 250.0f));
			mState = eBradV2State::Idle;
		}
		if (mAnimator->IsComplete() && mbLeft)
		{
			object::Destory(colObj);
			mAnimator->Play(L"BradV2IdleLeft", true);
			collider->SetCenter(Vector2(-90.0f, -240.0f));
			collider->SetSize(Vector2(180.0f, 250.0f));
			mState = eBradV2State::Idle;
		}
	}

	void BradV2::attack5_ready()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		if (mAnimator->IsComplete())
		{
			if (mbLeft)
			{
				mAnimator->Play(L"Attack5FireLeft", false);
				mLazer = object::Instantiate<Lazer>(Vector2(monsterPos.x - 1070.0f, monsterPos.y-130.0f), eLayerType::Lazer);
				mState = eBradV2State::Attack5_Fire;
			}
			if (mbRight)
			{
				mAnimator->Play(L"Attack5FireRight", false);
				mLazer = object::Instantiate<Lazer>(Vector2(monsterPos.x + 100.0f, monsterPos.y - 130.0f), eLayerType::Lazer);
				
				mState = eBradV2State::Attack5_Fire;
			}
		}
	}

	void BradV2::attack5_fire()
	{
		if (mAnimator->IsComplete())
		{
			if (mbLeft)
			{
				mAnimator->Play(L"BradV2IdleLeft", true);
				object::Destory(mLazer);
				mState = eBradV2State::Idle;
			}
			if (mbRight)
			{
				mAnimator->Play(L"BradV2IdleRight", true);
				object::Destory(mLazer);
				mState = eBradV2State::Idle;
			}
		}
	}

	void BradV2::attack6_ready()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 monsterPos = tr->GetPos();

		Transform* playTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playTr->GetPos();

		if (mAnimator->IsComplete())
		{
			if (mbLeft)
			{
				object::Destory(colObj);
				mAnimator->Play(L"Attack6FireLeft", false);
				mLazer = object::Instantiate<Lazer>(Vector2(monsterPos.x - 1070.0f, monsterPos.y - 100.0f), eLayerType::Lazer);
				mState = eBradV2State::Attack6_Fire;
			}
			if (mbRight)
			{
				object::Destory(colObj);
				mAnimator->Play(L"Attack6FireRight", false);
				mLazer = object::Instantiate<Lazer>(Vector2(monsterPos.x + 100.0f, monsterPos.y - 100.0f), eLayerType::Lazer);

				mState = eBradV2State::Attack6_Fire;
			}
		}
	}

	void BradV2::attack6_fire()
	{
		if (mAnimator->IsComplete())
		{
			if (mbLeft)
			{
				mAnimator->Play(L"BradV2IdleLeft", true);
				object::Destory(mLazer);
				mState = eBradV2State::Idle;
			}
			if (mbRight)
			{
				mAnimator->Play(L"BradV2IdleRight", true);
				object::Destory(mLazer);
				mState = eBradV2State::Idle;
			}
		}
	}
}