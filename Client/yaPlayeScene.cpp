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

extern ya::Application application;

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

		//mBgImage = Resources::Load<Image>(L"LobbyBG", L"..\\Resources\\HaND_Resource\\Map\\LobbyBG.bmp");

		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"LobbyBG", L"LobbyBG.bmp");

		Player* player = object::Instantiate<Player>(Vector2(500.0f, 400.0f), eLayerType::Player);
		//object::Instantiate<Monster>(Vector2(500.0f, 500.0f), eLayerType::Player);
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
		//TransparentBlt(hdc, 0, 0
		//	, 1600, application.GetHeight()
		//	, mBgImage->GetHdc()
		//	, 0, 0
		//	, mBgImage->GetWidth(), mBgImage->GetHeight()
		//	, RGB(255, 0, 255));
		//Super::Tick();
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
