#pragma once
#include "yaScene.h"
#include "yaImage.h"

namespace ya
{
	class Player;
	class Monster;
	class HungScene : public Scene
	{
	public:
		HungScene();
		~HungScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual eSceneType GetSceneType() override { return mType; }

		void eleIn();
		void eleOut();
		void eleDisappear();

	private:
		class Hung* hung;
		eSceneType mType;
		float mTime;
		class Elevator* elevator;
		eElevatorState mEleState;
		class Sound* mainTheme;
	};
}