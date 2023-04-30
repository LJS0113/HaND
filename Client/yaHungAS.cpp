#include "yaHungAS.h"
#include "yaAnimator.h"
#include "yaObject.h"
#include "yaCollider.h"



namespace ya
{
	HungAS::HungAS()
		: mLayerType(eLayerType::HungAS)
	{
	}
	HungAS::~HungAS()
	{
	}
	void HungAS::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Monster\\Hung\\AttackSpecial\\FX", Vector2::Zero, 0.2f);

		mAnimator->Play(L"HungAttackSpecialFX", false);

		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-15.0f, -1400.0f));
		collider->SetSize(Vector2(35.0f, 1200.0f));

		GameObject::Initialize();
	}
	void HungAS::Update()
	{
		GameObject::Update();
		if (mAnimator->IsComplete())
			object::Destory(this);
	}
	void HungAS::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void HungAS::Release()
	{
		GameObject::Release();
	}
}