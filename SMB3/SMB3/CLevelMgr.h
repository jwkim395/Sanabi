#pragma once


class CLevelMgr
{
	SINGLETON(CLevelMgr);
private:
	class CLevel*	m_pCurLevel;
	CLevel*			m_arrLevels[(UINT)LEVEL_TYPE::END];
	class CImageUI* selectedTile;

public:
	CLevel* GetCurLevel() { return m_pCurLevel; }
	CImageUI* GetTile() { return selectedTile; }
	void SetTile(CImageUI* _ui) { selectedTile = _ui; }

private:
	void ChangeLevel(LEVEL_TYPE _Type);

public:
	void init();
	void tick();
	void render(HDC _dc);

	friend class CTaskMgr;
};

