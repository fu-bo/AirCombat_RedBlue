

#ifndef COLORQUAD_HPP
#define COLORQUAD_HPP

#include "Colored.hpp"

class ColorQuad: public Colored{
protected:
    double a_;
    double b_;
    double r_;
public:
    ColorQuad(){};
    ~ColorQuad(){};
    bool setColorQuad(double x, double y, int state, int color, double hp_max, double a, double b);
    double getRho(double agl = 0.0);
    void show();
    void showFull(bool flag_white = false);
    void showUp();
    void showLine();
};

#endif // COLORQUAD_HPP
