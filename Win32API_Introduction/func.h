#pragma once

class CObject;

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eScene);

template<typename T>
void DeleteVectorSafe(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (nullptr != _vec[i])
		{
			delete _vec[i];
		}
		_vec.clear();
	}
}

template<typename T, typename U>
void DeleteMapSafe(map<T, U>& _map)
{
	typename map<T, U>::iterator iter = _map.begin();
	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
		}
	}
	_map.clear();
}
