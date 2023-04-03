#include "yaToolScene.h"
#include "yaApplication.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaTile.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaTilePalatte.h"
#include "yaCamera.h"

extern ya::Application application;

namespace ya
{

	ToolScene::ToolScene()
	{
	}

	ToolScene::~ToolScene()
	{
	}

	void ToolScene::Initialize()
	{
		Scene::Initialize();
		TilePalatte::Initiailize();
	}

	void ToolScene::Update()
	{
		Scene::Update();
		Vector2  temp = Input::GetMousePos();
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			Vector2 pos = Input::GetMousePos();
			pos -= Camera::CaluatePos(Vector2::Zero);

			pos = TilePalatte::GetTilePos(pos);

			UINT tileIndxe = TilePalatte::GetIndex();
			TilePalatte::CreateTile(tileIndxe, pos);
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			TilePalatte::Save();
		}
		if (Input::GetKeyDown(eKeyCode::L))
		{
			TilePalatte::Load();
		}
	}

	void ToolScene::Render(HDC hdc)
	{
		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

		
		Vector2 startPos(0, 0);
		startPos = Camera::CaluatePos(startPos);

		int maxRow = application.GetHeight() / TILE_SIZE_Y + 1;
		for (size_t y = 0; y < maxRow * 3; y++)
		{
			MoveToEx(hdc, startPos.x, TILE_SIZE_Y * y + startPos.y, NULL);
			LineTo(hdc, application.GetWidth(), TILE_SIZE_Y * y + startPos.y);
		}
		int maxColumn = application.GetWidth() / TILE_SIZE_X + 1;
		
		for (size_t x = 0; x < maxColumn * 3; x++)
		{
			MoveToEx(hdc, TILE_SIZE_X * x + startPos.x, startPos.y, NULL);
			LineTo(hdc, TILE_SIZE_X * x + startPos.x, application.GetHeight());
		}
		(HPEN)SelectObject(hdc, oldPen);
		DeleteObject(redPen);

		Scene::Render(hdc);
	}

	void ToolScene::Release()
	{
		Scene::Release();
	}

	void ToolScene::OnEnter()
	{
	}

	void ToolScene::OnExit()
	{
	}
}


#include "Resource.h"
LRESULT CALLBACK AtlasWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		//512 384
		//HMENU mMenubar = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));
		//SetMenu(hWnd, mMenubar);
		ya::Image* tile = ya::Resources::Load<ya::Image>(L"TileAtlas", L"..\\Resources\\Tile.bmp");
		RECT rect = { 0, 0, tile->GetWidth(), tile->GetHeight() };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// 윈도우 크기 변경및 출력 설정
		SetWindowPos(hWnd
			, nullptr, 1600, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(hWnd, true);
	}

	case WM_LBUTTONDOWN:
	{

		if (GetFocus())
		{
			::POINT mousePos = {};
			::GetCursorPos(&mousePos);
			::ScreenToClient(application.GetToolHwnd(), &mousePos);
			
			int x = mousePos.x / TILE_SIZE_X;
			int y = mousePos.y / TILE_SIZE_Y;

			int index = (y * 8) + (x % 8);

			ya::TilePalatte::SetIndex(index);
		}
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
			//case IDM_ABOUT:
			//    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			//    break;
			//case IDM_EXIT:
			//    DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		ya::Image* tile = ya::Resources::Find<ya::Image>(L"TileAtlas");
		BitBlt(hdc, 0, 0, tile->GetWidth(), tile->GetHeight(), tile->GetHdc(), 0, 0, SRCCOPY);

		//HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		//HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

		//Ellipse(hdc, 0, 0, 100, 100);
		////RoundRect(hdc, 200, 200, 300, 300, 500, 500);
		//(HPEN)SelectObject(hdc, oldPen);
		//DeleteObject(redPen);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}