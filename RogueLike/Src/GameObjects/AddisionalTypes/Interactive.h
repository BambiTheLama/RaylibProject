#pragma once
class GameObject;
class Interactive
{
protected:
	bool isClosestObject = false;
public:
	virtual void interact(GameObject* interactObject) = 0;

	void setIsClosesObject(bool closest);
};

