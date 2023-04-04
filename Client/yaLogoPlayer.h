#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Image;
	class LogoPlayer : public GameObject
	{
	public:
		LogoPlayer();
		~LogoPlayer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;

		GameObject* mHead;
		GameObject* mBody;
		GameObject* mArm;
		GameObject* mWeapon;
		GameObject* mSmoke;
		
		Animator* mHeadAnimator;
		Animator* mBodyAnimator;
		Animator* mArmAnimator;
		Animator* mWeaponAnimator;
		Animator* mSmokeAnimator;
	};

}