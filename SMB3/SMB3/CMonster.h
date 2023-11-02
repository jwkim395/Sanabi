#pragma once
#include "CObj.h"


class CCollider;
class CTexture;

class CMonster :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    FMonInfo        m_Info;
    CCollider*      m_Collider;
    CStateMachine*  m_AI;


    CTexture*   m_Texture;

public:
    void SetMonsterInfo(const FMonInfo& _Info) { m_Info = _Info; }

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;


public:
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    
public:
    CLONE(CMonster);
    CMonster();
    CMonster(const CMonster& _Origin);
    ~CMonster();
};

