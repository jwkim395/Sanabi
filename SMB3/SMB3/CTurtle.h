#pragma once
#include "CMonster.h"
class CTurtle :
    public CMonster
{
public:
    float velo;
    float deadTime;
    int onBlock;
    int status;

public:
    virtual void tick(float _DT) override;

    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
};

