#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Collider/Collider.h"
#include "../Elements/ShopItem.h"

class ShopKeeper
	:public GameObject,public Hitable,public Collider
{
	TextureController texture;
	std::list<ShopItem*> items;
	float timer = 0.0f;
	static int seed;
public:
	ShopKeeper(Rectangle pos);

	~ShopKeeper();

	void start() override;

	void destroy() override;

	void update(float deltaTime)override;

	void draw() override;

	void removeItem(ShopItem* item);

	static void setSeed(int seed) { ShopKeeper::seed = seed; }
};

