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
	pPanelUI->SetScale(Vec2(350.f, 550.f));
	pPanelUI->SetPos(Vec2(1200.f, 10.f));

	// 불러오기 버튼
	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetScale(Vec2(64.f, 64.f));
	pBtnUI->SetPos(Vec2(39.5f, 10.f));
	CTexture* pTexture = CAssetMgr::GetInst()->LoadTexture(L"load", L"texture\\load.png");
	pBtnUI->SetNormalImg(pTexture);
	pBtnUI->SetDeletage(this, (DelegateFunc)&CEditorLevel::LoadTile);
	pPanelUI->AddChildUI(pBtnUI);

	// 저장 버튼
	pBtnUI = new CBtnUI;
	pBtnUI->SetScale(Vec2(64.f, 64.f));
	pBtnUI->SetPos(Vec2(143.f, 10.f));
	pTexture = CAssetMgr::GetInst()->LoadTexture(L"save", L"texture\\save.png");
	pBtnUI->SetNormalImg(pTexture);
	pBtnUI->SetDeletage(this, (DelegateFunc)&CEditorLevel::SaveTile);
	pPanelUI->AddChildUI(pBtnUI);

	// 초기화 버튼
	pBtnUI = new CBtnUI;
	pBtnUI->SetScale(Vec2(64.f, 64.f));
	pBtnUI->SetPos(Vec2(246.5f, 10.f));
	pTexture = CAssetMgr::GetInst()->LoadTexture(L"reset", L"texture\\reset.png");
	pBtnUI->SetNormalImg(pTexture);
	pBtnUI->SetDeletage(this, (DelegateFunc)&CEditorLevel::initSelected);
	pPanelUI->AddChildUI(pBtnUI);


	// 게임 시작 버튼
	pBtnUI = new CBtnUI;
	pBtnUI->SetScale(Vec2(150.f, 50.f));
	pBtnUI->SetPos(Vec2(100.f, 84.f));
	pTexture = CAssetMgr::GetInst()->LoadTexture(L"start", L"texture\\start.png");
	pBtnUI->SetNormalImg(pTexture);
	//pBtnUI->SetDeletage(this, (DelegateFunc)&CEditorLevel::initSelected);
	pPanelUI->AddChildUI(pBtnUI);
	

	CPanelUI* mPanelUI = new CPanelUI;
	mPanelUI->SetScale(Vec2(321.f, 380.f));
	mPanelUI->SetPos(Vec2(10.f, 144.f));

	for (int i = 0; i < 30; ++i) {
		CImageUI* imageUI = new CImageUI;
		imageUI->SetScale(Vec2(64.f, 64.f));
		imageUI->SetPos(Vec2(0.f + 64 * (i % 5), 0.f + 64 * (i / 5)));
		imageUI->GetTile()->SetImgIdx(i);
		mPanelUI->AddChildUI(imageUI);
	}
	pPanelUI->AddChildUI(mPanelUI);

	AddObject(LAYER::UI, pPanelUI);

	
	/*pPanelUI = pPanelUI->Clone();
	pPanelUI->SetPos(Vec2(500.f, 200.f));
	AddObject(LAYER::UI, pPanelUI);*/
}

void CEditorLevel::exit()
{
	const vector<CObj*>& vecTile = GetObjects(LAYER::TILE);
	CLevelMgr::GetInst()->SetMapData(vecTile, mLeft, mRightBottom);
	DeleteAllObjects();
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
			if (selected->GetTile()->GetImgIdx() == Tile_Type::MARIO && isMarioSetted) {
				
			}
			else if (selected->GetTile()->GetImgIdx() == Tile_Type::GAME_END && isEndSetted) {

			}
			else {
				if (selected->GetTile()->GetImgIdx() == Tile_Type::MARIO)
					isMarioSetted = true;
				else if (selected->GetTile()->GetImgIdx() == Tile_Type::GAME_END)
					isEndSetted = true;
				CTile* pTile = selected->GetTile()->Clone();
				pTile->SetPos(vMousePos);
				if (pTile->GetPos().x < mLeft.x)
					mLeft.x = pTile->GetPos().x;
				if (pTile->GetPos().x > mRightBottom.x)
					mRightBottom.x = pTile->GetPos().x;
				if (pTile->GetPos().y > mRightBottom.y)
					mRightBottom.y = pTile->GetPos().y;
				AddObject(LAYER::TILE, pTile);
			}
		}

		
	}

	// 해당 위치의 오브젝트 삭제
	if (KEY_TAP(KEY::RBTN))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		const vector<CObj*>& vecTile = GetObjects(LAYER::TILE);
		for (int i = 0; i < vecTile.size(); ++i) {
			if (vecTile[i]->GetRenderPos().x <= vMousePos.x && vecTile[i]->GetRenderPos().x + vecTile[i]->GetScale().x >= vMousePos.x
				&& vecTile[i]->GetRenderPos().y <= vMousePos.y && vecTile[i]->GetRenderPos().y + vecTile[i]->GetScale().y >= vMousePos.y) {
				vecTile[i]->Destroy();
				break;
			}
		}
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

	// mapsize 저장
	// mLeft
	// mRightBottom
	// mariosetted
	// endsetted
	fwrite(&mLeft, sizeof(Vec2), 1, pFile); 
	fwrite(&mRightBottom, sizeof(Vec2), 1, pFile);
	fwrite(&isMarioSetted, sizeof(bool), 1, pFile);
	fwrite(&isEndSetted, sizeof(bool), 1, pFile);
	
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
	if (nullptr != CLevelMgr::GetInst()->GetTile()) {
		CLevelMgr::GetInst()->GetTile()->SetSelected();
		CLevelMgr::GetInst()->SetTile(nullptr);
	}
}

void CEditorLevel::LoadGame()
{
	// endtile, mario가 설정되어 있으면 changeLevel 가능
	if (isMarioSetted && isEndSetted)
		ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
}


CEditorLevel::CEditorLevel()
	: selected(nullptr)
	, mLeft(0, 0)
	, mRightBottom(0, 0)
	, isMarioSetted(false)
	, isEndSetted(false)
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

	// mapsize 불러오기
	// mLeft
	// mRightBottom
	// mariosetted
	// endsetted
	fread(&mLeft, sizeof(Vec2), 1, pFile);
	fread(&mRightBottom, sizeof(Vec2), 1, pFile);
	fread(&isMarioSetted, sizeof(bool), 1, pFile);
	fread(&isEndSetted, sizeof(bool), 1, pFile);

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