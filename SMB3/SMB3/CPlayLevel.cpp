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
#include "CBackGround.h"

#include "platforms.h"

void CPlayLevel::init()
{
	// 충돌 설정
	CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLAYER);
	CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLATFORM);
	CCollisionMgr::GetInst()->CheckCollision(PLAYER, PLATFORM);
	CCollisionMgr::GetInst()->CheckCollision(ITEM, PLAYER);
	CCollisionMgr::GetInst()->CheckCollision(ITEM, PLATFORM);
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
		for (int i = 0; i < curMapTiles.size(); ++i) {
			CTile* tToObj = dynamic_cast<CTile*>(curMapTiles[i]);
			if (nullptr != tToObj)
				setObj(tToObj);
		}
	}

	CLevelMgr::GetInst()->setMarioStatus(1);
	CCamera::GetInst()->FadeIn(0.3f);
}

void CPlayLevel::exit()
{
	CLevelMgr::GetInst()->clearMapData();
	DeleteAllObjects();
}

void CPlayLevel::tick()
{
	if (CLevelMgr::GetInst()->getmTime() <= 0.f && CLevelMgr::GetInst()->getMarioStatus() == 3) {
		DeleteAllObjects();
		enter();
	}
	if (CLevelMgr::GetInst()->getmTime() <= 0.f && CLevelMgr::GetInst()->getMarioStatus() == 4) {
		ChangeLevel(LEVEL_TYPE::EDITOR_LEVEL);
	}
	if (CLevelMgr::GetInst()->getMarioStatus() == 4) {
		CCollisionMgr::GetInst()->UncheckCollision(MONSTER, PLAYER);
		CCollisionMgr::GetInst()->UncheckCollision(MONSTER, PLATFORM);
		CCollisionMgr::GetInst()->UncheckCollision(ITEM, PLAYER);
		CCollisionMgr::GetInst()->UncheckCollision(ITEM, PLATFORM);
	}
	else if (CLevelMgr::GetInst()->getmTime() > 0.f) {
		CCollisionMgr::GetInst()->UncheckCollision(MONSTER, PLAYER);
		CCollisionMgr::GetInst()->UncheckCollision(MONSTER, PLATFORM);
		CCollisionMgr::GetInst()->UncheckCollision(PLAYER, PLATFORM);
		CCollisionMgr::GetInst()->UncheckCollision(ITEM, PLAYER);
		CCollisionMgr::GetInst()->UncheckCollision(ITEM, PLATFORM);
	}
	else {
		CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLAYER);
		CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLATFORM);
		CCollisionMgr::GetInst()->CheckCollision(PLAYER, PLATFORM);
		CCollisionMgr::GetInst()->CheckCollision(ITEM, PLAYER);
		CCollisionMgr::GetInst()->CheckCollision(ITEM, PLATFORM);
	}
	CLevel::tick();
	

	// Enter 키가 눌리면 StartLevel 로 변환
}

