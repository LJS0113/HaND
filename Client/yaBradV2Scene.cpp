#include "yaBradV2Scene.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaGround.h"
#include "yaBradV2.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaBGImageObject.h"
#include "yaPlayer.h"
#include "yaCollisionManager.h"
#include "yaBrad.h"
#include "yaLifebar.h"

namespace ya
{
	BradV2Scene::BradV2Scene()
		: mType(eSceneType::BradV2)
	{
	}

	BradV2Scene::~BradV2Scene()
	{
	}

	void BradV2Scene::Initialize()
	{
		Ground* ground = object::Instantiate<Ground>(Vector2(-300.0f, 800.0f), eLayerType::Ground);
		ground->SetPlayer(gPlayer);

		BGImageObject* bgImage = object::Instantiate<BGImageObject>(Vector2(0.0f, 0.0f), eLayerType::BG);
		bgImage->SetImage(L"BradBG", L"BradBG.bmp");

		Transform* bradTr = gBrad->GetComponent<Transform>();
		Vector2 bradPos = bradTr->GetPos();

		Transform* playerTr = gPlayer->GetComponent<Transform>();
		Vector2 playerPos = playerTr->GetPos();

		BradV2* bradV2 = object::Instantiate<BradV2>(Vector2(bradPos.x, bradPos.y), eLayerType::Monster);
		gPlayer = object::Instantiate<Player>(Vector2(playerPos.x, playerPos.y), eLayerType::Player);
		gPlayer->SetHpCount(100.0f);
		gLifebar = object::Instantiate<Lifebar>(Vector2(1300.0f, 850.0f), eLayerType::UI);
		gLifebar->SetBossLifebar(true);
		gLifebar->SetPlayerIconImage(L"PlayerIcon", L"Player.bmp");
		gLifebar->SetBossIconImage(L"BradV2Icon", L"BradV2.bmp");
		gLifebar->SetPlayerAttackCount(0.0f);
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
		Scene::Render(hdc);
	}

	void BradV2Scene::Release()
	{
		Scene::Release();
	}

	void BradV2Scene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterColliderObj, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::ColliderObj, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Lazer, true);
	}

	void BradV2Scene::OnExit()
	{
	}

}