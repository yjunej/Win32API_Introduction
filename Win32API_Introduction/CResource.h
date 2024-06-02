#pragma once

class CResource
{
private:
	wstring m_strKey;
	wstring m_strRelPath;

public:
	void SetKey(const wstring& _str) { m_strKey = _str; }
	void SetRelPath(const wstring& _str) { m_strRelPath = _str; }

	const wstring& GetKey() const { return m_strKey; }
	const wstring& GetRelPath() const { return m_strRelPath; }

public:
	CResource();
	~CResource();
		
};

