//
// Created by Szymek on 14.05.2024.
//

#ifndef ENGINE_H
#define ENGINE_H
#include "Scene.h"


class Engine {
    Scene *s;

public:
    Engine();

    void setScene(Scene *s);
};


#endif //ENGINE_H
