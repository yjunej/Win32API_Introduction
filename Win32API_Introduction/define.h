#pragma once

#define SINGLE(type) static type* GetInstance()\
									{\
									static type mgr;\
									return &mgr;\
									}