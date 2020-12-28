#ifndef COLORED_HPP
#define COLORED_HPP

const int MAX_SHAPE_NUM = 500;

const double G = 9.8;
const double MYPI = 3.141592653589;
const double DEG2RAD = MYPI / 180.0;
const double RAD2DEG = 180.0 / MYPI;
const double METER2PIXEL = 10.0;
const double PIXEL2METER = 0.1;
const int WIN_HEIGHT = 768;
const int WIN_LENGTH = 600;
const int ORIGIN_X = 0;
const int ORIGIN_Y = WIN_HEIGHT;
const double WIN_HEIGHT_METER = ((double) WIN_HEIGHT) * PIXEL2METER;
const double WIN_LENGTH_METER = ((double) WIN_LENGTH) * PIXEL2METER;
const double DOUBLE_BIG = 10000000000000;

const double WIN_MARGIN_METER = 20;

const int COLOR_NUM = 4;

class Colored{
protected:
    double shape_scale_;
    double x_;
    double y_;
    double vx_;
    double vy_;
    double v_;
    int state_;
    int color_;
    int rgb_[COLOR_NUM];
    int line_rgb_[COLOR_NUM];
    double line_width_;
    double hp_;
    double hp_max_;
    bool flag_enable_blend_;
    int time_prev_;
public:
    Colored();
    ~Colored();
    static void swap(double &a, double &b);
    static void swap(int &a, int &b);
    static double myRand(double min_value, double max_value);
    static void bubbleSort(int n, double x[], int index[]);
    
    double interpUnit(double x1, double x2, double y1, double y2, double x);
    static double myAtan2(double y, double x);
    bool myglVertex2d(double x_m, double y_m);
    static void getRGB(double x_m, double y_m, unsigned char* pixel);
    
    bool setColored(double x, double y, int state, int color, double hp_max);
    bool setV(double v);
    bool setVxy(double vx, double vy);
    bool setScale(double shape_scale);
    bool setRGB(int color, int rgb[]);
    int setHp(double hp, double ratio = -1);
    int setHpMax1(double hp_max);
    int minusHp(double hp_minus);
    bool setXY(double x, double y);
    bool setState(int state);
    bool setTimePrev(int time_prev);
    
    bool isInside(double margin = 0.0);
    static bool isInside2(double x, double y, double margin = 0.0);
    
    void fall(double dt);
    static double getMinHp(Colored* c1, Colored* c2, double hp_minus);
    
    double _hp();
    double _hp_max1();
    int _state();
    double _x();
    double _y();
    double _vx();
    double _vy();
    int _color();
    int _time_prev();
    
    virtual double getRho(double agl);
    
};

#endif // COLORED_HPP


