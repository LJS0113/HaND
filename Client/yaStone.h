#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Collider;
	class Stone : public GameObject
	{
	public:
		Stone();
		~Stone();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		virtual eLayerType GetLayerType() override { return mLayerType; }

	private:
		Animator* mAnimator;
		Collider* collider;
		eLayerType mLayerType;
	};

}