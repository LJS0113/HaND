#pragma once
#include "yaScene.h"

namespace ya
{
	class Image;
	class Animator;
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual eSceneType GetSceneType() override { return mType; };

	private:
		Image* mBgLogoImage;
		Animator* mAnimator;
		eSceneType mType;
		class Sound* mainTheme;
	};
}