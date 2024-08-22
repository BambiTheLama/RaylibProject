#include "GameObject.h"
#include "Collider/Collider.h"
Rectangle GameObject::getColPos()
{
    Collider* col = dynamic_cast<Collider*>(this);
    if (!col)
        return getPos();
    return col->getCollisionArea();
}
