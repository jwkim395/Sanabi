#pragma once
#include "CEntity.h"
#include "CStateMachine.h"

#include "CObj.h"
#include "CAnimator.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster.h"
#include "CMario.h"

class CState :
    public CEntity
{
private:
    CStateMachine*  m_pSM;
    UINT            m_StateID;


public:
    CStateMachine* GetOwnerSM() {return m_pSM;}
    UINT GetStateID() { return m_StateID; }

public:
    virtual void finaltick(float _DT) = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    virtual CState* Clone() = 0;

public:
    CState();
    ~CState();

    friend class CStateMachine;
};

