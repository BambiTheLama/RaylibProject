#include "StandardEnemy.h"
#include "../Collider/CollisionElementCircle.h"
#include "../Collider/CollisionElementLines.h"
#include "raymath.h"
#include "../Game.h"
#include "../Particle/ParticleText.h"
#include <magic_enum/magic_enum.hpp>
#include "../Projectal/ProjectalFactory.h"
#include "../Items/ItemFactory.h"
#include "../Particle/TextureDestroyParticleSystem.h"

static float hpBarSize = 100;

StandardEnemy::StandardEnemy(std::string type, nlohmann::json data, int level)
{
	setMaxHp(10);
	pos = { 0,0,64.0f,64.0f };
	//addCollisionElement(new CollisionElementCircle({ pos.width / 2,pos.height / 2 }, pos.height / 4));
	//addCollisionElement(new CollisionElementLines({ pos.width / 3+4,pos.height / 3 + 10,pos.width / 3-8,pos.height / 3 }));
	this->type = ObjectType::Enemy;
	ai = new AIController();
	ai->thisObj = this;
	ai->targerType = (int)ObjectType::Player;
	ai->action = Action::GoTo;
	ai->range = 300;
	controller.setController(ai);
	controller.setCharacter(this);
	controller.setCharacterType(ObjectType::Enemy);
	mass = 10;
	//trigger = true;
	texture = TextureController("Enemies/Skeletron.png");
	readData(type, data, level);
}

StandardEnemy::~StandardEnemy()
{

}

void StandardEnemy::start()
{
	particleActivated = false;
}

void StandardEnemy::destroy()
{
	if (!Game::isGameScene())
		return;

	if (!particleActivated)
	{
		int frame = texture.getFrame(animationName, frameTimer / timePerFrame);
		Game::addObject(new TextureDestroyParticleSystem(texture, 0, getPos()));
		particleActivated = true;
	}

	if (!weapon)
		return;
	weapon->destory();

	GameObject* gm = dynamic_cast<GameObject*>(weapon);
	if (gm)
		Game::deleteObject(gm);
	weapon = nullptr;

}

void StandardEnemy::update(float deltaTime)
{
	frameTimer += deltaTime;
	if (item)
		item->update(deltaTime, attackDir);
	Hitable::update(deltaTime);
	
	controller.update(deltaTime);
	if (!ai)
		return;

	Rectangle pos = getPos();
	if (target != 0 && ai->target)
	{

		Vector2 posV = getMidlePoint(pos);
		Vector2 otherPosV = getMidlePoint(ai->target->getPos());
		attackDir = Vector2Subtract(otherPosV, posV);
		float distance = Vector2Length(attackDir);
		attackDir = Vector2Normalize(attackDir);
		bool canSwap = true;
		bool chargeWeapon = false;
		if (item)
			canSwap = item->canSwap();
		if (weapon)
			chargeWeapon = weapon->isChargeWeapon();
		if (chargeWeapon)
			canSwap = true;
		if (distance > maxRangeAttack && canSwap)
			ai->setAction(Action::GoTo);
		else if (distance < minRangeAttack && canSwap)
			ai->setAction(Action::RunFrom);		
		else if (distance < maxRangeAttack && distance > minRangeAttack)
			ai->setAction(Action::Attack);
		else 
			ai->setAction(Action::IDE);
	}
	else if(!ai->hasPath())
	{
		ai->lookForTarget();
		ai->setAction(Action::IDE);
	}
	std::string actionName = ai->getActionName();
	if (actionName.compare(animationName))
	{
		frameTimer = 0.0f;
		animationName = actionName;
	}
}

void StandardEnemy::draw()
{
	//DrawRectangleRec(pos, { 255,255,0,69 });
	//DrawRectangleRec(pos, col ?RED: LIGHTGRAY);
	int frame = texture.getFrame(animationName, frameTimer / timePerFrame);
		
	texture.draw(pos, false, false, frame);
	//Hitable::draw({ pos.x + pos.width / 2 - hpBarSize / 2,pos.y - 30,hpBarSize,20 });
	GameObject* gm = dynamic_cast<GameObject*>(weapon);
	if (gm)
		gm->draw();
	//Color c = GREEN;
	//c.a = 20;
	//DrawRectangleRec(RectangleIncreasSize(pos, ai->range), c);

}

