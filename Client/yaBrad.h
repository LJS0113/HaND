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
			Move,
			Death,
			Idle,
			Attack,
		};

		Brad();
		~Brad();

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
		eBradState mState;

		UINT rand;
		float mTime;
		bool mbLeft;
		bool mbRight;
	};
}