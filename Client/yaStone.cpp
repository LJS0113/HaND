#include "yaStone.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaTransform.h"
#include "yaTime.h"

namespace ya
{
	Stone::Stone()
		: mLayerType(eLayerType::Stone)
	{
	}

	Stone::~Stone()
	{
	}

	void Stone::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\FX\\Falling_Rock\\Idle", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Brad\\FX\\Falling_Rock\\Impact", Vector2::Zero, 0.1f);

		mAnimator->Play(L"FXFalling_RockIdle", false);

		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-70.0f, -100.0f));
		collider->SetSize(Vector2(150.0f, 150.0f));

		GameObject::Initialize();

	}

	void Stone::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.y += 600 * Time::DeltaTime();
		tr->SetPos(pos);
		if (mAnimator->IsComplete())
			object::Destory(this);
	}

	void Stone::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Stone::Release()
	{
		GameObject::Release();
	}

	void Stone::OnCollisionEnter(Collider* other)
	{
	}

	void Stone::OnCollisionStay(Collider* other)
	{
	}

	void Stone::OnCollisionExit(Collider* other)
	{
	}

}