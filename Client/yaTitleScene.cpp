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

		BGImageObject* bgLogoImage = object::Instantiate<BGImageObject>(Vector2(100.0f, 100.0f), eLayerType::BG);
		bgLogoImage->SetImage(L"TitleLogoBG", L"Logo.bmp");
		bgLogoImage->SetScale(Vector2(0.5f, 0.5f));

		LogoPlayer* logoPlayerWeapon = object::Instantiate<LogoPlayer>(Vector2(1100.0f, 800.0f), eLayerType::Player);
		logoPlayerWeapon->SetPath(L"LogoTitlePlayerHomeScreenWeapon");
		LogoPlayer* logoPlayerBody = object::Instantiate<LogoPlayer>(Vector2(1280.0f, 800.0f), eLayerType::Player);
		logoPlayerBody->SetPath(L"LogoTitlePlayerHomeScreenBody");
		LogoPlayer* logoPlayerArm = object::Instantiate<LogoPlayer>(Vector2(1320.0f, 670.0f), eLayerType::Player);
		logoPlayerArm->SetPath(L"LogoTitlePlayerHomeScreenArm");
		LogoPlayer* logoPlayerHead = object::Instantiate<LogoPlayer>(Vector2(1300.0f, 500.0f), eLayerType::Player);
		logoPlayerHead->SetPath(L"LogoTitlePlayerHomeScreenHead");

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
		Scene::Render(hdc);
	}
	void TitleScene::Release()
	{
		Scene::Release();
	}
	void TitleScene::OnEnter()
	{
		//CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
	}
	void TitleScene::OnExit()
	{
	}
}
