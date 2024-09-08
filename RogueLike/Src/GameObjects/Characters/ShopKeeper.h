#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/Hitable.h"
#include "../Collider/Collider.h"
class ShopKeeper
	:public GameObject,public Hitable,public Collider
{
	TextureController texture;
public:
	ShopKeeper(Rectangle pos);

	~ShopKeeper();

	void start() override;

	void destroy() override;

	void update(float deltaTime)override;

	void draw() override;
};

