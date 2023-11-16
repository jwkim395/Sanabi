#include "pch.h"
#include "CLevelMgr.h"

#include "CEngine.h"
#include "CCamera.h"
#include "CLogMgr.h"
#include "CCollisionMgr.h"

#include "CLevel.h"
#include "CPlayLevel.h"
#include "CStartLevel.h"
#include "CEditorLevel.h"


#include "CMario.h"
#include "CMonster.h"
#include "CPlatform.h"
#include "CTimeMgr.h"

CLevelMgr::CLevelMgr()
	: m_pCurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		if (nullptr != m_arrLevels[i])
			delete m_arrLevels[i];
	}
}


void CLevelMgr::init()
{
	// 모든 레벨 생성
	m_arrLevels[(UINT)LEVEL_TYPE::START_LEVEL] = new CStartLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::PLAY_LEVEL] = new CPlayLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::EDITOR_LEVEL] = new CEditorLevel;

	// 레벨 초기화
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		m_arrLevels[i]->init();
	}

	// Level
	::ChangeLevel(LEVEL_TYPE::EDITOR_LEVEL);
	selectedTile = nullptr;
	curMap = nullptr;
	mTime = 0.f;
}

void CLevelMgr::tick()
{
	if (nullptr != m_pCurLevel) {
		m_pCurLevel->tick();
	}
	if (mTime > 0.f) {
		mTime -= DT;
	}
}

void CLevelMgr::render(HDC _dc)
{
	if (nullptr == m_pCurLevel)
		return;

	// Level Render
	// 화면 Clear
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	Rectangle(_dc, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	// editor level일 경우 64 * 64 격자 생성
	if (dynamic_cast<CEditorLevel*>(m_pCurLevel)) {
		for (int i = 0; i < ptResolution.x / 64; ++i) {
			MoveToEx(_dc, i * 64, 0, nullptr);
			LineTo(_dc, i * 64, ptResolution.y);
			
		}
		for (int i = 0; i < ptResolution.y / 64; ++i) {
			MoveToEx(_dc, 0, i * 64, nullptr);
			LineTo(_dc, ptResolution.x, i * 64);
		}
		
	}
	

	// 레벨 render
	m_pCurLevel->render(_dc);

	// Log
	CLogMgr::GetInst()->tick(_dc);
}


void CLevelMgr::ChangeLevel(LEVEL_TYPE _Type)
{
	if (m_pCurLevel == m_arrLevels[(UINT)_Type])
		return;

	if(nullptr != m_pCurLevel)
		m_pCurLevel->exit();

	m_pCurLevel = m_arrLevels[(UINT)_Type];

	m_pCurLevel->enter();

	m_pCurLevel->begin();
}