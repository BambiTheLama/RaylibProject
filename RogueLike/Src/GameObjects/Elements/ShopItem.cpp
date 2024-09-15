#include "ShopItem.h"
#include "../Characters/ShopKeeper.h"
#include "../Characters/Player.h"
#include "../Game.h"

ShopItem::ShopItem(Rectangle pos, Item* item)
{
	this->pos = pos;
	this->item = item;
	buySound = SoundController("Buy.mp3");
	cancelSound = SoundController("Cancel.mp3");
}

ShopItem::~ShopItem()
{
	if (item)
		delete item;
}

void ShopItem::interact(GameObject* interactObject)
{
	Player* p = dynamic_cast<Player*>(interactObject);
	if (!p)
		return;
	if (!p->removeCoins(price))
	{
		cancelSound.play();
		return;
	}

	if (shopKeeper)
		shopKeeper->removeItem(this);
	GameObject* itemGm = dynamic_cast<GameObject*>(item);
	if (itemGm)
	{
		itemGm->setPos({ pos.x,pos.y });
		Game::addObject(itemGm);
	}
	else
	{
		delete item;
	}
	buySound.play();
	item = nullptr;
	Game::deleteObject(this);

}

void ShopItem::start()
{
}

void ShopItem::draw()
{
	Rectangle pos = getPos();
	if (isClosestObject)
	{
		startOutLineShader();
		const float lineSize = pos.width / 32.0f;
		draw(moveRectangeBy(pos, { 0,lineSize }), WHITE);
		draw(moveRectangeBy(pos, { 0,-lineSize }), WHITE);
		draw(moveRectangeBy(pos, { lineSize ,0 }), WHITE);
		draw(moveRectangeBy(pos, { -lineSize,0 }), WHITE);
		EndShaderMode();
	}
	draw(pos, WHITE);
	std::string text = "{Icon:11}" + std::to_string(price);
	float fontSize = 32;
	float textSize = MyFont::TextSize(text.c_str(), fontSize, 0.0f).x;
	float x = pos.x + (pos.width - textSize) / 2;
	MyFont::DrawTextWithOutline(text.c_str(), x, pos.y + pos.height, fontSize, ORANGE, BLACK, { 0.0 }, 0, 1.0f);
}

void ShopItem::draw(Rectangle pos, Color c)
{
	if (item)
		item->drawIcon(pos, true, c);
}

void ShopItem::setShopSkeeper(ShopKeeper* shopKeeper)
{
	this->shopKeeper = shopKeeper;
}
