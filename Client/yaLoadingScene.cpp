#include "yaLoadingScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaLoading.h"
#include "yaObject.h"
#include "yaScene.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSound.h"

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
		gSound->Stop(true);

		if (SceneManager::GetPrevScene()->GetSceneType() ==  eSceneType::Title)
		{
			if (loading->GetComponent<Animator>()->IsComplete())
			{
				object::Destory(loading);
				gSound = Resources::Load<Sound>(L"PlayTheme", L"..\\Resources\\Sound\\y2mate.com-Have-A-Nice-Death-OST-CEOs-Office.wav");
				gSound->Play(true);
				SceneManager::LoadScene(eSceneType::Play);
				return;
			}
		}

		if (SceneManager::GetPrevScene()->GetSceneType() == eSceneType::Play)
		{
			if (loading->GetComponent<Animator>()->IsComplete())
			{
				object::Destory(loading);
				gSound = Resources::Load<Sound>(L"HungTheme", L"..\\Resources\\Sound\\y2mate.com-Have-A-Nice-Death-OST-W-Hung.wav");
				gSound->Play(true);
				SceneManager::LoadScene(eSceneType::Hung);
				return;
			}
		}

		if (SceneManager::GetPrevScene()->GetSceneType() == eSceneType::Hung)
		{
			if (loading->GetComponent<Animator>()->IsComplete())
			{
				object::Destory(loading);
				gSound = Resources::Load<Sound>(L"BradTheme", L"..\\Resources\\Sound\\y2mate.com-Have-A-Nice-Death-OST-Brad-Theme-1.wav");
				gSound->Play(true);
				SceneManager::LoadScene(eSceneType::Brad);
				return;
			}
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
