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

extern ya::Application application;
extern ya::Player* player;

namespace ya
{
	PlayeScene::PlayeScene()
	{
	}

	PlayeScene::~PlayeScene()
	{
	}

	void PlayeScene::Initialize()
	{
		Scene::Initialize();

		//Sound* mainTheme 
		//	= Resources::Load<Sound>(L"MainTheme", L"..\\Resources\\Sound\\BGTheme.wav");
		//mainTheme->Play(true);

		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"LobbyBG", L"LobbyBG.bmp");

		Elevator* elevator = object::Instantiate<Elevator>(Vector2(800.0f, 700.0f), eLayerType::BG);
		player = object::Instantiate<Player>(Vector2(100.0f, 700.0f), eLayerType::Player);
		Ground* ground = object::Instantiate<Ground>(Vector2(0.0f, 0.0f), eLayerType::Ground);
		ground->SetPlayer(player);

	}

	void PlayeScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Hung);
		}

		Scene::Update();
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
	}
	void PlayeScene::OnExit()
	{
		//mPlayer->SetPos(Vector2{ 0.0f, 0.0f });
	}
}
