#include "yaBGImageObject.h"
#include "yaResources.h"
#include "yaTransform.h"
#include "yaApplication.h"
#include "yaImage.h"

extern ya::Application application;

namespace ya
{
	BGImageObject::BGImageObject()
		: mImage(nullptr)
	{
	}

	BGImageObject::~BGImageObject()
	{
	}

	void BGImageObject::Initialize()
	{
		GameObject::Initialize();
	}

	void BGImageObject::Update()
	{
		GameObject::Update();
	}

	void BGImageObject::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 scale = tr->GetScale();
		Vector2 finalPos = pos;

		Vector2 rect;
		rect.x = application.GetWidth();
		rect.y = application.GetHeight();

		TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));
		GameObject::Render(hdc);
	}

	void BGImageObject::SetImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\HaND_Resource\\Map\\";
		path += fileName;

		mImage = Resources::Load<Image>(key, path);
	}

}

