#include "yaLogoPlayer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaTransform.h"

namespace ya
{
	LogoPlayer::LogoPlayer()
	{
	}

	LogoPlayer::~LogoPlayer()
	{
	}

	void LogoPlayer::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.0f, 1.0f));

		//mImage = Resources::Load<Image>(L"TitlePlayer", L"..\\Resources\\HaND_Resource\\Title_Player_tea.bmp");
		//mAnimator = AddComponent<Animator>();
		//mAnimator->CreateAnimation(L"Idle", mImage, Vector2(0.0f, 0.0f), 9, 1, 9, Vector2(30.0f, 30.0f), 0.1f);

		//mAnimator->Play(L"Idle", true);

		//Animator* mArmAnimator;
		//Animator* mBodyAnimator;
		//Animator* mWeaponAnimator;
		//Animator* mSmokeAnimator;
		
		mHead = new GameObject();
		mHeadAnimator = AddComponent<Animator>();
		mHeadAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\TitlePlayer\\HomeScreenHead", Vector2(0.0f, 0.0f), 0.1f);
		mHeadAnimator->Play(L"HaND_ResourceTitlePlayerHomeScreenHead", true);
		tr->SetPos(Vector2(650.0f, 450.0f));

		//mBodyAnimator = AddComponent<Animator>();
		//mBodyAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\TitlePlayer\\HomeScreenBody", Vector2(0.0f, 0.0f), 0.1f);
		//mBodyAnimator->Play(L"TitlePlayerHomeScreenBody", true);
		//tr->SetPos(Vector2(650.0f, 850.0f));

		//mWeaponAnimator = AddComponent<Animator>();
		//mWeaponAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\TitlePlayer\\HomeScreenHead", Vector2(0.0f, 0.0f), 0.1f);
		//mWeaponAnimator->Play(L"TitlePlayerHomeScreenHead", true);

		//mSmokeAnimator = AddComponent<Animator>();
		//mSmokeAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\TitlePlayer\\HomeScreenHead", Vector2(0.0f, 0.0f), 0.1f);
		//mSmokeAnimator->Play(L"TitlePlayerHomeScreenHead", true);


		GameObject::Initialize();
	}

	void LogoPlayer::Update()
	{
		GameObject::Update();
	}

	void LogoPlayer::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void LogoPlayer::Release()
	{
		GameObject::Release();
	}

}
