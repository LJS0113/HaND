#pragma once
#include "yaMonster.h"

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

	private:
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		eHungState mState;
		Player* mPlayer;

		UINT rand;
		float mTime;
		bool mbLeft;
		bool mbRight;
	};
}