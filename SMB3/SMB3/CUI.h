#pragma once
#include "CObj.h"

class CUI :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CUI*                m_ParentUI;
    vector<CUI*>        m_vecChildUI;
    Vec2                m_vFinalPos;

    bool                m_bMouseOn;
    bool                m_bMouseOn_Prev;

    bool                m_bMouseLBtnDown;

public:
    void AddChildUI(CUI* _ChildUI)
    {
        m_vecChildUI.push_back(_ChildUI);
        _ChildUI->m_ParentUI = this;
    }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    virtual void OnHovered(Vec2 _vMousePos) {}
    virtual void MouseOn(Vec2 _vMousePos) {}
    virtual void OnUnHovered(Vec2 _vMousePos) {}

    virtual void LBtnDown(Vec2 _vMousePos){}
    virtual void LBtnUp(Vec2 _vMousePos) {}
    virtual void LBtnClicked(Vec2 _vMousePos){}


public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    bool IsLBtnDown() { return m_bMouseLBtnDown; }

public:
    virtual CUI* Clone() = 0;
    CUI();
    CUI(const CUI& _Origin);
    ~CUI();

    friend class CUIMgr;
};

