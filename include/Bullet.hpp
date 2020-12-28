#ifndef BULLET_HPP
#define BULLET_HPP

#include "ColorCircle.hpp"

class Bullet: public ColorCircle{
protected:
    int type_;
public:
    bool shoot(double x, double y, int type = 0);
    int move(double dt);
};

#endif // BULLET_HPP