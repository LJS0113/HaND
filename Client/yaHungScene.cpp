#include "yaHungScene.h"
#include "yaBradScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaGround.h"
#include "yaObject.h"
#include "yaBrad.h"
#include "yaApplication.h"
#include "yaResources.h"
#include "yaHung.h"
#include "yaBGImageObject.h"

extern ya::Application application;

namespace ya
{
	HungScene::HungScene()
	{
	}
	HungScene::~HungScene()
	{
	}
	void HungScene::Initialize()
	{
		Scene::Initialize();
		//mBgImage = Resources::Load<Image>(L"HungBG", L"..\\Resources\\HaND_Resource\\Map\\HungBG.bmp");
		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"HungBG", L"HungBG.bmp");
		Player* player = object::Instantiate<Player>(Vector2(500.0f, 400.0f), eLayerType::Player);
		Hung* hung = object::Instantiate<Hung>(Vector2(500.0f, 400.0f), eLayerType::Monster);

		Ground* ground = object::Instantiate<Ground>(Vector2(0.0f, 0.0f), eLayerType::Ground);
		ground->SetPlayer(player);
	}
	void HungScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Brad);
		}
		Scene::Update();
	}
	void HungScene::Render(HDC hdc)
	{
		//TransparentBlt(hdc, 0, 0
		//	, application.GetWidth(), application.GetHeight()
		//	, mBgImage->GetHdc()
		//	, 0, 0
		//	, mBgImage->GetWidth(), mBgImage->GetHeight()
		//	, RGB(255, 0, 255));

		Scene::Render(hdc);
	}
	void HungScene::Release()
	{
		Scene::Release();
	}
	void HungScene::OnEnter()
	{
	}
	void HungScene::OnExit()
	{
	}
}