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
#include "CTurtle.h"
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
	m_Animator = AddComponent<CAnimator>(L"Animator");
	m_Animator->LoadAnimation(L"animdata\\MINI_IDLE.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Dead.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Jump.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Run.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Walk.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_TO_SUPER.txt");
	
	m_Animator->LoadAnimation(L"animdata\\SUPER_IDLE.txt");
	m_Animator->LoadAnimation(L"animdata\\SUPER_Sit.txt");
	m_Animator->LoadAnimation(L"animdata\\SUPER_Jump.txt");
	m_Animator->LoadAnimation(L"animdata\\SUPER_Run.txt");
	m_Animator->LoadAnimation(L"animdata\\SUPER_Walk.txt");

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"MarioLAtlas", L"texture\\69712_l.png");
	m_Animator->LoadAnimation(L"animdata\\MINI_IDLE_L.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Jump_L.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Run_L.txt");
	m_Animator->LoadAnimation(L"animdata\\MINI_Walk_L.txt");

	m_Animator->LoadAnimation(L"animdata\\SUPER_IDLE_L.txt");
	m_Animator->LoadAnimation(L"animdata\\SUPER_Jump_L.txt");
	m_Animator->LoadAnimation(L"animdata\\SUPER_Run_L.txt");
	m_Animator->LoadAnimation(L"animdata\\SUPER_Sit_L.txt");
	m_Animator->LoadAnimation(L"animdata\\SUPER_Walk_L.txt");
	
	m_Animator->Play(L"MINI_IDLE", true);


	// Movement 컴포넌트 추가
	m_Movement = AddComponent<CMovement>(L"PlayerMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(5.f);
	m_Movement->SetMaxSpeed(192.f);
	m_Movement->SetFrictionScale(300.f);

	m_Movement->UseGravity(true);
	m_Movement->SetGravity(Vec2(0.f, 3000.f));
	m_Movement->SetGround(false);
}

CMario::~CMario()
{		
}

