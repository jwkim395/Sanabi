#pragma once


class CLogMgr
{
	SINGLETON(CLogMgr)
private:
	list<FLog>	m_LogList;

	float		m_LogMaxLife;

public:
	void SetLogMaxLife(float _Life) { m_LogMaxLife = _Life; }

	void AddLog(const FLog& _log) {	m_LogList.push_front(_log); }

public:
	void tick(HDC _dc);
};

#define LOG(Level, Message)		{\
									string funcname = __FUNCTION__; \
									wchar_t szBuffer[100] = {};\
									swprintf_s(szBuffer, L"Function : %s  {Line : %d } : %s"\
										, wstring(funcname.begin(), funcname.end()).c_str(), __LINE__\
										, Message);\
									CLogMgr::GetInst()->AddLog(FLog{ Level, szBuffer });\
								}

