#include "yaElevator.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaTransform.h"
#include "yaCollider.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaPlayer.h"

extern ya::Player* gPlayer;

namespace ya
{
	Elevator::Elevator()
	{
	}

	Elevator::~Elevator()
	{
	}

	void Elevator::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Map\\Elevator\\In", Vector2(0.0f, 0.0f), 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\HaND_Resource\\Map\\Elevator\\Out", Vector2(0.0f, 0.0f), 0.05f);
		
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-25.0f, -250.0f));
		collider->SetSize(Vector2(80.0f, 200.0f));

		mAnimator->Play(L"MapElevatorIn", false);

		GameObject::Initialize();
	}

	void Elevator::Update()
	{
		GameObject::Update();
	}

	void Elevator::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Elevator::Release()
	{
		GameObject::Release();
	}

	void Elevator::OnCollisionEnter(Collider* other)
	{
	}

	void Elevator::OnCollisionStay(Collider* other)
	{
		if (Input::GetKeyDown(eKeyCode::F))
		{
 			gPlayer->GetComponent<Animator>()->Play(L"PlayerElevatorIn", false);
		}
		if (gPlayer->GetComponent<Animator>()->IsComplete())
		{
			SceneManager::LoadScene(eSceneType::Hung);
			gPlayer->GetComponent<Animator>()->Play(L"PlayerIdleRight", true);
		}
	}

	void Elevator::OnCollisionExit(Collider* other)
	{
	}

}