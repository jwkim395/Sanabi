#pragma once

struct mapData {
	vector<CObj*> tileData;
	Vec2 vLeft;
	Vec2 vBottomRight;
	~mapData() {
		for (int i = 0; i < tileData.size(); ++i) {
			delete tileData[i];
		}
	}
};

class CLevelMgr
{
	SINGLETON(CLevelMgr);
private:
	class CLevel*	m_pCurLevel;
	CLevel*			m_arrLevels[(UINT)LEVEL_TYPE::END];
	class CImageUI* selectedTile;
	mapData*		curMap;

public:
	CLevel* GetCurLevel() { return m_pCurLevel; }
	CImageUI* GetTile() { return selectedTile; }
	void SetTile(CImageUI* _ui) { selectedTile = _ui; }
	void SetMapData(vector<CObj*> _tileData, Vec2 _left, Vec2 _botRight) { 
		curMap = new mapData;
		curMap->tileData = _tileData;
		curMap->vLeft = _left;
		curMap->vBottomRight = _botRight;
	}
	mapData* getMapData() { return curMap; }

private:
	void ChangeLevel(LEVEL_TYPE _Type);

public:
	void init();
	void tick();
	void render(HDC _dc);

	friend class CTaskMgr;
};

