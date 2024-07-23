#include "WeaponNodeItem.h"

WeaponNodeItem::WeaponNodeItem(std::string path)
{
	texture = TextureController(path);
}

void WeaponNodeItem::drawIcon(Rectangle pos, bool onlyIcon, Color color)
{
	texture.draw(pos, false, false, 0, { 0.0f,0.0f }, 0.0f, color);
}