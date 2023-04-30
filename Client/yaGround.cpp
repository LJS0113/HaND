#pragma once
#include "yaGround.h"
#include "yaCollider.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaTransform.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaMonster.h"
#include "yaApplication.h"

extern ya::Application application;

namespace ya
{
	Ground::Ground()
		: mLayerType(eLayerType::Ground)
	{
	}

	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(3000.0f, 100.0f));

		mImage = Resources::Load<Image>(L"Ground", L"..\\Resources\\TitleGround.bmp");

		GameObject::Initialize();
	}

	void Ground::Update()
	{
		GameObject::Update();

		//Transform* playerTr = gPlayer->GetComponent<Transform>();

		//COLORREF color = mImage->GetPixel(playerTr->GetPos().x, playerTr->GetPos().y);

		//Rigidbody* rb = gPlayer->GetComponent<Rigidbody>();
		//if (color == RGB(255, 0, 255))
		//{
		//	rb->SetGround(true);

		//	Vector2 pos = playerTr->GetPos();
		//	pos.y -= 1;
		//	playerTr->SetPos(pos);
		//}
		//else
		//{
		//	rb->SetGround(false);
		//}

	}

	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();

		TransparentBlt(hdc, tr->GetPos().x, tr->GetPos().y
			, application.GetWidth(), application.GetHeight()
			, mImage->GetHdc()
			, 0, 0
			, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 255, 255));
	}

	void Ground::Release()
	{
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player == nullptr)
			return;

		Rigidbody* rb = player->GetComponent<Rigidbody>();
		rb->SetGround(true);

		Collider* cupheadCol = player->GetComponent<Collider>();
		Vector2 cupheadPos = cupheadCol->GetPos();

		Collider* groundCol = this->GetComponent<Collider>();
		Vector2 groundPos = groundCol->GetPos();

		float fLen = fabs(cupheadPos.y - groundPos.y);
		float fSize = (cupheadCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

		if (fLen < fSize)
		{
			Transform* cupTr = player->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();

			Vector2 cupPos = cupTr->GetPos();
			Vector2 grPos = grTr->GetPos();

			cupPos -= (fSize - fLen) - 1.0f;
			cupTr->SetPos(cupPos);
		}
	}

	void Ground::OnCollisionStay(Collider* other)
	{
	}

	void Ground::OnCollisionExit(Collider* other)
	{
	}

	void Ground::SetImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\";
		path += fileName;

		mImage = Resources::Load<Image>(key, path);
	}

	void Ground::SetSize(Vector2 size)
	{
		mCollider->SetSize(size);
	}

}
