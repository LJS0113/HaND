#include "yaCollider2.h"
#include "yaCollider.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaCamera.h"


namespace ya
{
	UINT Collider2::ColliderNumber = 0;
	Collider2::Collider2()
		: Component(eComponentType::Collider2)
		, mCenter(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mSize(Vector2::Zero)
		, mID(ColliderNumber++)
		, mCollisionCount(0)
		, mbDisplay(false)
	{
	}
	Collider2::~Collider2()
	{
	}
	void Collider2::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mPos = tr->GetPos() + mCenter;

		int a = 0;
	}
	void Collider2::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mPos = tr->GetPos() + mCenter;
	}
	void Collider2::Render(HDC hdc)
	{
		HPEN pen = NULL;
		if (mCollisionCount <= 0)
			pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
		else
			pen = CreatePen(BS_SOLID, 2, RGB(255, 0, 0));

		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		Vector2 pos = Camera::CaluatePos(mPos);
		Rectangle(hdc, pos.x, pos.y, pos.x + mSize.x, pos.y + mSize.y);

		(HPEN)SelectObject(hdc, oldPen);
		(HBRUSH)SelectObject(hdc, oldBrush);
		DeleteObject(pen);

		mCollisionCount = 0;
	}
	void Collider2::Release()
	{
	}
	void Collider2::OnCollisionEnter(Collider2* other)
	{
		GetOwner()->OnCollisionEnter(dynamic_cast<Collider*>(other));
	}
	void Collider2::OnCollisionStay(Collider2* other)
	{
		mCollisionCount = 1;
		GetOwner()->OnCollisionStay(dynamic_cast<Collider*>(other));
	}
	void Collider2::OnCollisionExit(Collider2* other)
	{
		GetOwner()->OnCollisionExit(dynamic_cast<Collider*>(other));
	}
}