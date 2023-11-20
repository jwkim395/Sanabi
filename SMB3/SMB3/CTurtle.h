#pragma once
#include "CMonster.h"
class CTurtle :
    public CMonster
{
public:
    float velo;
    float deadTime;
    int onBlock;
    int status; // 1 : normal, 2 : ²®Áú

public:
    virtual void tick(float _DT) override;

    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    void setShellMove(float);

public:
    CLONE(CTurtle);
    CTurtle();
    CTurtle(const CTurtle& _Origin);
    ~CTurtle();
};

