#pragma once
#include "../GameObject.h"
#include "../Collider/Collider.h"
#include "../AddisionalTypes/Interactive.h"

class Chest :
    public GameObject , public Collider, public Interactive
{
public:
    Chest(Rectangle pos, int tier);

    void draw();

    void draw(Rectangle pos);

    void interact(GameObject* interactObj);
};