void CPlayLevel::setObj(CTile* _tile)
{
	if (_tile->GetImgIdx() == 0) {
		CMario* pPlayer = new CMario;
		pPlayer->SetPos(Vec2(_tile->GetPos().x, _tile->GetPos().y - 1.f));
		pPlayer->SetScale(Vec2(64.f, 64.f));
		AddObject(PLAYER, pPlayer);
	}
	// 원본 이미지로 불러오는 설정좀 해야댐 마리오는 되어있음
	// 해당 함수에서 불러올 수 있도록 조정중
	else if (_tile->GetImgIdx() == 1) {
		// 코인 나오는 박스 추가
		CBonusBox* cBox = new CBonusBox();
		cBox->SetPos(_tile->GetPos());
		cBox->SetScale(Vec2(64.f, 64.f));
		AddObject(PLATFORM, cBox);
		CItem* nCoin = new CItem(1);
		nCoin->SetPos(_tile->GetPos());
		nCoin->SetScale(Vec2(65.f, 65.f));
		AddObject(ITEM, nCoin);
	}
	else if (_tile->GetImgIdx() == 2) {
		// 파워업 아이템 나오는 박스 추가
		CBonusBox* cBox = new CBonusBox();
		cBox->SetPos(_tile->GetPos());
		cBox->SetScale(Vec2(64.f, 64.f));
		AddObject(PLATFORM, cBox);
		CItem* nCoin = new CItem(2);
		nCoin->SetPos(_tile->GetPos());
		nCoin->SetScale(Vec2(65.f, 65.f));
		AddObject(ITEM, nCoin);
	}
	else if (_tile->GetImgIdx() == 3) {
		// 코인 추가
		CItem* nCoin = new CItem(3);
		nCoin->SetPos(_tile->GetPos());
		nCoin->SetScale(Vec2(64.f, 64.f));
		AddObject(ITEM, nCoin);

	}
	else if (_tile->GetImgIdx() == 4 || (_tile->GetImgIdx() >= 6 && _tile->GetImgIdx() <= 11)) {
		// 안부서지는 박스, 땅 추가
		CUnbreakableBlock* CUnBlock = new CUnbreakableBlock(_tile->GetImgIdx());
		CUnBlock->SetPos(_tile->GetPos());
		CUnBlock->SetScale(Vec2(64.f, 64.f));
		AddObject(PLATFORM, CUnBlock);
	}
	else if (_tile->GetImgIdx() == 5) {
		// 부서지는 박스 추가
		CBreakableBlock* CBlock = new CBreakableBlock;
		CBlock->SetPos(_tile->GetPos());
		CBlock->SetScale(Vec2(64.f, 64.f));
		AddObject(PLATFORM, CBlock);
	}
	else if (_tile->GetImgIdx() >= 12 && _tile->GetImgIdx() <= 15) {
		// 파이프 추가
		CPipe* Cp = new CPipe(_tile->GetImgIdx());
		Cp->SetPos(_tile->GetPos());
		Cp->SetScale(Vec2(64.f, 64.f));
		AddObject(PLATFORM, Cp);
	}
	else if (_tile->GetImgIdx() >= 16 && _tile->GetImgIdx() <= 24) {
		// 맨 위에만 충돌체 있는 박스 추가
	}
	else if (_tile->GetImgIdx() == 25) {
		// end tile
		CEnd* endTile = new CEnd;
		endTile->SetPos(_tile->GetPos());
		endTile->SetScale(Vec2(64.f, 64.f));
		AddObject(PLATFORM, endTile);
		
		// 검은 배경
		CBackGround* mainEndBackGround = new CBackGround;
		mainEndBackGround->SetPos(Vec2(_tile->GetPos().x, _tile->GetPos().y - 50.f));
		mainEndBackGround->SetScale(Vec2(1000.f, 1024.f));
		mainEndBackGround->setImagePos(Vec2(1.f, 3684.f), Vec2(500.f, 512.f));
		mainEndBackGround->setTexture(L"BackAtlas", L"texture\\back.png");
		AddObject(BACKGROUND, mainEndBackGround);
		// 외각 삼각형
		CBackGround* endBackGround;
		for (float i = 64.f; i <= 1024.f; i += 128.f) {
			endBackGround = new CBackGround;
			endBackGround->SetPos(Vec2(_tile->GetPos().x - mainEndBackGround->GetScale().x / 2 - 64.f
				, mainEndBackGround->GetPos().y - mainEndBackGround->GetScale().y / 2 + i));
			endBackGround->SetScale(Vec2(64.f, 64.f));
			endBackGround->setImagePos(Vec2(130.f, 879.f), Vec2(64.f, 64.f));
			endBackGround->setTexture(L"TileAtlas", L"texture\\69718.png");
			AddObject(BACKGROUND, endBackGround);
		}
	}
	else if (_tile->GetImgIdx() >= 26) {
		// 굼바 추가
		CMonster* pMonster = new CGoomba;
		pMonster->SetPos(_tile->GetPos());
		pMonster->SetScale(Vec2(64.f, 64.f));
		AddObject(MONSTER, pMonster);
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