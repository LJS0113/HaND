#pragma once
#include "yaHungScene.h"
#include "yaBradScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaGround.h"
#include "yaObject.h"
#include "yaBrad.h"
#include "yaApplication.h"
#include "yaResources.h"
#include "yaHung.h"
#include "yaBGImageObject.h"
#include "yaCollisionManager.h"
#include "yaPlayer.h"
#include "yaScene.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaElevator.h"
#include "yaLifebar.h"
#include "yaSound.h"

extern ya::Player* gPlayer;

namespace ya
{
	HungScene::HungScene()
		: mType(eSceneType::Hung)
		, mTime(0.0f)
	{
	}
	HungScene::~HungScene()
	{
	}
	void HungScene::Initialize()
	{
		//Scene::Initialize();


		Ground* ground = object::Instantiate<Ground>(Vector2(-300.0f, 800.0f), eLayerType::Ground);
		ground->SetPlayer(gPlayer);

		elevator = object::Instantiate<Elevator>(Vector2(100.0f, 850.0f), eLayerType::Elevator);

		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"HungBG", L"HungBG.bmp");

		hung = object::Instantiate<Hung>(Vector2(1400.0f, 850.0f), eLayerType::Monster);
		mEleState = eElevatorState::In;

		gLifebar = object::Instantiate<Lifebar>(Vector2(1300.0f, 850.0f), eLayerType::UI);
		gLifebar->SetBossLifebar(true);
		gLifebar->SetPlayerIconImage(L"PlayerIcon", L"Player.bmp");
		gLifebar->SetBossIconImage(L"HungIcon", L"Hung.bmp");
		gLifebar->SetPlayerAttackCount(0.0f);
	}
	void HungScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Loading);
		}
		switch (mEleState)
		{
		case eElevatorState::In:
			eleIn();
			break;
		case eElevatorState::Out:
			eleOut();
			break;
		case eElevatorState::Disappear:
			eleDisappear();
			break;
		case eElevatorState::End:
			break;
		default:
			break;
		}

		Scene::Update();
	}
	void HungScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void HungScene::Release()
	{
		Scene::Release();
	}
	void HungScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Elevator, true);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterColliderObj, true);
		CollisionManager::SetLayer(eLayerType::ColliderObj, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::HungAS, true);
	}
	void HungScene::OnExit()
	{
	}
	void HungScene::eleIn()
	{
		if (elevator->GetComponent<Animator>()->IsComplete())
		{
			gPlayer = object::Instantiate<Player>(Vector2(150.0f, 850.0f), eLayerType::Player);
			mEleState = eElevatorState::Out;
		}
	}
	void HungScene::eleOut()
	{
		mTime += Time::DeltaTime();
		if (mTime > 2.0f)
		{
			elevator->GetComponent<Animator>()->Play(L"MapElevatorOut", false);
			mEleState = eElevatorState::Disappear;
		}
	}
	void HungScene::eleDisappear()
	{
		if (elevator->GetComponent<Animator>()->IsComplete())
		{
			object::Destory(elevator);
			mEleState = eElevatorState::End;
		}
		
	}
}