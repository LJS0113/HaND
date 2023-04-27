#include "yaLazer.h"
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaCollider.h"


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
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\FX\\Lazer", Vector2::Zero, 0.1f);

		mAnimator->Play(L"BradV2FXLazer", false);
		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-70.0f, -100.0f));
		collider->SetSize(Vector2(150.0f, 150.0f));

		GameObject::Initialize();
	}
	void Lazer::Update()
	{
		GameObject::Update();
	}
	void Lazer::Render(HDC hdc)
	{
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