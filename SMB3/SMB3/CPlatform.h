#pragma once
#include "CObj.h"

class CPlatform :
    public CObj
{
    GENERATED_OBJECT(CObj);
protected:
    class CCollider* m_Collider;
    FFrame imagePos;
    class CTexture* m_Image;


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
    void SetScale(Vec2 v1) { m_Collider->SetScale(v1); };
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CPlatform);
    CPlatform();
    CPlatform(const CPlatform& _Origin);
    ~CPlatform();
};

