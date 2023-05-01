#include "yaLoadingScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaLoading.h"
#include "yaObject.h"
#include "yaScene.h"
#include "yaTransform.h"

namespace ya
{
	LoadingScene::LoadingScene()
		: mType(eSceneType::Loading)
	{
	}

	LoadingScene::~LoadingScene()
	{
	}

	void LoadingScene::Initialize()
	{
		loading = object::Instantiate<Loading>(Vector2(800.0f, 450.0f), eLayerType::UI);
	}

	void LoadingScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			object::Destory(loading);
			SceneManager::LoadScene(eSceneType::Play);
		}

		if (SceneManager::GetPrevScene()->GetSceneType() == eSceneType::Play)
		{
			object::Destory(loading);
			SceneManager::LoadScene(eSceneType::Hung);
			return;
		}

		if (SceneManager::GetPrevScene()->GetSceneType() == eSceneType::Hung)
		{
			object::Destory(loading);
			SceneManager::LoadScene(eSceneType::Brad);
			return;
		}

		if (SceneManager::GetPrevScene()->GetSceneType() == eSceneType::Brad)
		{
			object::Destory(loading);
			SceneManager::LoadScene(eSceneType::BradV2);
			return;
		}
	}

	void LoadingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void LoadingScene::Release()
	{
		Scene::Release();
	}


	void LoadingScene::OnEnter()
	{
	}
	void LoadingScene::OnExit()
	{
	}
}
