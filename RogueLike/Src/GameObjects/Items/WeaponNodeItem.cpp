#include "WeaponNodeItem.h"
#include "../Collider/CollisionElementLines.h"

#pragma region Constructor
WeaponNodeItem::WeaponNodeItem()
{
	addCollisionElement(new CollisionElementLines(RectangleDecreasSize(pos, 20)));
	setOwner(nullptr);
}

WeaponNodeItem::WeaponNodeItem(std::string path) :WeaponNodeItem()
{
	texture = TextureController(path);
}

WeaponNodeItem::WeaponNodeItem(nlohmann::json j) :WeaponNodeItem()
{
	if (j.contains("Texture"))
		texture = TextureController(j["Texture"]);
	node = WeaponNode(j);
	printf(node.getStats().toString(true).c_str());
	printf("KURWA KURWA KURWA KURWA KURWA KURWA KURWA KUWA \n");
}
#pragma endregion Constructor

void WeaponNodeItem::update(float deltaTime)
{
	if (owner)
	{
		Vector2 p = getMidlePoint(owner->getPos());
		pos.x = p.x;
		pos.y = p.y;
	}
}

#pragma region DrawFun
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
#pragma endregion DrawFun

void WeaponNodeItem::setOwner(GameObject* owner)
{
	Item::setOwner(owner);
	trigger = owner;
}