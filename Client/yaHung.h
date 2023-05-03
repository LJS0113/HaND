#pragma once
#include "yaMonster.h"
#include "yaCollider.h"
namespace ya
{
	class Rigidbody;
	class Animator;
	class Player;
	class Hung : public Monster
	{
	public:
		enum class eHungState
		{
			Intro_Loop,
			Intro_Start,
			Move,
			Death,
			Death_Move,
			Idle,
			Attack,
			End,
		};
		Hung();
		~Hung();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void move();
		void death();
		void death_move();
		void idle();
		void attack();
		void intro_loop();
		void intro_start();
		void end();

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		eHungState GetHungState() { return mState; }

	private:
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		eHungState mState;
		Collider* collider;
		Collider* collider3;
		class MonsterColliderObj* colObj;
		UINT rand;
		float hpCount;
		float mTime;
		float mDeathTime;
		float atCount;
		bool mbLeft;
		bool mbRight;
	};
}