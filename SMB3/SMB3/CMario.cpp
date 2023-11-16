#include "pch.h"
#include "CMario.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CPathMgr.h"
#include "CEngine.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CLogMgr.h"
#include "CPlatform.h"
#include "CMonster.h"
#include "CLevelMgr.h"
#include "CItem.h"

#include "components.h"

CMario::CMario()
	: m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, status(0)
	, jumpedTime(0.f)
	, watchDir(true)
	, powering(4.f)
	, onBlock(0)
{	
	SetName(L"Player");
	// 충돌체 컴포넌트 추가
	SetPos(Vec2(128.f, 700.f));
	SetScale(Vec2(64.f, 64.f));
	m_Collider = AddComponent<CCollider>(L"MarioCollider");
	m_Collider->SetScale(Vec2(50.f, 64.f));
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));

	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"MarioAtlas", L"texture\\69712.png");
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"MarioLAtlas", L"texture\\69712_l.png");

	m_Animator = AddComponent<CAnimator>(L"Animator");
	m_Animator->LoadAnimation(L"animdata\\MINI_IDLE.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Dead.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Jump.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Run.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Turn.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Walk.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_TO_SUPER.txt");
	
	m_Animator->LoadAnimation(L"animdata\\MINI_IDLE_L.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Jump_L.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Run_L.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Turn_L.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Walk_L.txt");
	m_Animator->Play(L"MINI_IDLE", true);


	// Movement 컴포넌트 추가
	m_Movement = AddComponent<CMovement>(L"PlayerMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(30.f);
	m_Movement->SetMaxSpeed(192.f);
	m_Movement->SetFrictionScale(300.f);

	m_Movement->UseGravity(true);
	m_Movement->SetGravity(Vec2(0.f, 3000.f));
	m_Movement->SetGround(true);
}

CMario::~CMario()
{		
}

void CMario::tick(float _DT)
{
	if (CLevelMgr::GetInst()->getmTime() <= 0) {
		Vec2 temp = GetPos();
		Super::tick(_DT);

		Vec2 vPos = GetPos();
		if (KEY_TAP(DOWN) && status > 1) {
			m_Animator->Play(L"SUPER_Sit", true);
			m_Collider->SetScale(Vec2(64.f, 64.f));
			SetPos(Vec2(GetPos().x, GetPos().y + 32.f));
		}
		else if (KEY_RELEASED(DOWN) && status > 1) {
			m_Animator->Play(L"SUPER_IDLE", true);
			m_Collider->SetScale(Vec2(64.f, 128.f));
		}
		else if (KEY_PRESSED(KEY::LSHIFT))
		{
			if (KEY_TAP(LEFT)) {
				watchDir = false;
				m_Animator->Play(L"MINI_Run_L", true);
			}
			else if (KEY_TAP(RIGHT)) {
				watchDir = true;
				m_Animator->Play(L"MINI_Run", true);
			}
			else if (KEY_PRESSED(LEFT)) {
				m_Movement->SetMaxSpeed(350.f);
				m_Movement->AddForce(Vec2(-800.f, 0.f));
			}
			else if (KEY_PRESSED(RIGHT)) {
				m_Movement->SetMaxSpeed(350.f);
				m_Movement->AddForce(Vec2(800.f, 0.f));
			}
		}
		else if (KEY_TAP(LEFT))
		{
			watchDir = false;
			m_Animator->Play(L"MINI_Walk_L", true);
		}
		else if (KEY_PRESSED(LEFT)) {
			m_Movement->AddForce(Vec2(-800.f, 0.f));
		}
		else if (KEY_TAP(RIGHT))
		{
			watchDir = true;
			m_Animator->Play(L"MINI_Walk", true);
		}
		else if (KEY_PRESSED(RIGHT)) {
			m_Movement->AddForce(Vec2(800.f, 0.f));
		}
		SetPos(Vec2(GetPos().x, GetPos().y - 32.f));
		}
		if (KEY_RELEASED(KEY::LSHIFT))
		{
			m_Movement->SetMaxSpeed(192.f);
		}

		if (KEY_RELEASED(LEFT))
		{
			m_Animator->Play(L"MINI_IDLE_L", true);
		}

		if (KEY_RELEASED(RIGHT))
		{
			m_Animator->Play(L"MINI_IDLE", true);

		}

		if (KEY_TAP(SPACE) && watchDir)
		{
			m_Animator->Play(L"MINI_Jump", true);
			if (m_Movement->IsGround()) {
				m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, -700.f));
				m_Movement->SetGround(false);
				jumpedTime = 0.f;
			}
		}
		if (KEY_TAP(SPACE) && !watchDir)
		{
			m_Animator->Play(L"MINI_Jump_L", true);
			if (m_Movement->IsGround()) {
				m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, -700.f));
				m_Movement->SetGround(false);
				jumpedTime = 0.f;
			}
		}
		if (KEY_PRESSED(SPACE))
		{
			if (!m_Movement->IsGround() && jumpedTime <= 0.8f) {
				m_Movement->AddForce(Vec2(0.f, -2800.f * (1 - jumpedTime / 0.8f)));
				jumpedTime += DT;
			}
		}

		prevPos = temp;
		SetPos(vPos);
	}
}

