#pragma once
#include "yaGameObject.h"
#include "yaCollider2.h"

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

	private:
		void move();
		void death();
		void idle();
		void dash();
		void jump();
		void attack();
		void idleCompleteEvent();

	private:
		ePlayerState mState;
		ePlayerState mPrevState;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Collider* collider;
		Collider* collider3;
		Collider2* collider2;

		UINT attackCount;
		float mTime;
		bool mbRight;
		bool mbLeft;
	};

	extern Player* gPlayer;
}
