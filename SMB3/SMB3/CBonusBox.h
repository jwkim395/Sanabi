#pragma once
#include "CPlatform.h"
#include "CItem.h"

class CBonusBox :
    public CPlatform
{
private:
public:
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
public:
    CBonusBox();
    ~CBonusBox();
    
};

