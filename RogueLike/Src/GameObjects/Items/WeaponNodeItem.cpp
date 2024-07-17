#include "WeaponNodeItem.h"

WeaponNodeItem::WeaponNodeItem(std::string path)
{
	texture = TextureController(path);
}

void WeaponNodeItem::drawIcon(Rectangle pos, bool onlyIcon)
{
	texture.draw(pos);
}