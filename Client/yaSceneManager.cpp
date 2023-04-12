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
	//SceneManager scsene;
	//SceneManager* scsene = new SceneManager();
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

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
		
		for ( Scene* scene : mScenes )
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}

		mActiveScene = mScenes[(UINT)eSceneType::Title];
	}

	void SceneManager::Update()
	{
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
		mActiveScene->OnEnter();

		
	}
}
