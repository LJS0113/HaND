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
		tr->SetScale(Vector2(2.5f, 2.5f));

		mImage = Resources::Load<Image>(L"TitlePlayer", L"..\\Resources\\HaND_Resource\\Title_Player_tea.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Idle", mImage, Vector2(0.0f, 0.0f), 9, 1, 9, Vector2(0.0f, 0.0f), 0.1f);

		mAnimator->Play(L"Idle", true);

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
