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

extern ya::Player* gPlayer;

namespace ya
{
	BradScene::BradScene()
		: mTime(0.0f)
	{

	}

	BradScene::~BradScene()
	{
	}

	void BradScene::Initialize()
	{
		Scene::Initialize();

		//mBgImage = Resources::Load<Image>(L"BradBG", L"..\\Resources\\HaND_Resource\\Map\\BradBG.bmp");
		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"BradBG", L"BradBG.bmp");
		Brad* brad = object::Instantiate<Brad>(Vector2(1300.0f, 850.0f), eLayerType::Monster);
		Desk* desk = object::Instantiate<Desk>(Vector2(1300.0f, 850.0f), eLayerType::BG);
		//AddGameObeject(gPlayer, eLayerType::Player);
		gPlayer = object::Instantiate<Player>(Vector2(300.0f, 850.0f), eLayerType::Player);

		Ground* ground = object::Instantiate<Ground>(Vector2(-100.0f, 800.0f), eLayerType::Ground);
		ground->SetPlayer(gPlayer);

		Scene::Initialize();
	}

	void BradScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::BradV2);
			//SceneManager::GetActiveScene()->Initialize();
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
	}

	void BradScene::OnExit()
	{
	}

}