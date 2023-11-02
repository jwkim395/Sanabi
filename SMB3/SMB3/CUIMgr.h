#pragma once


class CUI;

class CUIMgr
{
	SINGLETON(CUIMgr);
private:
	CUI*	m_FocuedUI;	// 최상위 부모 UI 중에서 포커싱 되어있는 UI

public:
	void tick();	

private:
	CUI* GetPriorityCheck(CUI* _ParentUI);

};

