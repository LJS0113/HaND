#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class BGImageObject : public GameObject
	{
	public:
		BGImageObject();
		~BGImageObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key, const std::wstring& fileName);
		Image* GetImage() { return mImage; }
		void SetScale(Vector2 scale) { mScale = scale; }

	private:
		Image* mImage;
		Image* mPixelImage;
		Vector2 mScale;
	};
}