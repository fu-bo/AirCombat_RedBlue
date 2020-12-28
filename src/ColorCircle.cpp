#include "ColorCircle.hpp"
#include "fssimplewindow.h"
#include <math.h>

bool ColorCircle::setColorCircle(double x, double y, int state, int color, double hp_max, double r, int shape_n){
    setColored(x, y, state, color, hp_max);
    
    flag_enable_blend_ = true;
    r_ = r;
    shape_n_ = shape_n;
    return true;
}


void ColorCircle::showFull(bool flag_white){ //flag_white = false
    if(state_ > 0){
        if(flag_white){
            //glColor3ub(255, 255, 255);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            if(flag_enable_blend_){
                glColor4ub(255, 255, 255, 100);
            }
            else{
                glColor3ub(255, 255, 255);
            }
        }
        else{
            glColor3ub(rgb_[0], rgb_[1], rgb_[2]);
        }
        glBegin(GL_POLYGON);
        for(int i=0; i<shape_n_; i++)
        {
            double xx = x_ + shape_scale_ * r_ * cos( ((double)i)/shape_n_ * 2 * MYPI );
            double yy = y_ + shape_scale_ * r_ * sin( ((double)i)/shape_n_ * 2 * MYPI );
            myglVertex2d(xx,yy);
        }
        glEnd();
        if(flag_white){
            glDisable(GL_BLEND);
        }
        
    }
}

double ColorCircle::getRho(double agl){//agl = 0.0
    return r_;
}

void ColorCircle::showLine(){
    if(state_ > 0){
        glColor3ub(0, 0, 0);
        glLineWidth((float)line_width_);
        glBegin(GL_LINE_LOOP);
        for(int i=0; i<shape_n_; i++)
        {
            double xx = x_ + shape_scale_ * r_ * cos( ((double)i)/shape_n_ * 2 * MYPI );
            double yy = y_ + shape_scale_ * r_ * sin( ((double)i)/shape_n_ * 2 * MYPI );
            myglVertex2d(xx,yy);
        }
        glEnd();
    }
}

void ColorCircle::showUp(){
    if(state_ > 0){
        
        double y_hp = (hp_ / hp_max_) * 2 * r_ - r_;
        double x_hp2 = sqrt(r_ * r_ - y_hp * y_hp);
        double x_hp1 = - x_hp2;
        
        double agl1 = myAtan2(y_hp, x_hp1);
        double agl2 = myAtan2(y_hp, x_hp2);
        if(agl1 > agl2){
            agl2 = agl2 + 360;
        }
        
        glColor3ub(rgb_[0], rgb_[1], rgb_[2]);
        glBegin(GL_POLYGON);
        for(double agl = agl1; agl <= agl2; agl += 360 / ((double)shape_n_) )
        {
            double yy = y_ + shape_scale_ * r_ * sin( agl * DEG2RAD );
            double xx = x_ + shape_scale_ * r_ * cos( agl * DEG2RAD );
            myglVertex2d(xx,yy);
        }
        myglVertex2d(x_ + shape_scale_ * x_hp2, y_ + shape_scale_ * y_hp);
        glEnd();
        
        glColor3ub(0, 0, 0);
        glLineWidth((float)line_width_);
        glBegin(GL_LINES);
        myglVertex2d(x_ + shape_scale_ * x_hp1, y_ + shape_scale_ * y_hp);
        myglVertex2d(x_ + shape_scale_ * x_hp2, y_ + shape_scale_ * y_hp);
        glEnd();
    }
}

void ColorCircle::show(){
    if( (hp_ / hp_max_) > 0.99 ){
        showFull();
        showLine();
    }
    else if ( (hp_ / hp_max_) > 0.01 ){
        showFull(true);
        showUp();
        showLine();
    }
    else{
        showFull(true);
        showLine();
    }
    
}

bool ColorCircle::setShape(double r, int shape_n, double hp_max){
    r_ = r;
    shape_n_ = shape_n;
    if(hp_max > 0){
        hp_max_ = hp_max;
    }
    return true;
}
