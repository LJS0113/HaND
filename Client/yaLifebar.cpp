#include "yaLifebar.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaApplication.h"
#include "yaTransform.h"

extern ya::Application application;

namespace ya
{
	Lifebar* gLifebar = nullptr;
	Lifebar::Lifebar()
		: mbPlayer(true)
		, mbBoss(false)
		, playerAttackCount(0.0f)
		, bossAttackCount(0.0f)
	{
	}
	Lifebar::~Lifebar()
	{
	}
	void Lifebar::Initialize()
	{
		mLifebarBase = Resources::Load<Image>(L"BossLifebarBase", L"..\\Resources\\HaND_Resource\\UI\\Lifebar\\BossLifebarBase.bmp");
		mLifebar = Resources::Load<Image>(L"BossLifebar", L"..\\Resources\\HaND_Resource\\UI\\Lifebar\\BossLifebar.bmp");

		GameObject::Initialize();
	}
	void Lifebar::Update()
	{
		GameObject::Update();
	}
	void Lifebar::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 finalPos = pos;

		if (mbPlayer)
		{
			if (playerAttackCount == 0.0f)
			{
				TransparentBlt(hdc, 60.0f, 25.0f, mPlayerIcon->GetWidth()/2 , mPlayerIcon->GetHeight()
					, mPlayerIcon->GetHdc(), 0, 0, mPlayerIcon->GetWidth(), mPlayerIcon->GetHeight()
					, RGB(255, 0, 255));
				TransparentBlt(hdc, 50.0f, 10.0f, mLifebarBase->GetWidth()/2, mLifebarBase->GetHeight()
					, mLifebarBase->GetHdc(), 0, 0, mLifebarBase->GetWidth(), mLifebarBase->GetHeight()
					, RGB(255, 0, 255));

				TransparentBlt(hdc, 128.0f, 105.0f, mLifebar->GetWidth()/2, mLifebar->GetHeight()
					, mLifebar->GetHdc(), 0, 0, mLifebar->GetWidth(), mLifebar->GetHeight()
					, RGB(255, 0, 255));
			}
			else
			{
				TransparentBlt(hdc, 60.0f, 25.0f, mPlayerIcon->GetWidth()/2 , mPlayerIcon->GetHeight()
					, mPlayerIcon->GetHdc(), 0, 0, mPlayerIcon->GetWidth(), mPlayerIcon->GetHeight()
					, RGB(255, 0, 255));
				TransparentBlt(hdc, 50.0f, 10.0f, mLifebarBase->GetWidth()/2, mLifebarBase->GetHeight()
					, mLifebarBase->GetHdc(), 0, 0, mLifebarBase->GetWidth(), mLifebarBase->GetHeight()
					, RGB(255, 0, 255));

				TransparentBlt(hdc, 128.0f, 105.0f, (mLifebar->GetWidth()/2) * ((10.0f-playerAttackCount) / 10.0f), mLifebar->GetHeight()
					, mLifebar->GetHdc(), 0, 0, mLifebar->GetWidth(), mLifebar->GetHeight()
					, RGB(255, 0, 255));
			}
		}

		if (mbBoss)
		{
			if (bossAttackCount == 0.0f)
			{
				TransparentBlt(hdc, 855.0f, 50.0f, mBossIcon->GetWidth()/2, mBossIcon->GetHeight()/2
					, mBossIcon->GetHdc(), 0, 0, mBossIcon->GetWidth(), mBossIcon->GetHeight()
					, RGB(255, 0, 255));

				TransparentBlt(hdc, 845.0f, 5.0f, mLifebarBase->GetWidth()/2, mLifebarBase->GetHeight()
					, mLifebarBase->GetHdc(), 0, 0, mLifebarBase->GetWidth(), mLifebarBase->GetHeight()
					, RGB(255, 0, 255));

				TransparentBlt(hdc, 922.0f, 105.0f, mLifebar->GetWidth()/2, mLifebar->GetHeight()
					, mLifebar->GetHdc(), 0, 0, mLifebar->GetWidth(), mLifebar->GetHeight()
					, RGB(255, 0, 255));
			}
			else
			{
				TransparentBlt(hdc, 855.0f, 50.0f, mBossIcon->GetWidth() / 2, mBossIcon->GetHeight() / 2
					, mBossIcon->GetHdc(), 0, 0, mBossIcon->GetWidth(), mBossIcon->GetHeight()
					, RGB(255, 0, 255));
				TransparentBlt(hdc, 845.0f, 5.0f, mLifebarBase->GetWidth()/2, mLifebarBase->GetHeight()
					, mLifebarBase->GetHdc(), 0, 0, mLifebarBase->GetWidth(), mLifebarBase->GetHeight()
					, RGB(255, 0, 255));

				TransparentBlt(hdc, 922.0f, 105.0f, (mLifebar->GetWidth()/2) * ((20.0f - bossAttackCount) / 20.0f), mLifebar->GetHeight()
					, mLifebar->GetHdc(), 0, 0, mLifebar->GetWidth(), mLifebar->GetHeight()
					, RGB(255, 0, 255));
			}
		}
		GameObject::Render(hdc);
	}
	void Lifebar::Release()
	{
		GameObject::Release();
	}

	void Lifebar::SetPlayerIconImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\HaND_Resource\\UI\\Icon\\";
		path += fileName;

		mPlayerIcon = Resources::Load<Image>(key, path);
	}

	void Lifebar::SetBossIconImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\HaND_Resource\\UI\\Icon\\";
		path += fileName;

		mBossIcon = Resources::Load<Image>(key, path);
	}
}