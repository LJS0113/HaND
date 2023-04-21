#pragma once
#include "yaGameObject.h"


namespace ya
{
	class Animator;
	class HungAS : public GameObject
	{
	public:
		HungAS();
		~HungAS();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAnimator;
		class Collider* collider;
	};
}
