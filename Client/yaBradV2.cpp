#include "yaBradV2.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	BradV2::BradV2()
	{
	}

	BradV2::~BradV2()
	{
	}

	void BradV2::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Idle\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\BradV2\\Idle\\Right", Vector2::Zero, 0.1f);

		mAnimator->Play(L"BradV2IdleRight", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-60.0f, -80.0f));

		GameObject::Initialize();
	}

	void BradV2::Update()
	{
		GameObject::Update();
	}

	void BradV2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BradV2::Release()
	{
		GameObject::Release();
	}

} 