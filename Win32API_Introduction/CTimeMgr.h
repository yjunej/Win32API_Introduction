#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	LARGE_INTEGER m_llCurCount; // union
	LARGE_INTEGER m_llFrequency;

	// FPS - Frame Per Sec
	// Delta Time - Time interval between Frames
public:
	void Init();

};

