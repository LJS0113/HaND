#include "yaLoadingScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaLoading.h"
#include "yaObject.h"
#include "yaTransform.h"

namespace ya
{
	LoadingScene::LoadingScene()
	{
	}

	LoadingScene::~LoadingScene()
	{
	}

	void LoadingScene::Initialize()
	{
		Scene::Initialize();

		Loading* loading = object::Instantiate<Loading>(Vector2(500.0f, 500.0f), eLayerType::UI);

	}

	void LoadingScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Play);
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