void CMario::tick(float _DT)
{
	if (CLevelMgr::GetInst()->getmTime() <= 0) {
		Super::tick(_DT);

		if (GetPos().y > CLevelMgr::GetInst()->getMapData()->vBottomRight.y) {
			dead();
			return;
		}

		if (KEY_TAP(LEFT)) {
			watchDir = false;
		}
		if (KEY_TAP(RIGHT)) {
			watchDir = true;
		}
		if (KEY_TAP(DOWN) && status >= 1) {
			if(watchDir)
				m_Animator->Play(L"SUPER_Sit", true);
			else
				m_Animator->Play(L"SUPER_Sit_L", true);
			m_Collider->SetScale(Vec2(64.f, 72.f));
			SetPos(Vec2(GetPos().x, GetPos().y + 18.f));
		}
		else if (KEY_PRESSED(DOWN) && status >= 1) {
			if (watchDir)
				m_Animator->Play(L"SUPER_Sit", true);
			else
				m_Animator->Play(L"SUPER_Sit_L", true);
		}
		else if (KEY_RELEASED(DOWN) && status >= 1) {
			if (watchDir)
				m_Animator->Play(L"SUPER_IDLE", true);
			else
				m_Animator->Play(L"SUPER_IDLE_L", true);
			m_Collider->SetScale(Vec2(64.f, 112.f));
			SetPos(Vec2(GetPos().x, GetPos().y - 18.f));
		}
		else if (KEY_PRESSED(KEY::LSHIFT))
		{
			m_Movement->SetMaxSpeed(350.f);
			if (KEY_TAP(LEFT)) {
				watchDir = false;
				if (status >= 1) 
					m_Animator->Play(L"SUPER_Run_L", true);
				else 
					m_Animator->Play(L"MINI_Run_L", true);
			}
			else if (KEY_TAP(RIGHT)) {
				watchDir = true;
				if (status >= 1) 
					m_Animator->Play(L"SUPER_Run", true);
				else
					m_Animator->Play(L"MINI_Run", true);
			}
			else if (KEY_PRESSED(LEFT)) {
				if (status == 0 && m_Animator->m_CurAnim->GetName() != L"MINI_Run_L") {
					m_Animator->Play(L"MINI_Run_L", true);
				}
				else if(status == 1 && m_Animator->m_CurAnim->GetName() != L"SUPER_Run_L")
					m_Animator->Play(L"SUPER_Run_L", true);
				m_Movement->AddForce(Vec2(-800.f, 0.f));
			}
			else if (KEY_PRESSED(RIGHT)) {
				if (status == 0 && m_Animator->m_CurAnim->GetName() != L"MINI_Run") {
					m_Animator->Play(L"MINI_Run", true);
				}
				else if (status == 1 && m_Animator->m_CurAnim->GetName() != L"SUPER_Run")
					m_Animator->Play(L"SUPER_Run", true);
				m_Movement->AddForce(Vec2(800.f, 0.f));
			}
		}
		if (KEY_NONE(KEY::LSHIFT) || KEY_RELEASED(KEY::LSHIFT))
		{
			m_Movement->SetMaxSpeed(192.f);

			if (KEY_TAP(LEFT))
			{
				watchDir = false;
				if (status >= 1)
					m_Animator->Play(L"SUPER_Walk_L", true);
				else
					m_Animator->Play(L"MINI_Walk_L", true);
			}
			else if (KEY_PRESSED(LEFT)) {
				if (status == 0 && m_Animator->m_CurAnim->GetName() != L"MINI_Walk_L") {
					m_Animator->Play(L"MINI_Walk_L", true);
				}
				else if (status == 1 && m_Animator->m_CurAnim->GetName() != L"SUPER_Walk_L")
					m_Animator->Play(L"SUPER_Walk_L", true);
				m_Movement->AddForce(Vec2(-800.f, 0.f));
			}
			else if (KEY_TAP(RIGHT))
			{
				watchDir = true;
				if (status >= 1)
					m_Animator->Play(L"SUPER_Walk", true);
				else
					m_Animator->Play(L"MINI_Walk", true);
			}
			else if (KEY_PRESSED(RIGHT)) {
				if (status == 0 && m_Animator->m_CurAnim->GetName() != L"MINI_Walk") {
					m_Animator->Play(L"MINI_Walk", true);
				}
				else if (status == 1 && m_Animator->m_CurAnim->GetName() != L"SUPER_Walk")
					m_Animator->Play(L"SUPER_Walk", true);
				m_Movement->AddForce(Vec2(800.f, 0.f));
			}
			else if (KEY_RELEASED(LEFT))
			{
				if (status >= 1) {
					m_Animator->Play(L"SUPER_IDLE_L", true);
				}
				else
					m_Animator->Play(L"MINI_IDLE_L", true);
			}
			else if (KEY_RELEASED(RIGHT))
			{
				if (status >= 1) {
					m_Animator->Play(L"SUPER_IDLE", true);
				}
				else
					m_Animator->Play(L"MINI_IDLE", true);
			}
		}
		if (KEY_TAP(SPACE) && watchDir)
		{
			if (status >= 1) {
				m_Animator->Play(L"SUPER_Jump", true);
			}
			else
				m_Animator->Play(L"MINI_Jump", true);

			if (m_Movement->IsGround()) {
				m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, -700.f));
				m_Movement->SetGround(false);
				jumpedTime = 0.f;
				onBlock = 0;
			}
		}
		if (KEY_TAP(SPACE) && !watchDir)
		{
			if (status >= 1) {
				m_Animator->Play(L"SUPER_Jump_L", true);
			}
			else
				m_Animator->Play(L"MINI_Jump_L", true);

			if (m_Movement->IsGround()) {
				m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, -700.f));
				m_Movement->SetGround(false);
				jumpedTime = 0.f;
				onBlock = 0;
			}
		}
		if (KEY_PRESSED(SPACE))
		{
			if (status >= 1 && watchDir) 
				m_Animator->Play(L"SUPER_Jump", true);
			else if (status >= 1 && !watchDir)
				m_Animator->Play(L"SUPER_Jump_L", true);
			else if (watchDir)
				m_Animator->Play(L"MINI_Jump", true);
			else
				m_Animator->Play(L"MINI_Jump_L", true);

			if (!m_Movement->IsGround() && jumpedTime <= 0.8f) {
				m_Movement->AddForce(Vec2(0.f, -2800.f * (1 - jumpedTime / 0.8f)));
				jumpedTime += DT;
			}
		}
		if (KEY_TAP(_0)) {
			dead();
		}
	}
	else if (CLevelMgr::GetInst()->getmTime() > 0 && CLevelMgr::GetInst()->getMarioStatus() == 3) {
		m_Movement->AddForce(Vec2(0.f, 1200.f));
	}
	else if (CLevelMgr::GetInst()->getMarioStatus() == 4) {
		m_Movement->SetVelocity(Vec2(120.f, m_Movement->GetVelocity().y));
		if (status == 0 && m_Animator->m_CurAnim->GetName() != L"MINI_Walk") {
			m_Animator->Play(L"MINI_Walk", true);
		}
		else if (status == 1 && m_Animator->m_CurAnim->GetName() != L"SUPER_Walk") {
			m_Animator->Play(L"SUPER_Walk", true);
		}
	}
}

