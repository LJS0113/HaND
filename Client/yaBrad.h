#pragma once
#include "yaMonster.h"
#include "yaRigidbody.h"

namespace ya
{	
	class Animator;
	class Brad : public GameObject
	{
	public:
		enum class eBradState
		{
			Intro,
			Move,
			Death,
			Idle,
			Attack,
			Dive_Anticipation,
			Dive_Loop,
			Dive_End,
			Attack1,
			Fly,
			SpinAir,
			FlyToIdle,
		};

		Brad();
		~Brad();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void intro();
		void death();
		void idle();
		void attack();
		void move();
		void dive_anticipatiion();
		void dive_loop();
		void dive_end();
		void attack1();
		void fly();

		void spinAir();
		void flyToIdle();

	private:
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		eBradState mState;
		Collider* collider;
		Collider* collider3;
		class ColliderObj* colObj;

		UINT rand;
		float mTime;
		float mMovementTime;
		float mAttackDelay;
		float mflyTime;
		float mfallingTime;
		bool mbLeft;
		bool mbRight;

	};
}