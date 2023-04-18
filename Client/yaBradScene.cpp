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
	BradScene::BradScene()
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
		Player* player = object::Instantiate<Player>(Vector2(200.0f, 200.0f), eLayerType::Player);
		Brad* brad = object::Instantiate<Brad>(Vector2(800.0f, 650.0f), eLayerType::Monster);

		Ground* ground = object::Instantiate<Ground>(Vector2(0.0f, 0.0f), eLayerType::Ground);
		ground->SetPlayer(player);

		Scene::Initialize();
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
	}

	void BradScene::OnExit()
	{
	}

}