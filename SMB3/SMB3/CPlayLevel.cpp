#include "pch.h"
#include "CPlayLevel.h"

#include "CMario.h"
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
#include "CGoomba.h"

void CPlayLevel::init()
{
	// 충돌 설정
	CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLAYER);
	CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLATFORM);
	CCollisionMgr::GetInst()->CheckCollision(PLAYER_PJ, MONSTER);
	CCollisionMgr::GetInst()->CheckCollision(PLAYER, PLATFORM);
	
}

void CPlayLevel::enter()
{	
	/*
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
		curMapTiles.clear();
	}
	// map > obj 화 필요

	*/
	CMario* pPlayer = new CMario;
	pPlayer->SetPos(Vec2(128.f, 700.f));
	pPlayer->SetScale(Vec2(64.f, 64.f));
	AddObject(PLAYER, pPlayer);

	CMonster* pMonster = new CGoomba;
	pMonster->SetPos(Vec2(400.f, 700.f));
	pMonster->SetScale(Vec2(64.f, 64.f));
	AddObject(MONSTER, pMonster);

	// 플랫폼 설치
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(10.f, 700.f));
	pPlatform->SetScale(Vec2(1500.f, 64.f));
	AddObject(PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(500.f, 572.f));
	pPlatform->SetScale(Vec2(64.f, 192.f));
	AddObject(PLATFORM, pPlatform);

	

	
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);
	CCamera::GetInst()->FadeIn(0.3f);

	mIsDead = false;
}

void CPlayLevel::exit()
{
	DeleteAllObjects();
}

void CPlayLevel::tick()
{
	CLevel::tick();

	// Enter 키가 눌리면 StartLevel 로 변환
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
	//fread(&mLeft, sizeof(Vec2), 1, pFile);
	//fread(&mRightBottom, sizeof(Vec2), 1, pFile);
	//fread(&isMarioSetted, sizeof(bool), 1, pFile);
	//fread(&isEndSetted, sizeof(bool), 1, pFile);

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