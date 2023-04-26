#pragma once
#include "yaMonster.h"

namespace ya
{
	class Animator;
	class BradV2 : public Monster
	{
	public:
		enum class eBradV2State
		{
			Intro,
			Move,
			Death,
			Idle,
			Attack,
		};
		BradV2();
		~BradV2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void intro();
		void death();
		void idle();
		void attack();
		void move();

	private:
		Animator* mAnimator;
		eBradV2State mState;
		class Collider* collider;
		class Collider* collider3;
		class ColliderObj* colObj;

		bool mbLeft;
		bool mbRight;
	};
}