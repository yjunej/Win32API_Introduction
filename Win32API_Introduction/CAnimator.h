#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*> m_mapAnim; // Entire Animation
	CAnimation* m_pCurAnim; // Current Animation

	CObject* m_pOwner;
	bool m_bLoop; // Loop Animation

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex,  Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void LoadAnimation(const wstring& _strRelPath);
	void Play(const wstring& _strName, bool bLoop);

	void Update();
	void PostUpdate();
	void Render(HDC _hdc);

	CObject* GetOwner() const { return m_pOwner; }

public:
	CAnimator();
	~CAnimator();

	friend class CObject;

};

