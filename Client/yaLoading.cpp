#include "yaLoading.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaSceneManager.h"

namespace ya
{
	Loading::Loading()
	{
	}

	Loading::~Loading()
	{
	}

	void Loading::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 2.0f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Loading", Vector2(-100.0f, -100.0f), 0.1f);
		
		mAnimator->Play(L"ResourcesHaND_ResourceLoading", false);

		GameObject::Initialize();
	}

	void Loading::Update()
	{
		GameObject::Update();
		if (mAnimator->IsComplete())
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
	}

	void Loading::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Loading::Release()
	{
		GameObject::Release();
	}

}