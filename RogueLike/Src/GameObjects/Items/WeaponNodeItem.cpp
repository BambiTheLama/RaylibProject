#include "WeaponNodeItem.h"

WeaponNodeItem::WeaponNodeItem(std::string path)
{
	texture = TextureController(path);
	pos = { 0,0,64,64 };
}

void WeaponNodeItem::draw()
{
	if (isClosestObject)
	{
		const float moveBy = 3.0f;
		startOutLineShader();
		drawIcon(moveRectangeBy(pos, { moveBy,0 }));
		drawIcon(moveRectangeBy(pos, { -moveBy,0 }));
		drawIcon(moveRectangeBy(pos, { 0,-moveBy }));
		drawIcon(moveRectangeBy(pos, { 0,moveBy }));
		EndShaderMode();
	}

	drawIcon(pos);
	
}

void WeaponNodeItem::drawIcon(Rectangle pos, bool onlyIcon, Color color)
{
	texture.draw(pos, false, false, 0, { 0.0f,0.0f }, 0.0f, color);
}