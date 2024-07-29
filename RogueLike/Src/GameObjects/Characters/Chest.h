#pragma once
#include "../GameObject.h"
#include "../Collider/Collider.h"

class Chest :
    public GameObject , public Collider
{
public:
    Chest(Rectangle pos, int tier);



};

