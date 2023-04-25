#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Collider;
	class ColliderObj : public GameObject
	{
	public:
		ColliderObj();
		~ColliderObj();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		Collider* collider;
		float mTime;
	};
}
