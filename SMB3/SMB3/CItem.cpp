#include "pch.h"
#include "CItem.h"
#include "CAssetMgr.h"
#include "CTimeMgr.h"

#include "CSound.h"
#include "CSoundMgr.h"


void CItem::tick(float _DT)
{
	if (isMoving && overing <= 0 && itemNum == 2) {
		m_Movement->UseGravity(true);
		m_Movement->AddForce(Vec2(velo, 0.f));
	}
	else if (overing <= 0.f) {
		if (itemNum == 2) {
			SetPos(GetPos() - Vec2(0.f, 64.f) * (_DT));
			m_Movement->SetGround(false);
			isMoving = true;
		}
		else {
			Destroy();
		}
	}
	else if (overing <= 1.f) {
		SetPos(GetPos() - Vec2(0.f, 64.f) * (_DT / 1.f));
		overing -= _DT;
	}
}

void CItem::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx()) {
		if (isMoving) {
			SetDead();
			Destroy();
		}
		else {
			if (itemNum == 2) {
				CSound* pSound = CAssetMgr::GetInst()->FindSound(L"PowerUpAppear");
				pSound->SetVolume(80);
				pSound->Play();
				overing = 1.f;
			}
			else {
				overing = 0.5f;
				CSound* pSound = CAssetMgr::GetInst()->FindSound(L"Coin");
				pSound->SetVolume(80);
				pSound->Play();
				SetPos(GetPos() - Vec2(0.f, 64.f) * (0.8f));
			}
		}
	}
	if (dynamic_cast<CPlatform*>(_OtherObj)) {
		if (GetPos().y > _OtherObj->GetPos().y - _OtherObj->GetScale().y / 2 &&
			GetPos().y < _OtherObj->GetPos().y + _OtherObj->GetScale().y / 2)
			velo *= -1.f;
		float plattop = (_OtherCol->GetPos().y - _OtherCol->GetScale().y / 2.f);
		float prevbottom = (_OwnCol->GetPrevPos().y + _OwnCol->GetScale().y / 2.f);
		if (plattop >= prevbottom * 0.98f)
			m_Movement->SetGround(true);
		onBlock += 1;
	}

}

void CItem::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}

void CItem::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CPlatform*>(_OtherObj)) {
		onBlock -= 1;
		if (onBlock == 0)
			m_Movement->SetGround(false);
	}
}

CItem::CItem(int idx):CPlatform(), velo(-50000.f), onBlock(0)
{
	m_Collider = AddComponent<CCollider>(L"ItemCollider");
	m_Collider->SetScale(Vec2(50.f, 62.f));
	m_Collider->SetOffsetPos(Vec2(0.f, 2.f));
	setIsMoving(false);
	if (idx == 2) { // 2, 3
		itemNum = 2;
		imagePos = { Vec2(1, 249), Vec2(16, 16), Vec2(0, 0), 0 }; //¿ÞÀ§, Å©±â, offset, duration
		m_Image = CAssetMgr::GetInst()->LoadTexture(L"MarioAtlas", L"texture\\69712.png");
	}
	else if (idx == 1 || idx == 3) {
		itemNum = 1;
		imagePos = { Vec2(120, 1), Vec2(16, 16), Vec2(0, 0), 0 };
		m_Image = CAssetMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\69718.png");
	}
	overing = 2.f;
	m_Movement = AddComponent<CMovement>(L"ItemMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(150.f);
	m_Movement->SetMaxSpeed(150.f);
	m_Movement->UseGravity(false);
	m_Movement->SetGravity(Vec2(0.f, 3000.f));
	m_Movement->SetGround(true);
}

CItem::~CItem()
{
}
