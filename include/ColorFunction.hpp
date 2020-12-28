#ifndef COLORFUNCTION_HPP
#define COLORFUNCTION_HPP

#include "Colored.hpp"
class ColorObj;
class ColorCircle;
class ColorQuad;
class Bullet;

class ColorFunction: public Colored{
public:
    static bool checkCollision(ColorObj* clr1, ColorObj* clr2);
    static bool checkCollision(ColorObj* clr1, ColorCircle* clr2);
    static bool checkCollision(ColorObj* clr1, ColorQuad* clr2);
    static bool checkCollision(ColorCircle* clr1, ColorCircle* clr2);
    static bool checkCollision(ColorQuad* clr1, ColorCircle* clr2);
    static bool checkCollision(ColorQuad* clr1, ColorQuad* clr2);
    static void setPlane(int plane_id, ColorObj* clr);
    static bool fire(Colored* c, Bullet** bullet, int bullet_num, double x, double y, double vx, double vy, int fire_type = 0, int shoot_max = 16);
    static void showLife(int count_life, int count_large, int max_life, int max_large, ColorObj** life, ColorCircle** large);  
};

#endif // COLORFUNCTION_HPP