#pragma once
#include "CComponent.h"

class CAnim;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    // Animator 가 보유하고 있는 Animation 목록, 탐색을 위해서 Map 으로 
    map<wstring, CAnim*> m_mapAnim;

    // 현재 재생중인 Animation
    CAnim*               m_CurAnim;

    // 반복 재생 여부
    bool                 m_bRepeat;

public:
    void Play(const wstring& _strName, bool _bRepeat);
    void Stop();


    // Animation 찾기
    CAnim* FindAnim(const wstring& _strName);

    // 애니메이션 생성
    void CreateAnimation(const wstring& _strName, CTexture* _Altas, Vec2 _vLeftTop, Vec2 _vCutSize
                        , Vec2 _vOffset, float _duration, int _MaxFrm);

    void SaveAnimations(const wstring& _strRelativePath);
    void LoadAnimation(const wstring& _strRelativePath);
    


public:
    virtual void finaltick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CAnimator);
    CAnimator(CObj* _Owner);
    CAnimator(const CAnimator& _Origin);
    ~CAnimator();
};

