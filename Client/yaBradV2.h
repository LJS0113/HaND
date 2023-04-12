#pragma once
#include "yaMonster.h"

namespace ya
{
	class Animator;
	class BradV2 : public Monster
	{
	public:
		BradV2();
		~BradV2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAnimator;
	};
}