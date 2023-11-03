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

void CPlayLevel::init()
{
	// 플레이어 생성
	//CPlayer* pPlayer = new CPlayer;

	//pPlayer->SetPos(Vec2(500.f, 200.f));
	//pPlayer->SetScale(Vec2(50.f, 50.f));
	//AddObject(PLAYER, pPlayer);

	// 몬스터 생성
	//CMonster* pMonster = nullptr;

	//pMonster = new CMonster;
	//pMonster->SetPos(Vec2(900.f, 500.f));
	//pMonster->SetScale(Vec2(100.f, 100.f));
	//AddObject(MONSTER, pMonster);

	// 플랫폼 설치
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(800.f, 700.f));
	AddObject(PLATFORM, pPlatform);


	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);

	// 충돌 설정
	CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLAYER);
	//CCollisionMgr::GetInst()->CheckCollision(PLAYER_PJ, MONSTER);
	CCollisionMgr::GetInst()->CheckCollision(PLAYER, PLATFORM);
}

void CPlayLevel::enter()
{	
	CCamera::GetInst()->FadeOut(0.3f);
	CCamera::GetInst()->FadeIn(0.3f);

	//CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\DM.wav");
	//pSound->SetVolume(100);
	//pSound->SetPosition(45.f);
	//pSound->Play(true);
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
