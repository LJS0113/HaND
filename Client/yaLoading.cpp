#include "yaLoading.h"
#include "yaTransform.h"
#include "yaAnimator.h"

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
		tr->SetScale(Vector2(1.0f, 1.0f));

		//mImage = Resources::Load<Image>(L"TitlePlayer", L"..\\Resources\\HaND_Resource\\Title_Player_tea.bmp");
		//mAnimator = AddComponent<Animator>();
		//mAnimator->CreateAnimation(L"Idle", mImage, Vector2(0.0f, 0.0f), 9, 1, 9, Vector2(30.0f, 30.0f), 0.1f);

		//mAnimator->Play(L"Idle", true);


		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Loading", Vector2(0.0f, 0.0f), 0.1f);
		mAnimator->Play(L"HaND_ResourceLoading", true);


		GameObject::Initialize();
	}

	void Loading::Update()
	{
		GameObject::Update();
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