#pragma once
#include "yaGameObject.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaTransform.h"

namespace ya::object
{
	template <typename T>
	static inline T* Instantiate(eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObeject(gameObj, type);
		gameObj->Initialize();
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(Vector2 pos, eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObeject(gameObj, type);
		gameObj->GameObject::GetComponent<Transform>()->SetPos(pos);
		gameObj->Initialize();
		return gameObj;
	}


	static void Destory(GameObject* obj)
	{
		obj->SetState(GameObject::eState::Death);

	}
}