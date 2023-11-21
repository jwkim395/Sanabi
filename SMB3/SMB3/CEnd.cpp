#include "pch.h"
#include "CEnd.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CBackGround.h"
#include "CSound.h"


void CEnd::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}

void CEnd::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (_OtherObj->GetLayerIdx() == PLAYER) {
		_OtherObj->GetMovement()->SetVelocity(Vec2(192.f, 0.f));
		CLevelMgr::GetInst()->setmTime(7.f);
		CLevelMgr::GetInst()->setMarioStatus(4);
		CSound* pSound = CAssetMgr::GetInst()->FindSound(L"StageClear");
		pSound->SetVolume(80);
		pSound->PlayToBGM();
		CBackGround* CourseClear;
		CourseClear = new CBackGround;
		CourseClear->SetPos(Vec2(GetPos().x, GetPos().y - 300.f));
		CourseClear->SetScale(Vec2(128.f, 16.f));
		CourseClear->setImagePos(Vec2(0.f, 0.f), Vec2(128.f, 16.f));
		CourseClear->setTexture(L"CourseClear", L"texture\\courseClear.png");
		CLevelMgr::GetInst()->GetCurLevel()->GetLayer(BACKGROUND)->AddObject(CourseClear);
	}
}

CEnd::CEnd() {
	m_Collider = AddComponent<CCollider>(L"EndCollider");
	m_Collider->SetScale(Vec2(128.f, 128.f));
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Image = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\69718.png");
	imagePos = { Vec2(195, 879), Vec2(32, 32), Vec2(0, 0), 0 }; //¿ÞÀ§, Å©±â, offset, duration
}

CEnd::~CEnd()
{
}
