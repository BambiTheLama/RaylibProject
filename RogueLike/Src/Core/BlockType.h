#pragma once
enum class BlockType :char
{
	NON = 0, 
	Wall,
	BossWall,
	PlayerSpawnPoint,
	ChestSpawnPoint,
	EnemySpawnPoint,
	LootSpawnPoint,
	BossSpawnPoint,
	BossEnterWall,
	ElitEnemySpawn
};