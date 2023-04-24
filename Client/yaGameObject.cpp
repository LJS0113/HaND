#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaCollider.h"
#include "yaCollider2.h"

namespace ya
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		mComponents.resize((UINT)eComponentType::End);
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render(hdc);
		}
	}

	void GameObject::Release()
	{

	}
	void GameObject::OnCollisionEnter(Collider* other)
	{
	}
	void GameObject::OnCollisionStay(Collider* other)
	{
	}
	void GameObject::OnCollisionExit(Collider* other)
	{
	}
	void GameObject::OnCollisionEnter2(Collider2* other)
	{
		OnCollisionEnter(dynamic_cast<Collider*>(other));
	}
	void GameObject::OnCollisionStay2(Collider2* other)
	{
		OnCollisionStay(dynamic_cast<Collider*>(other));
	}
	void GameObject::OnCollisionExit2(Collider2* other)
	{
		OnCollisionExit(dynamic_cast<Collider*>(other));
	}
}
