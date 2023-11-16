#pragma once
#include "CPlatform.h"
class CBonusBox :
    public CPlatform
{
public:
    class CItem* mItem;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
public:
    CBonusBox(int);
    ~CBonusBox();
    
};

