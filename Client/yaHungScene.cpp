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

extern ya::Player* gPlayer;

namespace ya
{
	HungScene::HungScene()
	{
	}
	HungScene::~HungScene()
	{
	}
	void HungScene::Initialize()
	{
		//Scene::Initialize();

		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"HungBG", L"HungBG.bmp");

		hung = object::Instantiate<Hung>(Vector2(1300.0f, 850.0f), eLayerType::Monster);
		gPlayer = object::Instantiate<Player>(Vector2(100.0f, 600.0f), eLayerType::Player);
		Ground* ground = object::Instantiate<Ground>(Vector2(-300.0f, 800.0f), eLayerType::Ground);
		ground->SetPlayer(gPlayer);

	}
	void HungScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Brad);
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

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterColliderObj, true);
		CollisionManager::SetLayer(eLayerType::ColliderObj, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::HungAS, true);
	}
	void HungScene::OnExit()
	{
	}
}