#pragma once
#include "yaScene.h"

namespace ya
{
	class Image;
	class Animator;
	class LoadingScene : public Scene
	{
	public:
		LoadingScene();
		~LoadingScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual eSceneType GetSceneType() override { return mType; }

	private:
		Image* mImage;
		Animator* mAnimator;
		eSceneType mType;
		Loading* loading;
		class Sound* mainTheme;
	};
}