void CMario::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CPlatform*>(_OtherObj))
	{
		float plattop = (_OtherCol->GetPos().y - _OtherCol->GetScale().y / 2.f);
		float prevbottom = (_OwnCol->GetPrevPos().y + _OwnCol->GetScale().y / 2.f);
		if (plattop >= prevbottom * 0.98f)
			m_Movement->SetGround(true);
		onBlock += 1;
	}
	if (dynamic_cast<CMonster*>(_OtherObj) && !_OtherObj->IsDead())
	{
		// 콜라이터 양쪽 x좌표 둘중 하나가 플랫폼 x좌표 범위안 + y좌표가
		if ((((m_Collider->GetPos().x - m_Collider->GetScale().x / 2.f > _OtherObj->GetPos().x - _OtherObj->GetScale().x / 2.f + 1.f)
			&& (m_Collider->GetPos().x - m_Collider->GetScale().x / 2.f < _OtherObj->GetPos().x + _OtherObj->GetScale().x / 2.f) -1.f)
			|| ((m_Collider->GetPos().x + (m_Collider->GetScale().x / 2.f) > _OtherObj->GetPos().x - (_OtherObj->GetScale().x / 2.f) + 1.f)
			&& (m_Collider->GetPos().x + (m_Collider->GetScale().x / 2.f) < _OtherObj->GetPos().x + (_OtherObj->GetScale().x / 2.f) -1.f)))
			&& abs(m_Collider->GetPos().y + m_Collider->GetScale().y/2 - (_OtherCol->GetPos().y - _OtherCol->GetScale().y/2)) < abs(m_Collider->GetPos().y + m_Collider->GetScale().y/2 - (_OtherCol->GetPos().y - (_OtherCol->GetScale().y / 2)/0.9)))
			m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, -1200.f));
		else{
			powerDown();
		}
		
	}
	if ((UINT)LAYER::ITEM == _OtherObj->GetLayerIdx()) {
		CItem* curItem = dynamic_cast<CItem*>(_OtherObj);
		if (curItem) {
			if (curItem->getIsMoving() && curItem->getItemNum() == 2) {
				powerUp();
			}
		}
	}
}


void CMario::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	onBlock -= 1;
	if (onBlock == 0)
		m_Movement->SetGround(false);
}

void CMario::powerUp()
{
	if (status == 0) {
		status = 1;
		m_Animator->Play(L"MINI_TO_SUPER", true);
		SetPos(Vec2(GetPos().x, GetPos().y - 32.f));
		SetScale(Vec2(64.f, 128.f));
		m_Collider->SetScale(Vec2(64.f, 128.f));
		CLevelMgr::GetInst()->setmTime(1.5f);
	}
}



void CMario::powerDown()
{
	if (status > 1) {
		
	}
	else if (status == 1) {
		// 작아지는 애니메이션
		m_Collider->SetScale(Vec2(50.f, 64.f));
		m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
		CLevelMgr::GetInst()->setmTime(1.5f);
	}
	else {
		dead();
	}
}

void CMario::dead()
{
	m_Animator->Play(L"MINI_Dead", true);
	m_Movement->SetVelocity(Vec2(0.f, -1200.f));
	CLevelMgr::GetInst()->setmTime(5.f);
}


