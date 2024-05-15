//
// Created by szymek on 15.05.2024.
//

#ifndef MYPROJECT_HITABLE_H
#define MYPROJECT_HITABLE_H


class Hitable {
public:
    virtual void dealDamage(float damage) = 0;
};


#endif //MYPROJECT_HITABLE_H
