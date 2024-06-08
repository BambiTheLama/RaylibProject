#include "CollisionElementBox.h"
#include "../../Core/WaveCollapsFun.h"
CollisionElementBox::CollisionElementBox(Rectangle col) : CollisionElement(CollisionType::Box) {
    this->col = col;
}

bool CollisionElementBox::isCollidiongWith(Vector2 thisPos, CollisionElement *collisionElement,
                                           Vector2 collisionElementPos) {
    Rectangle thisBox = getBox(thisPos);
    if (collisionElement->getType() == CollisionType::Box) {
        Rectangle otherBox = collisionElement->getBox(collisionElementPos);
        return CheckCollisionRecs(thisBox, otherBox);
    }
    if (collisionElement->getType() == CollisionType::Line) {
        std::vector<Vector2> lines = collisionElement->getLines(collisionElementPos);
        for (int i = 0; i < lines.size() - 1; i++) {
            if (CheckCollisionRecLine(thisBox, lines[i], lines[i + 1]))
                return true;
        }
        if (CheckCollisionRecLine(thisBox, lines[0], lines[lines.size() - 1]))
            return true;
        return false;
    }
    if (collisionElement->getType() == CollisionType::Circle) {
        Vector3 circle = collisionElement->getCircle(collisionElementPos);
        return CheckCollisionCircleRec({circle.x, circle.y}, circle.z, thisBox);
    }
    return false;
}

Dir CollisionElementBox::getCollisionDir(Vector2 thisPos, CollisionElement* collisionElement, Vector2 collisionElementPos)
{
    Rectangle thisBox = getBox(thisPos);
    if (collisionElement->getType() == CollisionType::Box) {
        Rectangle otherBox = collisionElement->getBox(collisionElementPos);
        if(!CheckCollisionRecs(thisBox, otherBox))
            return Dir::NON;
        Rectangle col = GetCollisionRec(thisBox, otherBox);
        if (col.width > col.height)
        {
            if (thisPos.y - collisionElementPos.y > 0)
                return Dir::Down;
            return Dir::Up;
        }
        if (thisPos.x - collisionElementPos.x > 0)
            return Dir::Right;
        return Dir::Left;
        
    }
    if (collisionElement->getType() == CollisionType::Line) {
        std::vector<Vector2> lines = collisionElement->getLines(collisionElementPos);
        for (int i = 0; i < lines.size() - 1; i++) {
            {
                Dir d = CheckCollisionRecLineDir(thisBox, lines[i], lines[i + 1]);
                if (d != Dir::NON)
                    return d;
            }

        }
        return CheckCollisionRecLineDir(thisBox, lines[0], lines[lines.size() - 1]);
    }

    return Dir::NON;
}
