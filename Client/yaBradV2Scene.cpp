#include "yaBradV2Scene.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaGround.h"
#include "yaBradV2.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaBGImageObject.h"
#include "yaPlayer.h"
#include "yaCollisionManager.h"



namespace ya
{
	BradV2Scene::BradV2Scene()
	{
	}

	BradV2Scene::~BradV2Scene()
	{
	}

	void BradV2Scene::Initialize()
	{
		//Scene::Initialize();


		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"BradBG", L"BradBG.bmp");
		
		BradV2* bradV2 = object::Instantiate<BradV2>(Vector2(1300.0f, 850.0f), eLayerType::Monster);
		gPlayer = object::Instantiate<Player>(Vector2(100.0f, 600.0f), eLayerType::Player);
		Ground* ground = object::Instantiate<Ground>(Vector2(-300.0f, 800.0f), eLayerType::Ground);
		ground->SetPlayer(gPlayer);
	}

	void BradV2Scene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Waldo);
		}

		Scene::Update();
	}

	void BradV2Scene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void BradV2Scene::Release()
	{
		Scene::Release();
	}

	void BradV2Scene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ColliderObj, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::ColliderObj, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Lazer, true);
	}

	void BradV2Scene::OnExit()
	{
	}

}