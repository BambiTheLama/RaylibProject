#include "ShopKeeper.h"
#include "../Collider/CollisionElementCircle.h"
#include "../Collider/CollisionElementLines.h"
#include "../Elements/Torch.h"
#include "../Game.h"
#include "../Items/ItemFactory.h"

extern const float tileW;
extern const float tileH;

ShopKeeper::ShopKeeper(Rectangle pos)
{
	pos = changeRecntalgeSize(pos, pos.width * 3, pos.height * 3);
	this->pos = pos;
	addCollisionElement(new CollisionElementLines({pos.width/3,pos.height/3,pos.width/3,pos.height/3}));
	setMaxHp(100);
	mass = 10000;
	texture = TextureController("NPC/ShopKeeper.png");
}

ShopKeeper::~ShopKeeper()
{
}

void ShopKeeper::start()
{
	Rectangle itemPos = { pos.x - tileW * 2,pos.y + pos.height,tileW * 2,tileH * 2 };
	int seed = 1000;
	int tier = 0;
	for (int i = 0; i < 3; i++)
	{
		Item* item = getWeaponNode(getRandom(seed, 0, getWeaponNodeSize(tier)), tier);
		ShopItem* shopItem = new ShopItem(itemPos, item);
		shopItem->setShopSkeeper(this);
		shopItem->setPrice(getRandom(seed, 1, 10));
		Game::addObject(shopItem);
		itemPos.x += tileW * 2.5f;
	}
}

void ShopKeeper::destroy()
{
	if (!Game::isGameScene())
		return;
	for (auto i : items)
		i->setPrice(0);
}

void ShopKeeper::update(float deltaTime)
{
	timer += deltaTime;
	Collider::update(deltaTime);
	Hitable::update(deltaTime);
}

void ShopKeeper::draw()
{
	float diff = sin(timer * 8) * 5;
	Rectangle pos = getPos();
	pos = changeRecntalgeSize(pos, pos.width + diff, pos.height - diff);
	texture.draw(pos, false, false, 0, { 0,0 }, 0.0f, WHITE);

}

void ShopKeeper::removeItem(ShopItem* item)
{
	items.remove(item);
}

