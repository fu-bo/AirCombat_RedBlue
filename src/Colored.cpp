#include "Colored.hpp"
#include "Common.hpp"
#include "fssimplewindow.h"
#include <math.h>
#include <stdio.h>

Colored::Colored(){
    setRGB(101, line_rgb_); //black
}

Colored::~Colored(){}


//static
void Colored::swap(double &a, double &b)
{
    double temp = a;
    a = b;
    b = temp;
}

//static
void Colored::swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

//static
double Colored::myRand(double min_value, double max_value)
{
    double rand_value = ( ((double)(therand() % 32768)) / 32767) * (max_value - min_value) + min_value;
    return rand_value;
}

//static
void Colored::bubbleSort(int n, double x[], int index[]){
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(x[i] > x[j])
            {
                swap(x[i], x[j]);
                swap(index[i], index[j]);
            }
        }
        
    }
}

bool Colored::setColored(double x, double y, int state, int color, double hp_max){
    x_ = x;
    y_ = y;
    state_ = state;
    color_ = color;
    setRGB(color, rgb_);
    line_width_ = 3;
    hp_max_ = hp_max;
    hp_ = hp_max;
    vx_ = 0.0;
    vy_ = 0.0;
    v_ = 20.0;
    shape_scale_ = 1.0;
    flag_enable_blend_ = false;
    time_prev_ = 0;
    
    return true;
}

bool Colored::setV(double v){
    v_ = v;
    return true;
}

bool Colored::setVxy(double vx, double vy){
    vx_ = vx;
    vy_ = vy;
    return true;
}

bool Colored::setScale(double shape_scale){
    shape_scale_ = shape_scale;
    return true;
}

double Colored::interpUnit(double x1, double x2, double y1, double y2, double x){
    // x1 should be smaller than x2
    if(x1 > x2){
        double temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
    }
    // Do interpolation (no extrapolation)
    double y;
    if(x <= x1){
        y = y1;
    }
    else if (x >= x2){
        y = y2;
    }
    else{
        y = y1 + (y2 - y1) / (x2 - x1) * (x - x1);
    }
    return y;
}

//static
double Colored::myAtan2(double y, double x){
    double agl = atan2(y, x) * RAD2DEG;
    if(agl < 0){
        agl = agl + 360;
    }
    return agl;
}

//static
void Colored::getRGB(double x_m, double y_m, unsigned char* pixel)
{
    int x_p = ((int)(METER2PIXEL * x_m + 0.5)) + ORIGIN_X;
    int y_p = ((int)(-METER2PIXEL * y_m + 0.5)) + ORIGIN_Y;
    y_p = WIN_HEIGHT - y_p;
    
    glReadPixels(x_p, y_p, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
}

bool Colored::setRGB(int color, int rgb[]){
    bool flag = true;
    switch (color) {
        case -1:
            rgb[0] = 153;   rgb[1] = 204;   rgb[2] = 255; //blue
            break;
        case 0:
            rgb[0] = 255;   rgb[1] = 255;   rgb[2] = 255; //white
            break;
        case 1:
            rgb[0] = 255;   rgb[1] = 153;   rgb[2] = 153; //red
            break;
        case 100:
            rgb[0] = 255;   rgb[1] = 250;   rgb[2] = 240; //gray
            break;
        case 101:
            rgb[0] = 0;     rgb[1] = 0;     rgb[2] = 0;   //black
        default:
            flag = false;
            break;
    }
    return flag;
}

void Colored::fall(double dt){
    x_ += vx_ * dt;
    y_ += vy_ * dt;
    vy_ -= G * dt;
}

int Colored::setHp(double hp, double ratio){ //ratio = -1
    if(ratio < 0){
        hp_ = hp;
    }
    else{
        hp_ = hp_max_ * ratio;
    }
    if(hp_ > hp_max_){
        hp_ = hp_max_;
    }
    if(hp_ <= 0.1){
        hp_ = 0;
        state_ = 0;
    }
    return state_;
}

int Colored::setHpMax1(double hp_max){
    hp_max_ = hp_max;
    return state_;
}

int Colored::minusHp(double hp_minus){
    setHp(hp_ - hp_minus);
    return state_;
}

bool Colored::setXY(double x, double y){
    x_ = x;
    y_ = y;
    return true;
}

bool Colored::isInside(double margin){ //margin = 0.0
    return ( x_ < WIN_LENGTH_METER + margin && x_ >= 0 - margin && y_ < WIN_HEIGHT_METER + margin && y_ >= 0 - margin);
}

//static
bool Colored::isInside2(double x, double y, double margin){ //margin = 0.0
    return ( x < WIN_LENGTH_METER + margin && x >= 0 - margin && y < WIN_HEIGHT_METER + margin && y >= 0 - margin);
}

bool Colored::setState(int state){
    state_ = state;
    return true;
}

bool Colored::myglVertex2d(double x_m, double y_m){
    double x_p = METER2PIXEL * x_m + (double)ORIGIN_X;
    double y_p = -METER2PIXEL * y_m + (double)ORIGIN_Y;
    glVertex2d(x_p, y_p);
    return ( (int)(x_p + 0.5) < WIN_LENGTH && (int)(x_p + 0.5) >= 0 && (int)(y_p + 0.5) < WIN_HEIGHT && (int)(y_p + 0.5) >= 0);
}

double Colored::_hp(){
    return hp_;
}

double Colored::_hp_max1(){
    return hp_max_;
}

int Colored::_state()
{
    return state_;
}

double Colored::_x(){
    return x_;
}

double Colored::_y(){
    return y_;
}

double Colored::_vx(){
    return vx_;
}

double Colored::_vy(){
    return vy_;
}

int Colored::_color(){
    return color_;
}

int Colored::_time_prev(){
    return time_prev_;
}

bool Colored::setTimePrev(int time_prev){
    time_prev_ = time_prev;
    return true;
}

//static
double Colored::getMinHp(Colored* c1, Colored* c2, double hp_minus){
    double hp_min = hp_minus;
    if(c1->_hp() < hp_min){
        hp_min = c1->_hp();
    }
    if(c2->_hp() < hp_min){
        hp_min = c2->_hp();
    }
    return hp_min;
}

double Colored::getRho(double agl){
    return 1.0;
}
