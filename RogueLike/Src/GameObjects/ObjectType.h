#pragma once

enum class ObjectType :int
{
    NON = 0b0,
    Enemy = 0b1,
    Player = 0b10,
    Wall = 0b100,
    SpawnPoint = 0b1000,
    Loot = 0b10000,

};