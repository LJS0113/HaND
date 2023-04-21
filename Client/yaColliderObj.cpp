#include "yaColliderObj.h"
#include "yaCollider.h"

namespace ya
{
	ColliderObj::ColliderObj()
	{
	}
	ColliderObj::~ColliderObj()
	{
	}
	void ColliderObj::Initialize()
	{
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(0.0f, 0.0f));
		collider->SetSize(Vector2(200.0f, 200.0f));

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
	}
	void ColliderObj::OnCollisionStay(Collider* other)
	{
	}
	void ColliderObj::OnCollisionExit(Collider* other)
	{
	}
}