#pragma once
#include "yaScene.h"

namespace ya
{
	class Player;
	class Monster;
	class BradV2Scene : public Scene
	{
	public:
		BradV2Scene();
		~BradV2Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual eSceneType GetSceneType() override { return mType; }

	private:
		eSceneType mType;
		class Sound* mainTheme;
	};
}
