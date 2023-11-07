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

#include "components.h"

CMario::CMario()
	: m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, jumpedTime(0.f)
{	
	SetName(L"Player");
	// 충돌체 컴포넌트 추가
	SetPos(Vec2(128.f, 700.f));
	SetScale(Vec2(64.f, 64.f));
	m_Collider = AddComponent<CCollider>(L"PlayerCollider");
	m_Collider->SetOffsetPos(Vec2(0.f, 10.f));
	m_Collider->SetScale(Vec2(40.f, 80.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -40.f));

	// Movement 컴포넌트 추가
	m_Movement = AddComponent<CMovement>(L"PlayerMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(30.f);
	m_Movement->SetMaxSpeed(192.f);
	m_Movement->SetFrictionScale(300.f);

	m_Movement->UseGravity(true);
	m_Movement->SetGravity(Vec2(0.f, 1760.f));
	m_Movement->SetGround(true);
}
/*
CPlayer::CPlayer(const CPlayer& _Origin)
	: CObj(_Origin)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
{
	m_Collider = GetComponent<CCollider>();
	m_Animator = GetComponent<CAnimator>();
	m_Movement = GetComponent<CMovement>();
}*/

CMario::~CMario()
{		
}

void CMario::tick(float _DT)
{	
	Super::tick(_DT);

	Vec2 vPos = GetPos();

	if (KEY_PRESSED(LEFT))
	{
		m_Movement->AddForce(Vec2(-1000.f, 0.f));
		//m_Animator->Play(L"WalkLeft", true);
	}

	if (KEY_RELEASED(LEFT))
	{
		//m_Animator->Play(L"IdleLeft", true);
	}

	if (KEY_PRESSED(RIGHT))
	{
		m_Movement->AddForce(Vec2(1000.f, 0.f));
		//m_Animator->Play(L"WalkRight", true);
	}
	if (KEY_RELEASED(RIGHT))
	{
		//m_Animator->Play(L"IdleRight", true);
	}

	if (KEY_TAP(SPACE))
	{
		if (m_Movement->IsGround()) {
			m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, -450.f));
			m_Movement->SetGround(false);
			jumpedTime = 0.f;
		}

		//CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		//CGuided* pProjectile = new CGuided;

		//Vec2 ProjectilePos = GetPos();
		//ProjectilePos.y -= GetScale().y / 2.f;

		//pProjectile->SetSpeed(500.f);
		//pProjectile->SetAngle(PI / 2.f);
		//pProjectile->SetPos(ProjectilePos);
		//pProjectile->SetScale(Vec2(25.f, 25.f));
		//pProjectile->SetDir(Vec2(0.f, -1.f));

		//CTaskMgr::GetInst()->AddTask(FTask{ CREATE_OBJECT, PLAYER_PJ, (UINT_PTR)pProjectile });

		//		
		//LOG(WARNING, L"경고");		
	}
	if (KEY_PRESSED(SPACE))
	{
		if (!m_Movement->IsGround() && jumpedTime <= 0.5f) {
			m_Movement->AddForce(Vec2(0.f, -1450.f));
			jumpedTime += DT;
		}
		//m_Animator->Play(L"WalkDown", true);
	}

	SetPos(vPos);
}

void CMario::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CPlatform*>(_OtherObj))
	{
		m_Movement->SetGround(true);
	}
}


void CMario::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CPlatform*>(_OtherObj))
	{
		m_Movement->SetGround(false);
	}
}