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
		
		void SetPath(const std::wstring& path);

	private:
		Image* mImage;
		Animator* mAnimator;
	};

}