#pragma once
#include "yaPlayeScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaTransform.h"
#include "yaCamera.h"
#include "yaObject.h"
#include "yaGround.h"
#include "yaSound.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaApplication.h"
#include "yaBGImageObject.h"
#include "yaElevator.h"
#include "yaLifebar.h"

namespace ya
{
	PlayeScene::PlayeScene()
		: mType(eSceneType::Play)
	{
	}

	PlayeScene::~PlayeScene()
	{
	}

	void PlayeScene::Initialize()
	{


		Ground* ground = object::Instantiate<Ground>(Vector2(-100.0f, 800.0f), eLayerType::Ground);
		ground->SetPlayer(gPlayer);

		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"LobbyBG", L"LobbyBG.bmp");

		gLifebar = object::Instantiate<Lifebar>(Vector2(50.0f, 50.0f), eLayerType::UI);
		gLifebar->SetPlayerIconImage(L"PlayerIcon", L"Player.bmp");

		Elevator* elevator = object::Instantiate<Elevator>(Vector2(1300.0f, 850.0f), eLayerType::Elevator);
		gPlayer = object::Instantiate<Player>(Vector2(100.0f, 850.0f), eLayerType::Player);

	}

	void PlayeScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Loading);
		}
	}

	void PlayeScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PlayeScene::Release()
	{
		Scene::Release();
	}
	void PlayeScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Elevator, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);

	}
	void PlayeScene::OnExit()
	{
	}
}
