#pragma once
#include "yaComponent.h"

namespace ya
{
	class Collider2 : public Component
	{
	public:
		Collider2();
		~Collider2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(Collider2* other);
		virtual void OnCollisionStay(Collider2* other);
		virtual void OnCollisionExit(Collider2* other);

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

		bool mbDisplay;
	};
}
