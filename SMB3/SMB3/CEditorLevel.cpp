#include "pch.h"
#include "CEditorLevel.h"

#include "CLevelMgr.h"

#include "CKeyMgr.h"

#include "CEngine.h"
#include "CCamera.h"
#include "resource.h"

#include "CTile.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "resource.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CImageUI.h"
#include "CLayer.h"

void TestFunc();
INT_PTR CALLBACK CreateTileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


void CEditorLevel::init()
{

}

void CEditorLevel::enter()
{
	// 메뉴바 생성
	// 리소스 아이디로 메뉴를 골라서 생성
	//HMENU hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));
	//HMENU hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_EDITOR_MENU));

	// 메인 윈도우에 생성시킨 메뉴를 붙이기
	//SetMenu(CEngine::GetInst()->GetMainWind(), hMenu);

	// 메뉴가 추가되었기 때문에 윈도우 크기를 재조정
	//POINT ptResSol = CEngine::GetInst()->GetResolution();
	//CEngine::GetInst()->ChangeWindowSize(ptResSol, true);

	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);

	// UI 생성
	CPanelUI* pPanelUI = new CPanelUI;
	pPanelUI->SetScale(Vec2(350.f, 500.f));
	pPanelUI->SetPos(Vec2(1200.f, 10.f));

	// 불러오기 버튼
	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetScale(Vec2(80.f, 40.f));
	pBtnUI->SetPos(Vec2(10.f, 10.f));
	//pBtnUI->SetCallBack(TestFunc);
	pBtnUI->SetDeletage(this, (DelegateFunc)&CEditorLevel::LoadTile);
	pPanelUI->AddChildUI(pBtnUI);

	// 저장 버튼
	pBtnUI = new CBtnUI;
	pBtnUI->SetScale(Vec2(80.f, 40.f));
	pBtnUI->SetPos(Vec2(110.f, 10.f));
	//pBtnUI->SetCallBack(TestFunc);
	pBtnUI->SetDeletage(this, (DelegateFunc)&CEditorLevel::SaveTile);
	pPanelUI->AddChildUI(pBtnUI);

	// 초기화 버튼
	pBtnUI = new CBtnUI;
	pBtnUI->SetScale(Vec2(80.f, 40.f));
	pBtnUI->SetPos(Vec2(220.f, 10.f));
	//pBtnUI->SetCallBack(TestFunc);
	pBtnUI->SetDeletage(this, (DelegateFunc)&CEditorLevel::initSelected);
	pPanelUI->AddChildUI(pBtnUI);

	
	// atlus 카테고리화를 위해
	// 여러개의 판넬을 같은위치에 위치시킨 후
	// 버튼을 누르면 해당 UI가 제일 위로 올라오도록
	// 카테고리
	// 1. 몬스터
	// 2. 맵 타일
	// 3. 플레이어
	// 
	// 순서
	// 1. 판넬, atlus imageUI화 진행
	// 2. 버튼 UI 생성
	// 3. 해당 버튼 누르면 변경하는 함수 넣기

	// 이에 따른 수정해야 할 것
	// save / load 시 카테고리 분류가 필요
	// 몬스터의 경우 16*16이 아닌 16*32짜리도 좀 있는데 어칼까?
	

	// ex) 몬스터
	CPanelUI* mPanelUI = new CPanelUI;
	mPanelUI->SetScale(Vec2(321.f, 440.f));
	mPanelUI->SetPos(Vec2(0.f, 60.f));

	for (int i = 0; i < 25; ++i) {// 갯수 수정 필요
		CImageUI* imageUI = new CImageUI;
		imageUI->SetScale(Vec2(64.f, 64.f));
		imageUI->SetPos(Vec2(0.f + 64 * (i % 5), 0.f + 64 * (i / 5)));
		imageUI->GetTile()->SetImgIdx(i);
		mPanelUI->AddChildUI(imageUI);
	}
	pPanelUI->AddChildUI(mPanelUI);

	// 오른쪽에 카테고리 버튼
	pBtnUI = new CBtnUI;
	pBtnUI->SetScale(Vec2(28.f, 30.f));
	pBtnUI->SetPos(Vec2(322.f, 60.f));
	//pBtnUI->SetCallBack(TestFunc);
	pBtnUI->SetDeletage(this, (DelegateFunc)&CEditorLevel::SaveTile);
	pPanelUI->AddChildUI(pBtnUI);



	AddObject(LAYER::UI, pPanelUI);

	
	/*pPanelUI = pPanelUI->Clone();
	pPanelUI->SetPos(Vec2(500.f, 200.f));
	AddObject(LAYER::UI, pPanelUI);*/
}

