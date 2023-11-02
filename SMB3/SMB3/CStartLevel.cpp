#include "pch.h"
#include "CStartLevel.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"

void CStartLevel::init()
{
}

void CStartLevel::enter()
{
}

void CStartLevel::exit()
{
	DeleteAllObjects();
}

void CStartLevel::tick()
{
	CLevel::tick();

	// Enter 키가 눌리면 PlayLevel 로 전환
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
	}
}
