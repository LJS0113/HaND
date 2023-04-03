#include "yaPlayeScene.h"
#include "yaCuphead.h"
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

		Cuphead* player = object::Instantiate<Cuphead>(Vector2(500.0f, 400.0f), eLayerType::Player);
		//object::Instantiate<Monster>(Vector2(500.0f, 500.0f), eLayerType::Player);
		Ground* ground = object::Instantiate<Ground>(Vector2(0.0f, 0.0f), eLayerType::Ground);
		ground->SetPlayer(player);
	}

	void PlayeScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}

	void PlayeScene::Render(HDC hdc)
	{
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
		//mCuphead->SetPos(Vector2{ 0.0f, 0.0f });
	}
}
