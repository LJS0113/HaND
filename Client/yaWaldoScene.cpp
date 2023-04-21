#pragma once
#include "yaWaldoScene.h"
#include "yaBradScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaGround.h"
#include "yaObject.h"
#include "yaBrad.h"
#include "yaApplication.h"
#include "yaResources.h"
#include "yaBGImageObject.h"

extern ya::Application application;

namespace ya
{
	WaldoScene::WaldoScene()
	{
	}
	WaldoScene::~WaldoScene()
	{
	}
	void WaldoScene::Initialize()
	{
		Scene::Initialize();
		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"WaldoBG", L"WaldoBG.bmp");
		//mBgImage = Resources::Load<Image>(L"WaldoBG", L"..\\Resources\\HaND_Resource\\Map\\WaldoBG.bmp");

		//player = object::Instantiate<Player>(Vector2(1000.0f, 500.0f), eLayerType::Player);
		////Brad* brad = object::Instantiate<Brad>(Vector2(500.0f, 400.0f), eLayerType::Monster);

		//Ground* ground = object::Instantiate<Ground>(Vector2(0.0f, 0.0f), eLayerType::Ground);
		//ground->SetPlayer(player);


	}
	void WaldoScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}
		Scene::Update();
	}
	void WaldoScene::Render(HDC hdc)
	{
		//TransparentBlt(hdc, 0, 0
		//	, application.GetWidth(), application.GetHeight()
		//	, mBgImage->GetHdc()
		//	, 0, 0
		//	, mBgImage->GetWidth(), mBgImage->GetHeight()
		//	, RGB(255, 0, 255));

		Scene::Render(hdc);
	}
	void WaldoScene::Release()
	{
		Scene::Release();
	}

	void WaldoScene::OnEnter()
	{
	} 
	void WaldoScene::OnExit()
	{
	}
}