void StandardEnemy::action(Input input, Vector2 movedir, Vector2 cursorDir, float deltaTime)
{

	if (input == Input::Attack && weapon)
	{
		GameObject* gm = dynamic_cast<GameObject*>(weapon);
		Item* item = dynamic_cast<Item*>(weapon);
		if (weapon)
			weapon->setTarget(target);
		if (item)
			item->setOwner(this);
		Game::addObject(gm);
		weapon->use(cursorDir, deltaTime);
		if (weapon->stopUseWeapon())
			weapon->stopUse(cursorDir, deltaTime);
	}
	attackDir = cursorDir;

}

void StandardEnemy::onCollision(Collider* collider)
{
	GameObject* gm = collider->getThisObj();
	if (((int)gm->getType() & target) != 0) {
		Hitable* hit = dynamic_cast<Hitable*>(gm);
		if (hit)
		{
			hit->dealDamage(contactDamage, 0.2f);
		}
	}

}

void StandardEnemy::destoryController()
{
	controller.destoryController();
	ai = nullptr;
}

void StandardEnemy::onHit()
{

}

void StandardEnemy::readData(std::string type, nlohmann::json data, int level)
{
	if (!data.contains(type))
		return;
	if (data[type].contains("Size"))
	{
		pos.width = data[type]["Size"][0];
		pos.height = data[type]["Size"][1];
	}
	if (data[type].contains("Texture"))
		texture = TextureController(data[type]["Texture"]);

	if (data[type].contains("Col"))
	{
		std::vector<Vector2> col;
		
		for (int i = 0; i < data[type]["Col"].size(); i++)
		{
			int x = data[type]["Col"][i][0];
			int y = data[type]["Col"][i][1];
			col.push_back({ (float)x,(float)y });
		}
		addCollisionElement(new CollisionElementLines(col));
	}
	if (data[type].contains("Mass"))
		mass = data[type]["Mass"];
	if (data[type].contains("Range"))
		ai->range = data[type]["Range"];

	if (data[type].contains("MinDist"))
		minRangeAttack = data[type]["MinDist"];
	if (data[type].contains("MaxDist"))
		maxRangeAttack = data[type]["MaxDist"];
	if (data[type].contains("ContactDamage"))
		contactDamage = data[type]["ContactDamage"];
	if (data[type].contains("SpawnPoint"))
	{
		spawnPoint.x = data[type]["SpawnPoint"][0];
		spawnPoint.y = data[type]["SpawnPoint"][1];
	}
	if (data[type].contains("Scale"))
	{
		float scale = data[type]["Scale"];

		Collider::scaleColliderElements(scale);
		pos.width *= scale;
		pos.height *= scale;
		spawnPoint = Vector2Scale(spawnPoint, scale);
	}
	if (data[type].contains("Weapon"))
	{
		int tier = 0;
		int variant = 0;
		WeaponType weaponType = WeaponType::Sword;
		if (data[type]["Weapon"].contains("Tier"))
			tier = data[type]["Weapon"]["Tier"];
		if (data[type]["Weapon"].contains("Variant"))
			variant = data[type]["Weapon"]["Variant"];
		if (data[type]["Weapon"].contains("Type"))
		{
			std::string name = data[type]["Weapon"]["Type"];
			auto castName = magic_enum::enum_cast<WeaponType>(name);
			if (castName.has_value())
				weaponType = castName.value();
		}

		weapon = getWeapon(variant, tier, weaponType);
		if (weapon)
		{
			item = dynamic_cast<Item*>(weapon);
			GameObject* gm = dynamic_cast<GameObject*>(weapon);

			if (item)
				item->setOwner(this);
			Game::addObject(gm);
			weapon->use({ 0,0 }, 0);
			if (item)
				item->update(1000);

		}


	}
}
