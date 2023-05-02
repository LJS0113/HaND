#pragma once
#include "yaBradScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaGround.h"
#include "yaObject.h"
#include "yaBrad.h"
#include "yaApplication.h"
#include "yaResources.h"
#include "yaBGImageObject.h"
#include "yaPlayer.h"
#include "yaCollisionManager.h"
#include "yaDesk.h"
#include "yaTime.h"
#include "yaLifebar.h"

namespace ya
{
	BradScene::BradScene()
		: mTime(0.0f)
		, mType(eSceneType::Brad)
	{

	}

	BradScene::~BradScene()
	{
	}

	void BradScene::Initialize()
	{
		Ground* ground = object::Instantiate<Ground>(Vector2(-300.0f, 800.0f), eLayerType::Ground);
		ground->SetPlayer(gPlayer);

		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"BradBG", L"BradBG.bmp");

		gBrad = object::Instantiate<Brad>(Vector2(1300.0f, 850.0f), eLayerType::Monster);
		Desk* desk = object::Instantiate<Desk>(Vector2(1300.0f, 850.0f), eLayerType::BG);
		gPlayer = object::Instantiate<Player>(Vector2(100.0f, 700.0f), eLayerType::Player);
		gPlayer->SetHpCount(100.0f);
		gLifebar = object::Instantiate<Lifebar>(Vector2(1300.0f, 850.0f), eLayerType::UI);
		gLifebar->SetBossLifebar(true);
		gLifebar->SetPlayerIconImage(L"PlayerIcon", L"Player.bmp");
		gLifebar->SetBossIconImage(L"BradIcon", L"Brad.bmp");
		gLifebar->SetPlayerAttackCount(0.0f);
	}

	void BradScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::BradV2);
		}	
		Scene::Update();

	}

	void BradScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void BradScene::Release()
	{
		Scene::Release();
	}

	void BradScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterColliderObj, true);
		CollisionManager::SetLayer(eLayerType::ColliderObj, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Stone, true);
	}

	void BradScene::OnExit()
	{
	}

}