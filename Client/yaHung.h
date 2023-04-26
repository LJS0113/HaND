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
			Intro,
			Move,
			Death,
			Idle,
			Attack,
		};
		Hung();
		~Hung();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void move();
		void death();
		void idle();
		void attack();
		void intro();

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		eHungState mState;
		Collider* collider;
		Collider* collider3;
		class ColliderObj* colObj;
		UINT rand;
		float mTime;
		bool mbLeft;
		bool mbRight;
	};
}