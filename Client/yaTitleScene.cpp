#include "yaTitleScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaTransform.h"
#include "yaCamera.h"
#include "yaObject.h"
#include "yaImage.h"
#include "yaApplication.h"
#include "yaResources.h"
#include "yaComponent.h"
#include "yaAnimator.h"
#include "yaAnimation.h"
#include "yaGameObject.h"
#include "yaLogoPlayer.h"
#include "yaBGImageObject.h"

extern ya::Application application;

namespace ya
{
	TitleScene::TitleScene()
		: mBgLogoImage(nullptr)
		, mAnimator(nullptr)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		Scene::Initialize();

		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"TitleBG", L"TitleScene.bmp");

		//mBgLogoImage = Resources::Load<Image>(L"TitleLogo", L"..\\Resources\\HaND_Resource\\HaND_LOGO.bmp");

		LogoPlayer* logoPlayer = object::Instantiate<LogoPlayer>(Vector2(650.0f, 450.0f), eLayerType::Player);

	}
	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Loading);
		}

	}
	void TitleScene::Render(HDC hdc)
	{
		//TransparentBlt(hdc, 50, 50
		//	, mBgLogoImage->GetWidth()/3, mBgLogoImage->GetHeight()/3
		//	, mBgLogoImage->GetHdc()
		//	, 0, 0
		//	, mBgLogoImage->GetWidth(), mBgLogoImage->GetHeight()
		//	, RGB(255, 255, 255));

		Scene::Render(hdc);
	}
	void TitleScene::Release()
	{
		Scene::Release();
	}
	void TitleScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
	}
	void TitleScene::OnExit()
	{
	}
}
