#pragma once
#include "yaMonster.h"


namespace ya
{	
	class Animator;
	class Brad : public GameObject
	{
	public:
		Brad();
		~Brad();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAnimator;
	};
}