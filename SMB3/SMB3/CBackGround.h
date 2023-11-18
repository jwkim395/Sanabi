#pragma once
#include "CObj.h"
#include "CAssetMgr.h"

class CBackGround :
    public CObj
{
    GENERATED_OBJECT(CObj);
protected:
    FFrame imagePos;
    class CTexture* m_Image;

public:
    void setImagePos(Vec2 _vLeftTop, Vec2 _vCutSize) { imagePos.vLeftTop = _vLeftTop; imagePos.vCutSize = _vCutSize; }
    void setTexture(const wstring& _strTextureName, const wstring& _strRelativePath) { m_Image = CAssetMgr::GetInst()->LoadTexture(_strTextureName, _strRelativePath); }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CBackGround);
    CBackGround();
    CBackGround(const CBackGround& _Origin);
    ~CBackGround();
};

