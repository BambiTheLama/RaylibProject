//
// Created by Szymek on 14.05.2024.
//

#ifndef SCENE_H
#define SCENE_H



class Scene {
public:
    virtual void start() = 0;

    virtual void update(float deltaTime) = 0;

    virtual void draw() = 0;
};



#endif //SCENE_H
