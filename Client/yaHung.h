#pragma once
#include "yaMonster.h"

namespace ya
{
	class Animator;
	class Hung : public GameObject
	{
	public:
		Hung();
		~Hung();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAnimator;
	};
}