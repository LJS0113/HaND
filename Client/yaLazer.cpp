#include "yaLazer.h"
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTransform.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	Lazer::Lazer()
	{
	}
	Lazer::~Lazer()
	{
	}
	void Lazer::Initialize()
	{
		mImage = Resources::Load<Image>(L"Lazer", L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\FX\\Lazer\\Lazer_01.bmp");

		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(0.0f, 0.0f));
		collider->SetSize(Vector2(mImage->GetWidth(), mImage->GetHeight()));
		GameObject::Initialize();
	}
	void Lazer::Update()
	{
		GameObject::Update();
	}
	void Lazer::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
	void Lazer::Release()
	{
		GameObject::Release();
	}
	void Lazer::OnCollisionEnter(Collider* other)
	{
	}
	void Lazer::OnCollisionStay(Collider* other)
	{
	}
	void Lazer::OnCollisionExit(Collider* other)
	{
	}
}