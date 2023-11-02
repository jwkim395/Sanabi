#include "pch.h"
#include "CPlayer.h"

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

CPlayer::CPlayer()
	: m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
{	
	SetName(L"Player");

	// 애니메이터 컴포넌트 추가
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlas", L"texture\\link_alpha.bmp");

	m_Animator = AddComponent<CAnimator>(L"Animator");

	/*m_Animator->CreateAnimation(L"WalkDown", pAtlas, Vec2(0.f, 520.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
	m_Animator->CreateAnimation(L"WalkLeft", pAtlas, Vec2(0.f, 650.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
	m_Animator->CreateAnimation(L"WalkUp", pAtlas, Vec2(0.f, 780.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
	m_Animator->CreateAnimation(L"WalkRight", pAtlas, Vec2(0.f, 910.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);	
	m_Animator->CreateAnimation(L"IdleDown", pAtlas, Vec2(0.f, 0.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
	m_Animator->CreateAnimation(L"IdleLeft", pAtlas, Vec2(0.f, 130.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
	m_Animator->CreateAnimation(L"IdleUp", pAtlas, Vec2(0.f, 260.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 1);
	m_Animator->CreateAnimation(L"IdleRight", pAtlas, Vec2(0.f, 390.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
	m_Animator->SaveAnimations(L"animdata");*/

	m_Animator->LoadAnimation(L"animdata\\IdleDown.txt");
	m_Animator->LoadAnimation(L"animdata\\IdleLeft.txt");
	m_Animator->LoadAnimation(L"animdata\\IdleRight.txt");
	m_Animator->LoadAnimation(L"animdata\\IdleUp.txt");
	m_Animator->LoadAnimation(L"animdata\\WalkDown.txt");
	m_Animator->LoadAnimation(L"animdata\\WalkLeft.txt");
	m_Animator->LoadAnimation(L"animdata\\WalkRight.txt");
	m_Animator->LoadAnimation(L"animdata\\WalkUp.txt");
	
	m_Animator->Play(L"WalkDown", true);

	// 충돌체 컴포넌트 추가
	m_Collider = AddComponent<CCollider>(L"PlayerCollider");
	m_Collider->SetOffsetPos(Vec2(0.f, 10.f));
	m_Collider->SetScale(Vec2(40.f, 80.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -40.f));

	// Movement 컴포넌트 추가
	m_Movement = AddComponent<CMovement>(L"PlayerMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(200.f);
	m_Movement->SetMaxSpeed(400.f);		
	m_Movement->SetFrictionScale(1000.f);

	m_Movement->UseGravity(true);
	m_Movement->SetGravity(Vec2(0.f, 980.f));
	m_Movement->SetGround(true);
}

CPlayer::CPlayer(const CPlayer& _Origin)
	: CObj(_Origin)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
{
	m_Collider = GetComponent<CCollider>();
	m_Animator = GetComponent<CAnimator>();
	m_Movement = GetComponent<CMovement>();
}

CPlayer::~CPlayer()
{		
}

void CPlayer::tick(float _DT)
{	
	Super::tick(_DT);

	Vec2 vPos = GetPos();

	if (KEY_PRESSED(A))
	{
		m_Movement->AddForce(Vec2(-300.f, 0.f));
		//m_Animator->Play(L"WalkLeft", true);
	}

	if (KEY_RELEASED(A))
	{
		//m_Animator->Play(L"IdleLeft", true);
	}

	if (KEY_PRESSED(D))
	{
		m_Movement->AddForce(Vec2(300.f, 0.f));
		//m_Animator->Play(L"WalkRight", true);
	}
	if (KEY_RELEASED(D))
	{
		//m_Animator->Play(L"IdleRight", true);
	}


	if (KEY_PRESSED(W))
	{
		//m_Movement->AddForce(Vec2(0.f, -300.f));
		//m_Animator->Play(L"WalkUp", true);
	}
	if (KEY_RELEASED(W))
	{		
		//m_Animator->Play(L"IdleUp", true);
	}

	if (KEY_PRESSED(S))
	{
		m_Movement->AddForce(Vec2(0.f, 300.f));
		//m_Animator->Play(L"WalkDown", true);
	}
	if (KEY_RELEASED(S))
	{
		//m_Animator->Play(L"IdleDown", true);
	}

	if (KEY_TAP(SPACE))
	{
		m_Movement->SetGround(false);
		m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, -500.f));

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
		m_Movement->AddForce(Vec2(0.f, 300.f));
		//m_Animator->Play(L"WalkDown", true);
	}

	SetPos(vPos);
}

void CPlayer::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CPlatform*>(_OtherObj))
	{
		m_Movement->SetGround(true);
	}
}


void CPlayer::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CPlatform*>(_OtherObj))
	{
		m_Movement->SetGround(false);
	}
}