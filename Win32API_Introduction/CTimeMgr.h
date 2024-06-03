#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	LARGE_INTEGER m_llPrevCount; // union
	LARGE_INTEGER m_llCurCount; // union
	LARGE_INTEGER m_llFrequency;

	// Delta Time - Time interval between Frames
	double m_dDT;
	double m_dTT; // Total Time

	UINT m_iCallCount;
	UINT m_iFPS;
	

	// FPS - Frame Per Sec
public:
	void Init();
	void Update();

public:
	double GetDT() const { return m_dDT; }
	float GetfDT() const { return (float)m_dDT; }
};

