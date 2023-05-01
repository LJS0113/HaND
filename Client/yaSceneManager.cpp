#include "yaSceneManager.h"
#include "yaPlayeScene.h"
#include "yaTitleScene.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaToolScene.h"
#include "yaLoadingScene.h"
#include "yaBradScene.h"
#include "yaBradV2Scene.h"
#include "yaHungScene.h"
#include "yaWaldoScene.h"


namespace ya
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Scene* SceneManager::mPrevScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::End);

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Loading] = new LoadingScene();
		mScenes[(UINT)eSceneType::Play] = new PlayeScene();
		mScenes[(UINT)eSceneType::Hung] = new HungScene();
		mScenes[(UINT)eSceneType::Brad] = new BradScene();
		mScenes[(UINT)eSceneType::BradV2] = new BradV2Scene();
		mScenes[(UINT)eSceneType::Waldo] = new WaldoScene();
		mScenes[(UINT)eSceneType::Tool] = new ToolScene();

		//for ( Scene* scene : mScenes )
		//{
		//	if (scene == nullptr)
		//		continue;

		//	scene->Initialize();
		//}
		mScenes[(UINT)eSceneType::Title]->Initialize();

		mActiveScene = mScenes[(UINT)eSceneType::Title];
	}

	void SceneManager::Update()
	{

		if (mActiveScene == mScenes[(UINT)eSceneType::Title])
		{
			mPrevScene = mScenes[(UINT)eSceneType::Title];
		}
		if (mActiveScene == mScenes[(UINT)eSceneType::Play])
		{
			mPrevScene = mScenes[(UINT)eSceneType::Play];
		}
		if (mActiveScene == mScenes[(UINT)eSceneType::Hung])
		{
			mPrevScene = mScenes[(UINT)eSceneType::Hung];
		}
		if (mActiveScene == mScenes[(UINT)eSceneType::Brad])
		{
			mPrevScene = mScenes[(UINT)eSceneType::Brad];
		}
		if (mActiveScene == mScenes[(UINT)eSceneType::BradV2])
		{
			mPrevScene = mScenes[(UINT)eSceneType::BradV2];
		}
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			delete scene;
			scene = nullptr;
		}
	}

	void SceneManager::LoadScene(eSceneType type)
	{
		Camera::Clear();

		// ÇöÀç¾À
		mActiveScene->OnExit();
		CollisionManager::Clear();
		//´ÙÀ½¾À
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->Initialize();
		mActiveScene->OnEnter();
	}
}
