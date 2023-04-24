#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Ground : public GameObject
	{
	public:
		Ground();
		virtual ~Ground();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetPlayer(class Player* player) { mPlayer = player; }
		void SetImage(const std::wstring& key, const std::wstring& fileName);
		void SetSize(Vector2 size);

	private:
		class Collider* mCollider;
		class Image* mImage;
		class Player* mPlayer;
		class Monster* mMonster;
	};
}
