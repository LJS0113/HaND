#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Image;
	class Elevator : public GameObject
	{
	public:
		Elevator();
		~Elevator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAnimator;
	};
}
