#include "yaColliderObj.h"
#include "yaCollider.h"
#include "yaTime.h"

namespace ya
{
	ColliderObj::ColliderObj()
		: mTime(0.0f)
	{
	}
	ColliderObj::~ColliderObj()
	{
	}
	void ColliderObj::Initialize()
	{
		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2::Zero);
		collider->SetSize(Vector2::Zero);

		GameObject::Initialize();
	}
	void ColliderObj::Update()
	{
		GameObject::Update();
	}
	void ColliderObj::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ColliderObj::Release()
	{
		GameObject::Release();
	}
	void ColliderObj::OnCollisionEnter(Collider* other)
	{ 
		int a = 0;
	}
	void ColliderObj::OnCollisionStay(Collider* other)
	{
	}
	void ColliderObj::OnCollisionExit(Collider* other)
	{
	}
}