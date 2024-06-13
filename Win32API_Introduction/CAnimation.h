#pragma once

#include "global.h"

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2 vLT;
	Vec2 vSlice;
	Vec2 vOffset;
	float fDuration;
};

class CAnimation
{
private:
	wstring m_strName;
	CAnimator* m_pAnimator;
	CTexture* m_pTex; // Texture for Animation
	vector<tAnimFrm> m_vecFrm; // All Frames Info
	int m_iCurFrm; // Current Frame
	float m_fAccTime; // Accumulated Time

	bool m_bFinish;

public:
	void Update();
	void Render(HDC _hdc);

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	void Save(const wstring& _strRelPath);
	void Load(const wstring& _strRelPath);

	bool IsFinish() const { return m_bFinish; }
	const wstring& GetName() const { return m_strName; }
	void SetCurFrame(int _i)
	{ 
		m_bFinish = false; 
		m_iCurFrm = _i;
		m_fAccTime = 0.f;
	}
	void ResetAnim() { m_bFinish = false; m_iCurFrm= 0; }
	int GetCurFrame() const { return m_iCurFrm; }
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }




public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

