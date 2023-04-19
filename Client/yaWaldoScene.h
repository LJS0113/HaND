#pragma once
#include "yaScene.h"
#include "yaImage.h"

namespace ya
{
	class Player;
	class Monster;
	class WaldoScene : public Scene
	{
	public:
		WaldoScene();
		~WaldoScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		Image* mBgImage;
	};
}