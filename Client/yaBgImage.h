#pragma once
#include "yaGameObject.h"

namespace ya 
{
	class Image;
	class BgImage : public GameObject
	{
	public :
		BgImage();
		~BgImage();
		
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Image* mImage;
	};
}