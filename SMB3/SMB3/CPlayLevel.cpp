#include "pch.h"
#include "CPlayLevel.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CPlatform.h"

#include "CEngine.h"
#include "CCamera.h"
#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"

#include "CAssetMgr.h"
#include "CSound.h"
#include "CPathMgr.h"

void CPlayLevel::init()
{
}

void CPlayLevel::enter()
{	
	CCamera::GetInst()->FadeOut(0.3f);
	if (CLevelMgr::GetInst()->getMapData() == nullptr) {
		// 미리 저장해놓은 맵 로딩
		loadMap();
	}
	else {
		vector<CObj*> curMapTiles = CLevelMgr::GetInst()->getMapData()->tileData;
		CLayer* curLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(LAYER::TILE);
		for (int i = 0; i < curMapTiles.size(); ++i) {
			AddObject(TILE, curMapTiles[i]);
		}
	}
	// map > obj 화 필요
	CCamera::GetInst()->FadeIn(0.3f);

	
}

void CPlayLevel::exit()
{
	DeleteAllObjects();
}

void CPlayLevel::tick()
{
	CLevel::tick();

	// Enter 키가 눌리면 StartLevel 로 변환
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR_LEVEL);
	}

	if (KEY_TAP(KEY::M))
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_02", L"sound\\BGM_Stage1.wav");
		pSound->SetVolume(100);
		pSound->SetPosition(45.f);
		pSound->Play(true);
	}	
}

void CPlayLevel::loadMap()
{
	wstring strTileFilePath = CPathMgr::GetContentPath();
	strTileFilePath += L"tile\\stage1";
	wchar_t szExt[256] = {};
	_wsplitpath_s(strTileFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);
	DeleteObjectsByLayer(LAYER::TILE);
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szExt, L"rb");

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