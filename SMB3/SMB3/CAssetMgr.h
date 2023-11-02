#pragma once

class CTexture;
class CSound;

class CAssetMgr
{
	SINGLETON(CAssetMgr);
private:
	map<wstring, CTexture*>	m_mapTex;
	map<wstring, CSound*>	m_mapSound;

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* CreateTexture(const wstring& _strKey, UINT _width, UINT _height);
	CTexture* FindTexture(const wstring& _strKey);

	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);	
	CSound* FindSound(const wstring& _strKey);

};