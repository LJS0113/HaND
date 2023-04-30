#pragma once
#include "yaMonster.h"

namespace ya
{
	class Animator;
	class BradV2 : public GameObject
	{
	public:
		enum class eBradV2State
		{
			Intro,
			Move,
			Death,
			Idle,
			Attack,
			Attack1,
			Attack2,
			Attack3_Slice,
			Attack3_Punch,
			Attack5_Ready,
			Attack5_Fire,
			Attack6_Ready,
			Attack6_Fire,
		};
		BradV2();
		~BradV2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void intro();
		void death();
		void idle();
		void attack();
		void move();

		void attack1();
		void attack2();
		void attack3_slice();
		void attack3_punch();
		void attack5_ready();
		void attack5_fire();
		void attack6_ready();
		void attack6_fire();

		eBradV2State GetBradV2State() { return mState; }

	private:
		Animator* mAnimator;
		eBradV2State mState;
		class Collider* collider;
		class Collider* collider3;
		class MonsterColliderObj* colObj;
		UINT rand;
		UINT hpCount;
		bool mbLeft;
		bool mbRight;
		float mTime;
		float mMovementTime;
		class Lazer* mLazer;
	};
}