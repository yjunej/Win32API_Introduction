#pragma once

#define SINGLE(type) public:\
							static type* GetInstance()\
							{\
								static type mgr;\
								return &mgr;\
							}\
			     	private:\
							type();\
							~type();\
							type(const type&) = delete;\
							type& operator=(const type&) = delete;

# define fDT CTimeMgr::GetInstance()->GetfDT()
# define DT CTimeMgr::GetInstance()->GetfDT()

enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MISSILE,
	ENEMY,

	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};