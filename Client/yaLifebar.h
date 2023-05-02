#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Lifebar : public GameObject
	{
	public:
		Lifebar();
		~Lifebar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetImage(const std::wstring& key, const std::wstring& fileName);

		float GetPlayerAttackCount() { return playerAttackCount; }
		float GetBossAttackCount() { return bossAttackCount; }

		void SetPlayerAttackCount(float count) { playerAttackCount = count; }
		void SetBossAttackCount(float count) { bossAttackCount = count; }

		void SetBossLifebar(bool bossOn) { mbBoss = bossOn; }
		void SetPlayerIconImage(const std::wstring& key, const std::wstring& fileName);
		void SetBossIconImage(const std::wstring& key, const std::wstring& fileName);

	private:
		//Image* mPlayerLifebarBase;
		//Image* mPlayerLifebar;
		Image* mLifebarBase;
		Image* mLifebar;
		Image* mPlayerIcon;
		Image* mBossIcon;

		float playerAttackCount;
		float bossAttackCount;

		bool mbPlayer;
		bool mbBoss;
	};
	extern Lifebar* gLifebar;
}
