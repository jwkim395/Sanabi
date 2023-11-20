#include "pch.h"
#include "CTurtle.h"
#include "CAssetMgr.h"
#include "CAnimator.h"
#include "CTimeMgr.h"
#include "CMario.h"
#include "CPlatform.h"
#include "CLevelMgr.h"

void CTurtle::tick(float _DT)
{
	if (GetPos().y > CLevelMgr::GetInst()->getMapData()->vBottomRight.y)
		Destroy();
	if(abs(m_Movement->GetVelocity().x > 0))
		m_Movement->AddForce(Vec2(velo, 0.f));
}

void CTurtle::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	// 위에서 밟았으면
	if (dynamic_cast<CMario*>(_OtherObj)) {
		float monTop = (_OwnCol->GetPos().y - _OwnCol->GetScale().y / 2.f);
		float playerprevbottom = (_OtherCol->GetPrevPos().y + _OtherCol->GetScale().y / 2.f);

		if (monTop >= playerprevbottom * 0.98f)
		{
			if (status == 1) {
				m_Movement->SetVelocity(Vec2(0.f, 0.f));
				m_Movement->SetInitSpeed(220.f);
				m_Movement->SetMaxSpeed(220.f);
				m_Animator->Play(L"GOOMBA_Shell_IDLE", true);
				m_Collider->SetScale(Vec2(64.f, 64.f));
				SetPos(Vec2(GetPos().x, GetPos().x + 10.f));
			}
			else {
				// 마리오의 중심 기준 거북이의 왼쪽으로 찍으면 velo음수
				// 오른쪽이면 양수
				// 움직이고 있는 상태에서 찍으면 정지
				if (abs(m_Movement->GetVelocity().x) > 0) {
					m_Movement->SetVelocity(Vec2(0, 0));
					m_Animator->Play(L"GOOMBA_Shell_IDLE", true);
				}
				else {
					if (GetPos().x - _OtherObj->GetPos().x > 0)
						velo = abs(velo);
					else
						velo = abs(velo) * -1;
					m_Movement->AddForce(Vec2(velo, 0.f));
				}
			}
		}
	}
	if (dynamic_cast<CPlatform*>(_OtherObj)) {
		if (GetPos().y > _OtherObj->GetPos().y - _OtherObj->GetScale().y / 2 &&
			GetPos().y < _OtherObj->GetPos().y + _OtherObj->GetScale().y / 2)
			velo *= -1.f;
		if (status == 1) {
			if(velo < 0)
				m_Animator->Play(L"TURTLE_IDLE_L", true);
			else
				m_Animator->Play(L"TURTLE_IDLE", true);
		}
		float plattop = (_OtherCol->GetPos().y - _OtherCol->GetScale().y / 2.f);
		float prevbottom = (_OwnCol->GetPrevPos().y + _OwnCol->GetScale().y / 2.f);
		if (plattop >= prevbottom * 0.98f)
			m_Movement->SetGround(true);
		onBlock += 1;
	}
}

void CTurtle::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CPlatform*>(_OtherObj)) {
		onBlock -= 1;
		if (onBlock == 0)
			m_Movement->SetGround(false);
	}
}

CTurtle::CTurtle():CMonster(), velo(-50000.f), onBlock(0)
{
	m_Collider = AddComponent<CCollider>(L"TurtleCollider");
	m_Collider->SetScale(Vec2(64.f, 120.f));
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"MonsterAtlas", L"texture\\119432.png");
	m_Animator = AddComponent<CAnimator>(L"TurtleAnimator");
	m_Animator->LoadAnimation(L"animdata\\TURTLE_IDLE.txt");
	m_Animator->LoadAnimation(L"animdata\\TURTLE_IDLE_L.txt");
	m_Animator->LoadAnimation(L"animdata\\TURTLE_Shell_IDLE.txt");
	m_Animator->LoadAnimation(L"animdata\\TURTLE_Shell_Move.txt");
	m_Animator->Play(L"TURTLE_IDLE_L", true);


	m_Movement = AddComponent<CMovement>(L"TurtleMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(64.f);
	m_Movement->SetMaxSpeed(64.f);
	m_Movement->UseGravity(true);
	m_Movement->SetGravity(Vec2(0.f, 3000.f));
	m_Movement->SetGround(true);
}

CTurtle::CTurtle(const CTurtle& _Origin)
{
}

CTurtle::~CTurtle()
{
}
