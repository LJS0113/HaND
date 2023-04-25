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

extern ya::Player* gPlayer;

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
		Scene::Initialize();

		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"BradBG", L"BradBG.bmp");
		
		//AddGameObeject(gPlayer, eLayerType::Player);
		gPlayer = object::Instantiate<Player>(Vector2(400.0f, 850.0f), eLayerType::Player);
		
		BradV2* bradV2 = object::Instantiate<BradV2>(Vector2(800.0f, 650.0f), eLayerType::Monster);

		Ground* ground = object::Instantiate<Ground>(Vector2(-100.0f, 800.0f), eLayerType::Ground);
		ground->SetPlayer(gPlayer);
	}

	void BradV2Scene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Waldo);
			//SceneManager::GetActiveScene()->Initialize();
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
	}

	void BradV2Scene::OnExit()
	{
	}

}