void CMario::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CPlatform*>(_OtherObj))
	{
		float plattop = (_OtherCol->GetPos().y - _OtherCol->GetScale().y / 2.f);
		float prevbottom = (_OwnCol->GetPrevPos().y + _OwnCol->GetScale().y / 2.f);
		if (plattop >= prevbottom * 0.99f)
			m_Movement->SetGround(true);
		onBlock += 1;
	}
	if (dynamic_cast<CMonster*>(_OtherObj))
	{
		float monTop = (_OtherCol->GetPos().y - _OtherCol->GetScale().y / 2.f);
		float playerprevbottom = (_OwnCol->GetPrevPos().y + _OwnCol->GetScale().y / 2.f);

		if (monTop >= playerprevbottom * 0.98f)
			m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, -1000.f));
		else {
			CTurtle* isTur = dynamic_cast<CTurtle*>(_OtherObj);
			if (isTur && abs(isTur->GetMovement()->GetVelocity().x ) == 0.f) {
				isTur->setShellMove(GetPos().x);
			}
			else
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
	if (onBlock > 0)
		onBlock -= 1;
	if (onBlock == 0)
		m_Movement->SetGround(false);
}

void CMario::powerUp()
{
	if (status == 0) {
		status = 1;
		m_Animator->Play(L"MINI_TO_SUPER", true);
		SetPos(Vec2(GetPos().x, GetPos().y - 16.f));
		SetScale(Vec2(64.f, 112.f));
		m_Collider->SetScale(Vec2(62.f, 112.f));
		CLevelMgr::GetInst()->setMarioStatus(2);
		CLevelMgr::GetInst()->setmTime(1.4f);
	}
}



void CMario::powerDown()
{
	if (status > 1) {
		
	}
	else if (status == 1) {
		--status;
		m_Animator->Play(L"MINI_TO_SUPER", true);
		SetPos(Vec2(GetPos().x, GetPos().y + 16.f));
		SetScale(Vec2(64.f, 64.f));
		m_Collider->SetScale(Vec2(50.f, 64.f));
		CLevelMgr::GetInst()->setMarioStatus(2);
		CLevelMgr::GetInst()->setmTime(1.4f);
	}
	else {
		dead();
	}
}

void CMario::dead()
{
	m_Animator->Play(L"MINI_Dead", true);
	m_Movement->SetVelocity(Vec2(0.f, -800.f));
	CLevelMgr::GetInst()->setmTime(5.f);
	CLevelMgr::GetInst()->setMarioStatus(3);
}


