#include "ColorQuad.hpp"
#include "fssimplewindow.h"

bool ColorQuad::setColorQuad(double x, double y, int state, int color, double hp_max, double a, double b){
    setColored(x, y, state, color, hp_max);
    a_ = a;
    b_ = b;
    flag_enable_blend_ = true;
    if(a_ < b_){
        r_  = a_;
    }
    else{
        r_ = b_;
    }
    return true;
}

double ColorQuad::getRho(double agl){//agl = 0.0
    return r_;
}

void ColorQuad::show(){
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

void ColorQuad::showFull(bool flag_white){ // flag_white = false
    if(state_ > 0){
        if(flag_white){
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
        glBegin(GL_QUADS);
        myglVertex2d(x_ + a_/2, y_ + b_/2);
        myglVertex2d(x_ - a_/2, y_ + b_/2);
        myglVertex2d(x_ - a_/2, y_ - b_/2);
        myglVertex2d(x_ + a_/2, y_ - b_/2);
        glEnd();
        if(flag_white){
            glDisable(GL_BLEND);
        }
        
    }
}

void ColorQuad::showUp(){
    if(state_ > 0){
        double y_hp = (hp_ / hp_max_) * b_ - b_/2;
        glColor3ub(rgb_[0], rgb_[1], rgb_[2]);
        glBegin(GL_QUADS);
        myglVertex2d(x_ + a_/2, y_ + y_hp);
        myglVertex2d(x_ - a_/2, y_ + y_hp);
        myglVertex2d(x_ - a_/2, y_ - b_/2);
        myglVertex2d(x_ + a_/2, y_ - b_/2);
        glEnd();
        
        glColor3ub(0, 0, 0);
        glLineWidth((float)line_width_);
        glBegin(GL_LINES);
        myglVertex2d(x_ + a_/2, y_ + y_hp);
        myglVertex2d(x_ - a_/2, y_ + y_hp);
        glEnd();
    }
}

void ColorQuad::showLine(){
    if(state_ > 0){
        glColor3ub(0, 0, 0);
        glLineWidth((float)line_width_);
        glBegin(GL_LINE_LOOP);
        myglVertex2d(x_ + a_/2, y_ + b_/2);
        myglVertex2d(x_ - a_/2, y_ + b_/2);
        myglVertex2d(x_ - a_/2, y_ - b_/2);
        myglVertex2d(x_ + a_/2, y_ - b_/2);
        glEnd();
    }
}


