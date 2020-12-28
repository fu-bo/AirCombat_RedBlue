
#ifndef COLORCIRCLE_HPP
#define COLORCIRCLE_HPP

#include "Colored.hpp"

class ColorCircle: public Colored{
protected:
    double r_;
    int shape_n_;
    
public:
    ColorCircle(){}
    ~ColorCircle(){}
    bool setColorCircle(double x, double y, int state, int color, double hp_max, double r, int shape_n);
    double getRho(double agl = 0.0);
    void showFull(bool flag_white = false);
    void showLine();
    void showUp();
    void show();
    bool setShape(double r, int shape_n, double hp_max = -1);
};

#endif // COLORCIRCLE_HPP
