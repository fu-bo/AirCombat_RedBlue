
#ifndef COLOROBJ_HPP
#define COLOROBJ_HPP

#include "Colored.hpp"

class ColorObj: public Colored{
protected:
    double shape_x_[MAX_SHAPE_NUM];
    double shape_y_[MAX_SHAPE_NUM];
    double shape_rho_[MAX_SHAPE_NUM];
    int shape_n_; // for shape x and y
    double shape_agl_res_; // shape_agl_res_ * shape_m_ = 360;
    int shape_m_; // for shape angle and rho
    
    double shape_y_min_;
    double shape_y_range_;
    int shape_y_min_ind_;
    
public:
    ColorObj();
    ~ColorObj();
    
    bool setColorObj(double x, double y, int state, int color, double hp_max, int shape_n, int shape_agl_res, double* shape_x, double* shape_y);
    double interpRho(double* x_array, double* y_array, int n, double x);
    double getRho(double agl);
    void show();
    int scanY(double hp_y, double* hp_x, int* index_up_out, int* index_down_out);
    void showColoredDown();
    void showColoredUp();
    void showFull(bool flag_white = false);
    void showLine(bool flag_loop = true);
    void showRho();
    void moveRandom(double dt, int random_type = 0);
    void moveUp(double dt, bool flag_up);
    void moveRight(double dt, bool flag_right);
    
    void randomShape();
    virtual int move(double dt);
};

#endif // COLOROBJ_HPP
