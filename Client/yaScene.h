#pragma once
#include "yaEntity.h"
#include "yaLayer.h"

namespace ya
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();
		
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Destroy();
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObeject(GameObject* obj, eLayerType layer);
		std::vector<GameObject*>& GetGameObjects(eLayerType layer);

		virtual eSceneType GetSceneType() { return mType; }

	private:
		std::vector<Layer> mLayers;
		eSceneType mType;
	};
}