void CEditorLevel::exit()
{
	DeleteAllObjects();

	// 메뉴바 제거
	// 현재 윈도우에 붙어있는 메뉴의 핸들(아이디) 를 알아낸다.
	HMENU hMenu = GetMenu(CEngine::GetInst()->GetMainWind());

	// 메인 윈도우에 부착되어있는 메뉴를 떼어낸다.
	SetMenu(CEngine::GetInst()->GetMainWind(), nullptr);

	// 메뉴를 메모리 해제시킨다.
	DestroyMenu(hMenu);

	// 메뉴가 윈도우에서 떨어졌으니, 윈도우 크기를 다시 설정해준다.
	POINT ptResSol = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResSol, false);
}

void CEditorLevel::tick()
{
	CLevel::tick();
	setSelected(CLevelMgr::GetInst()->GetTile());
	// Enter 키가 눌리면 StartLevel 로 변환
	//if (KEY_TAP(KEY::ENTER))
	//{
	//	ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
	//}

	// 오브젝트 놓기
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
		vMousePos = { (int)vMousePos.x / 64, (int)vMousePos.y / 64 };
		vMousePos *= 64;
		bool uiMouseOn = false;
		const vector<CObj*>& vecUi = GetObjects(LAYER::UI);
		for (int i = 0; i < vecUi.size(); ++i) {
			CUI* uiNow = dynamic_cast<CUI*>(vecUi[i]);
			if (nullptr == uiNow)
				continue;
			if (uiNow->getMouseOn()) {
				uiMouseOn = true;
				break;
			}
		}
		if (!uiMouseOn && selected != nullptr) {
			CTile* pTile = selected->GetTile()->Clone();
			pTile->SetPos(vMousePos);
			AddObject(LAYER::TILE, pTile);
		}

		
	}

	// 해당 위치의 오브젝트 삭제
	if (KEY_TAP(KEY::RBTN))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
		const vector<CObj*>& vecTile = GetObjects(LAYER::TILE);
		for (int i = 0; i < vecTile.size(); ++i) {
			if (vecTile[i]->GetRenderPos().x <= vMousePos.x && vecTile[i]->GetRenderPos().x + vecTile[i]->GetScale().x >= vMousePos.x
				&& vecTile[i]->GetRenderPos().y <= vMousePos.y && vecTile[i]->GetRenderPos().y + vecTile[i]->GetScale().y >= vMousePos.y) {
				vecTile[i]->Destroy();
				break;
			}
		}
	}
	
	if (KEY_TAP(KEY::_8))
	{
		SaveTile();
	}
}

void CEditorLevel::OpenTileCreateWindow()
{
	DialogBox(nullptr, MAKEINTRESOURCE(IDD_CREATE_TILE), CEngine::GetInst()->GetMainWind(), CreateTileProc);
}

void CEditorLevel::SaveTile()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetContentPath();
	strTileFolderPath += L"tile\\";


	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");

	const vector<CObj*>& vecTile = GetObjects(LAYER::TILE);
	UINT iTileCount = vecTile.size();

	fwrite(&iTileCount, sizeof(UINT), 1, pFile);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CEditorLevel::initSelected()
{
	CLevelMgr::GetInst()->GetTile()->SetSelected();
	CLevelMgr::GetInst()->SetTile(nullptr);
}


CEditorLevel::CEditorLevel()
	:selected(nullptr)
{
}


void CEditorLevel::LoadTile()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetContentPath();
	strTileFolderPath += L"tile\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	DeleteObjectsByLayer(LAYER::TILE);

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");

	UINT iTileCount = 0;

	fread(&iTileCount, sizeof(UINT), 1, pFile);

	CLayer* curLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(LAYER::TILE);
	
	for (size_t i = 0; i < iTileCount; ++i)
	{
		CTile* lFile = new CTile;
		lFile->Load(pFile);
		curLayer->AddObject(lFile);
	}

	fclose(pFile);
}




// ==============================
// CreateTile Dialog 프로시저 함수
// ==============================
INT_PTR CALLBACK CreateTileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// IDC_COL, IDC_ROW 에디트 컨트롤에 입력한 숫자를 알아내서
			// EditorLevel 의 타일을 해당 수치에 맞게 생성시킨다.
			int Col = GetDlgItemInt(hDlg, IDC_COL, nullptr, true);
			int Row = GetDlgItemInt(hDlg, IDC_ROW, nullptr, true);

			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(pCurLevel);

			if (nullptr != pEditorLevel)
			{
				pEditorLevel->CreateTile(Row, Col);
			}

			// 다이얼로그 윈도우 종료
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			// 다이얼로그 윈도우 종료
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}


void TestFunc()
{
	DialogBox(nullptr, MAKEINTRESOURCE(IDD_CREATE_TILE), CEngine::GetInst()->GetMainWind(), CreateTileProc);
}