#pragma once

class CEnemy;

enum class ENEMY_TYPE
{
	NORMAL,
	BOSS
};

class CEnemySpawner
{

public:
	static CEnemy* SpawnEnemy(ENEMY_TYPE _eType, Vec2 _vPos);

private:
	CEnemySpawner();
	~CEnemySpawner();
};

