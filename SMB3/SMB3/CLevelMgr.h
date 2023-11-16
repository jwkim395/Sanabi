#pragma once

class CObj;

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
	float mTime;
	int marioStatus; // 1: »ì¾ÆÀÕÀ½, 2: powerUp/down, 3: Á×À½, 4: clear

public:
	void setmTime(float t) { mTime = t; }
	float getmTime() { return mTime; }
	int getMarioStatus() { return marioStatus; }
	void setMarioStatus(int status) { marioStatus = status; }
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
	void clearMapData() {
		for (int i = 0; i < curMap->tileData.size(); ++i) {
			delete curMap->tileData[i];
		}
		curMap->tileData.clear();
		delete curMap;
		curMap = nullptr;
	}
	

private:
	void ChangeLevel(LEVEL_TYPE _Type);

public:
	void init();
	void tick();
	void render(HDC _dc);

	friend class CTaskMgr;
};

