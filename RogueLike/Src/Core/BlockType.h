#pragma once
enum class BlockType :char
{
	NON = 0, Wall,
	PlayerSpawnPoint,
	ChestSpawnPoint,
	EnemySpawnPoint,
	LootSpawnPoint,
	BossSpawnPoint,
	BossEnterWall,
	ElitEnemySpawn
};