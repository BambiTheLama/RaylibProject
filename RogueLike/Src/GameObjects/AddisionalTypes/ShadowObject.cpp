#include "ShadowObject.h"
#include "../GameObject.h"

Rectangle ShadowObject::getShadowPos()
{
    GameObject* gm = dynamic_cast<GameObject*>(this);
    if(!gm)
        return Rectangle();
    return gm->getPos();
}
