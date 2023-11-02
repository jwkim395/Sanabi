#pragma once
#include "CEntity.h"


class CObj;

class CComponent :
    public CEntity
{
private:
    CObj*  m_pOwner;

public:
    CObj* GetOwner() { return m_pOwner; }
  

public:
    virtual void tick(float _DT) {}
    virtual void finaltick(float _DT) = 0;
    virtual void render(HDC _dc){}

public:
    virtual CComponent* Clone() = 0;

public:
    CComponent(CObj* _Owner);
    ~CComponent();

    friend class CObj;
};

