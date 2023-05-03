#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Collider;
	class Rigidbody;
	class Animator;
	class Player : public GameObject
	{
	public:
		enum class ePlayerState
		{
			ElevatorOut,
			Move,
			Dash,
			Jump,
			Death,
			Idle,
			Attack,
		};

		Player();
		~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetMonsterDead(bool isDead) { mbMonsterDead = isDead; }
		void SetHpCount(float hp) { hpCount = hp; }
		void SetPlayerState(ePlayerState state) { mState = state; }

		bool IsLeft() { return mbLeft; }

	private:
		void elevatorOut();
		void move();
		void death();
		void idle();
		void dash();
		void jump();
		void attack();

	private:
		ePlayerState mState;
		ePlayerState mPrevState;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Collider* collider;
		Collider* collider3;
		class ColliderObj* colObj;

		UINT attackCount;

		float mTime;
		float hpCount;
		float atCount;

		bool mbRight;
		bool mbLeft;
		bool mbMonsterDead;
	};

	extern Player* gPlayer;
}
