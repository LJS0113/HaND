#pragma once
#include "yaComponent.h"


namespace ya
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetCenter(Vector2 center) { mCenter = center; };
		void SetSize(Vector2 size) { mSize = size; };
		Vector2 GetPos() { return mPos; }
		Vector2 GetSize() { return mSize; }
		UINT GetID() { return mID; }

	private:
		static UINT ColliderNumber;
		UINT mCollisionCount;
		UINT mID;
		Vector2 mCenter;
		Vector2 mSize;
		Vector2 mPos;
	};
}
