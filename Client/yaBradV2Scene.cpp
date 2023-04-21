#include "yaBradV2Scene.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaGround.h"
#include "yaBradV2.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaBGImageObject.h"
#include "yaPlayer.h"

namespace ya
{
	BradV2Scene::BradV2Scene()
	{
	}

	BradV2Scene::~BradV2Scene()
	{
	}

	void BradV2Scene::Initialize()
	{
		Scene::Initialize();
		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		//BGImageObject* bgImage = new BGImageObject();
		bgImage->SetImage(L"BradBG", L"BradBG.bmp");
		//mBgImage = Resources::Load<Image>(L"BradBG", L"..\\Resources\\HaND_Resource\\Map\\BradBG.bmp");
		this->AddGameObeject(gPlayer, eLayerType::Player);
		BradV2* bradV2 = object::Instantiate<BradV2>(Vector2(800.0f, 650.0f), eLayerType::Monster);

		Ground* ground = object::Instantiate<Ground>(Vector2(0.0f, 0.0f), eLayerType::Ground);
		ground->SetPlayer(gPlayer);
	}

	void BradV2Scene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Waldo);
		}

		Scene::Update();
	}

	void BradV2Scene::Render(HDC hdc)
	{
		//TransparentBlt(hdc, 0, 0
		//	, application.GetWidth(), application.GetHeight()
		//	, mBgImage->GetHdc()
		//	, 0, 0
		//	, mBgImage->GetWidth(), mBgImage->GetHeight()
		//	, RGB(255, 0, 255));

		Scene::Render(hdc);
	}

	void BradV2Scene::Release()
	{
		Scene::Release();
	}

	void BradV2Scene::OnEnter()
	{
	}

	void BradV2Scene::OnExit()
	{
	}

}