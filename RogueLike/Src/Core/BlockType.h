#pragma once
#include "raylib.hpp"

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

bool isWallType(BlockType tpye);

Color getColorFromType(int i);

Color getColorFromType(BlockType type);

BlockType getRoomFromColor(Color c);

int getRoomElementFromColor(Color c);

BlockType getRoomElementType(int ID);

int getRoomElementID(BlockType type);