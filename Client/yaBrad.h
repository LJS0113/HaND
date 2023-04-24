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

		void death();
		void idle();
		void attack();

	private:
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		eBradState mState;
		Collider* collider;

		UINT rand;
		float mTime;
		bool mbLeft;
		bool mbRight;
	};
}