#include "yaLogoPlayer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaTransform.h"
#include "yaObject.h"

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

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Logo\\TitlePlayer\\HomeScreenHead", Vector2(0.0f, 0.0f), 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Logo\\TitlePlayer\\HomeScreenBody", Vector2(0.0f, 0.0f), 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Logo\\TitlePlayer\\HomeScreenArm", Vector2(0.0f, 0.0f), 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Logo\\TitlePlayer\\HomeScreenWeapon", Vector2(0.0f, 0.0f), 0.05f);
		mAnimator->Play(L"LogoTitlePlayerHomeScreenHead", true);

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

	void LogoPlayer::SetPath(const std::wstring& path)
	{
		mAnimator->Play(path, true);
	}

}
