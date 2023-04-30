#include "yaMonsterColliderObj.h"
#include "yaCollider.h"

namespace ya
{
	MonsterColliderObj::MonsterColliderObj()
		: mTime(0.0f)
		, mLayerType(eLayerType::MonsterColliderObj)
	{
	}
	MonsterColliderObj::~MonsterColliderObj()
	{
	}
	void MonsterColliderObj::Initialize()
	{
		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2::Zero);
		collider->SetSize(Vector2::Zero);

		GameObject::Initialize();
	}
	void MonsterColliderObj::Update()
	{
		GameObject::Update();
	}
	void MonsterColliderObj::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MonsterColliderObj::Release()
	{
		GameObject::Release();
	}
	void MonsterColliderObj::OnCollisionEnter(Collider* other)
	{
	}
	void MonsterColliderObj::OnCollisionStay(Collider* other)
	{
	}
	void MonsterColliderObj::OnCollisionExit(Collider* other)
	{
	}
}