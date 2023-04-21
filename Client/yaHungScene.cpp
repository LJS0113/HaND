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
		Scene::Initialize();
		
		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"HungBG", L"HungBG.bmp");

		Hung* hung = object::Instantiate<Hung>(Vector2(800.0f, 650.0f), eLayerType::Monster);
		this->AddGameObeject(gPlayer, eLayerType::Player);
	
		Ground* ground = object::Instantiate<Ground>(Vector2(0.0f, 0.0f), eLayerType::Ground);
		ground->SetImage(L"BossGround", L"BossGround.bmp");
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::HungAS, true);

	}
	void HungScene::OnExit()
	{
	}
}