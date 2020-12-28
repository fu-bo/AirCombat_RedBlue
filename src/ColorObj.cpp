#include "ColorObj.hpp"
#include "fssimplewindow.h"
#include <math.h>
#include <stdio.h>

ColorObj::ColorObj(){}

ColorObj::~ColorObj(){}

bool ColorObj::setColorObj(double x, double y, int state, int color, double hp_max, int shape_n, int shape_agl_res, double* shape_x, double* shape_y){
    
    setColored(x, y, state, color, hp_max);
    
    
    shape_n_ = shape_n;
    const int shape_N = shape_n;
    //shape_x_ = new double[MAX_SHAPE_NUM]();
    //shape_y_ = new double[MAX_SHAPE_NUM]();
    shape_y_min_ = DOUBLE_BIG;
    double shape_y_max = -DOUBLE_BIG;
    double shape_agl[MAX_SHAPE_NUM];
    double shape_rho[MAX_SHAPE_NUM];
    for(int i = 0; i < shape_n_; i++){
        shape_x_[i] = shape_x[i];
        shape_y_[i] = shape_y[i];
        shape_rho[i] = sqrt(shape_x[i] * shape_x[i] + shape_y[i] * shape_y[i]);
        shape_agl[i] = myAtan2(shape_y[i], shape_x[i]);
        if(shape_y[i] < shape_y_min_){
            shape_y_min_ = shape_y[i];
            shape_y_min_ind_ = i;
        }
        if(shape_y[i] > shape_y_max){
            shape_y_max = shape_y[i];
        }
    }
    shape_y_range_ = shape_y_max - shape_y_min_;
    
    if (360 % shape_agl_res == 0){
        shape_agl_res_ = (double) shape_agl_res;
        shape_m_ = 360 / shape_agl_res;
    }
    else{
        shape_agl_res_ = 10;
        shape_m_ = 36;
    }
    
    const int shape_M = shape_m_ + 1;
    //shape_rho_ = new double[MAX_SHAPE_NUM]();
    for(int i = 0; i < shape_m_; i++){
        double agl = shape_agl_res_ * ((double) i);
        shape_rho_[i] = interpRho(shape_agl, shape_rho, shape_n_, agl);
    }
    shape_rho_[shape_m_ + 1] = shape_rho_[0];
    
    return true;
}



double ColorObj::interpRho(double* x_array, double* y_array, int n, double x){
    double y_max = -1;
    for(int i = 0; i < n; i++){
        double x_front, x_behind, y_front, y_behind;
        double x_use = x;
        if(i < n-1){
            x_front = x_array[i];
            x_behind = x_array[i+1];
            y_front = y_array[i];
            y_behind = y_array[i+1];
        }
        else{
            x_front = x_array[i];
            x_behind = x_array[0];
            y_front = y_array[i];
            y_behind = y_array[0];
        }
        if(x_front > 270 && x_behind < 90 ){
            x_front -= 360;
            if(x_use > 270){
                x_use -= 360;
            }
        }
        if ( ((x_use - x_front) * (x_use - x_behind)) <= 0 ){
            double y_now = interpUnit(x_front, x_behind, y_front, y_behind, x_use);
            if(y_now > y_max){
                y_max = y_now;
            }
            //                printf("(i,x1,x2,y1,y2,x,y) = (%d,\t%.2f,\t%.2f,\t%.2f,\t%.2f,\t%.2f,\t%.2f)\n", i, x_front, x_behind, y_front, y_behind, x, y_max);
        }
    }
    if (y_max < 0){
        y_max = y_array[0];
    }
    
    return y_max;
    
}

double ColorObj::getRho(double agl){
    int i =  ( (int) (agl / shape_agl_res_) );
    if(i < 0){
        i = 0;
        printf("Bad input angle!\n");
    }
    else if(i >= shape_m_){
        i = shape_m_ - 1;
        printf("Bad input angle!\n");
    }
    double rho = shape_scale_ * interpUnit( ((double)i)*shape_agl_res_ , ((double)(i+1))*shape_agl_res_, shape_rho_[i], shape_rho_[i+1], agl);
    return rho;
}





void ColorObj::show(){
    if( (hp_ / hp_max_) > 0.99 ){
        showFull();
        showLine();
    }
    else if ( shape_y_min_ + (hp_ / hp_max_) * shape_y_range_ >= 0 ){
        showColoredUp();
        showLine();
    }
    else if ( (hp_ / hp_max_) > 0.01 ){
        showColoredDown();
        showLine();
    }
    else{
        showFull(true);
        showLine();
    }
    
}

int ColorObj::scanY(double hp_y, double* hp_x, int* index_up_out, int* index_down_out){
    const int shape_N = shape_n_;
    int index_up[MAX_SHAPE_NUM];
    int index_down[MAX_SHAPE_NUM];
    int hp_count = 0;
    
    for(int k = 0; k < shape_n_; k++){
        int i = k % shape_n_;
        int j = k-1;
        if(j < 0){
            j = j + shape_n_;
        }
        
        if( shape_y_[i] > hp_y && shape_y_[j] < hp_y ){
            index_up[hp_count] = i;
            index_down[hp_count] = j;
            hp_x[hp_count] = interpUnit(shape_y_[i], shape_y_[j], shape_x_[i], shape_x_[j], hp_y);
            hp_count++;
        }
        else if ( shape_y_[i] < hp_y && shape_y_[j] > hp_y ){
            index_up[hp_count] = j;
            index_down[hp_count] = i;
            hp_x[hp_count] = interpUnit(shape_y_[i], shape_y_[j], shape_x_[i], shape_x_[j], hp_y);
            hp_count++;
        }
    }
    const int HP_COUNT = hp_count;
    int index_of_index[MAX_SHAPE_NUM];
    for(int i = 0; i < hp_count; i++){
        index_of_index[i] = i;
    }
    bubbleSort(hp_count, hp_x, index_of_index);
    for(int i = 0; i < hp_count; i++){
        index_up_out[i] = index_up[ index_of_index[i] ];
        index_down_out[i] = index_down[ index_of_index[i] ];
    }
    return hp_count;
}

void ColorObj::showColoredDown(){
    if(state_ > 0){
        double y_hp = shape_y_min_ + (hp_ / hp_max_) * shape_y_range_;
        
        const int shape_N = shape_n_;
        int index_up[MAX_SHAPE_NUM];
        int index_down[MAX_SHAPE_NUM];
        double x_hp[MAX_SHAPE_NUM];
        int count_hp = scanY(y_hp, x_hp, index_up, index_down);
        
        unsigned char pixel_color[4];
        //            printf("(%d,%d,%d)\n",pixel_color[0],pixel_color[1],pixel_color[2]);
        getRGB(x_, y_, pixel_color);
        
        glColor3ub(rgb_[0], rgb_[1], rgb_[2]);
        glBegin(GL_TRIANGLE_FAN);
        myglVertex2d(x_,y_);
        myglVertex2d(x_ + shape_scale_ * x_hp[0], y_ + shape_scale_ * y_hp);
        for(int i = index_down[0]; i < index_down[0]+shape_n_; i++){
            int j = i;
            if(j >= shape_n_){
                j = j - shape_n_;
            }
            myglVertex2d(x_ + shape_scale_ * shape_x_[j], y_ + shape_scale_ * shape_y_[j]);
            if(j == index_down[count_hp-1]){
                break;
            }
        }
        myglVertex2d(x_ + shape_scale_ * x_hp[count_hp-1], y_ + shape_scale_ * y_hp);
        glEnd();
        
        if(pixel_color[0] == 0 && pixel_color[1] ==0 && pixel_color[2] == 0){
            glColor3ub(255, 255, 255);
        }
        else{
            glColor3ub(pixel_color[0], pixel_color[1], pixel_color[2]);
        }
        glBegin(GL_TRIANGLE_FAN);
        myglVertex2d(x_,y_);
        int count_line = 1;
        for(int i = index_down[0]; i < index_down[0]+shape_n_; i++){
            int j = i;
            if(j >= shape_n_){
                j = j - shape_n_;
            }
            if(count_line < count_hp){
                if(j == index_down[count_line]){
                    myglVertex2d(x_ + shape_scale_ * x_hp[count_line-1], y_ + shape_scale_ * y_hp);
                    myglVertex2d(x_ + shape_scale_ * x_hp[count_line], y_ + shape_scale_ * y_hp);
                    count_line += 2;
                }
            }
            if(j == index_down[count_hp-1]){
                break;
            }
            if( shape_y_[j] < y_hp){
                continue;
            }
            else{
                myglVertex2d(x_ + shape_scale_ * shape_x_[j], y_ + shape_scale_ * shape_y_[j]);
            }
            
        }
        myglVertex2d(x_ + shape_scale_ * x_hp[0], y_ + shape_scale_ * y_hp);
        glEnd();
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        if(flag_enable_blend_){
            glColor4ub(255, 255, 255, 100); // glGolor4f(0.5f,0.5f,0.5f,0.5f); The last entry is alpha
        }
        else{
            glColor3ub(255, 255, 255);
        }
        glBegin(GL_TRIANGLE_FAN);
        myglVertex2d(x_,y_);
        count_line = 1;
        for(int i = index_down[0]; i < index_down[0]+shape_n_; i++){
            int j = i;
            if(j >= shape_n_){
                j = j - shape_n_;
            }
            if(count_line < count_hp){
                if(j == index_down[count_line]){
                    myglVertex2d(x_ + shape_scale_ * x_hp[count_line-1], y_ + shape_scale_ * y_hp);
                    myglVertex2d(x_ + shape_scale_ * x_hp[count_line], y_ + shape_scale_ * y_hp);
                    count_line += 2;
                }
            }
            //                if(j == index_down[count_hp-1]){
            //                    break;
            //                }
            if( shape_y_[j] < y_hp){
                continue;
            }
            else{
                myglVertex2d(x_ + shape_scale_ * shape_x_[j], y_ + shape_scale_ * shape_y_[j]);
            }
            
        }
        myglVertex2d(x_ + shape_scale_ * x_hp[0], y_ + shape_scale_ * y_hp);
        glEnd();
        glDisable(GL_BLEND);
        
        glColor3ub(0, 0, 0);
        
        glLineWidth((float)line_width_);
        glBegin(GL_LINES);
        for(int count_line = 1; count_line < count_hp; count_line += 2){
            myglVertex2d(x_ + shape_scale_ * x_hp[count_line-1], y_ + shape_scale_ * y_hp);
            myglVertex2d(x_ + shape_scale_ * x_hp[count_line], y_ + shape_scale_ * y_hp);
        }
        glEnd();
        
    }
}

void ColorObj::showColoredUp(){
    if(state_ > 0){
        showFull(true);
        
        double y_hp = shape_y_min_ + (hp_ / hp_max_) * shape_y_range_;
        
        const int shape_N = shape_n_;
        int index_up[MAX_SHAPE_NUM];
        int index_down[MAX_SHAPE_NUM];
        double x_hp[MAX_SHAPE_NUM];
        int count_hp = scanY(y_hp, x_hp, index_up, index_down);
        
        glColor3ub(rgb_[0], rgb_[1], rgb_[2]);
        glBegin(GL_TRIANGLE_FAN);
        myglVertex2d(x_,y_);
        int count_line = count_hp - 2;
        for(int i = index_down[count_hp-1]; i < index_down[count_hp-1]+shape_n_; i++){
            int j = i;
            if(j >= shape_n_){
                j = j - shape_n_;
            }
            if(count_line >= 0){
                if(j == index_down[count_line]){
                    myglVertex2d(x_ + shape_scale_ * x_hp[count_line+1], y_ + shape_scale_ * y_hp);
                    myglVertex2d(x_ + shape_scale_ * x_hp[count_line], y_ + shape_scale_ * y_hp);
                    count_line -= 2;
                }
            }
            
            if( shape_y_[j] > y_hp){
                continue;
            }
            else{
                myglVertex2d(x_ + shape_scale_ * shape_x_[j], y_ + shape_scale_ * shape_y_[j]);
            }
            
        }
        myglVertex2d(x_ + shape_scale_ * shape_x_[ index_down[count_hp-1] ], y_ + shape_scale_ * shape_y_[ index_down[count_hp-1] ]);
        glEnd();
        
        glColor3ub(0, 0, 0);
        glLineWidth((float)line_width_);
        glBegin(GL_LINES);
        for(int count_line = 1; count_line < count_hp; count_line += 2){
            myglVertex2d(x_ + shape_scale_ * x_hp[count_line-1], y_ + shape_scale_ * y_hp);
            myglVertex2d(x_ + shape_scale_ * x_hp[count_line], y_ + shape_scale_ * y_hp);
        }
        glEnd();
        
    }
}

void ColorObj::showFull(bool flag_white){ // flag_white = false
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
        glBegin(GL_TRIANGLE_FAN);
        myglVertex2d(x_,y_);
        for(int i=0; i<shape_n_; i++)
        {
            double xx = x_ + shape_scale_ * shape_x_[i];
            double yy = y_ + shape_scale_ * shape_y_[i];
            myglVertex2d(xx,yy);
        }
        myglVertex2d(x_ + shape_scale_ * shape_x_[0], y_ + shape_scale_ * shape_y_[0]);
        glEnd();
        if(flag_white){
            glDisable(GL_BLEND);
        }
        
    }
}

void ColorObj::showLine(bool flag_loop){
    if(state_ > 0){
        glColor3ub(line_rgb_[0], line_rgb_[1], line_rgb_[2]);
        glLineWidth((float)line_width_);
        if(flag_loop){
            glBegin(GL_LINE_LOOP);
        }
        else{
            glBegin(GL_LINE_STRIP);
        }
        for(int i=0; i<shape_n_; i++)
        {
            double xx = x_ + shape_scale_ * shape_x_[i];
            double yy = y_ + shape_scale_ * shape_y_[i];
            myglVertex2d(xx,yy);
        }
        glEnd();
    }
}

void ColorObj::showRho(){
    if(state_ > 0){
        glColor3ub( ((int) (((double)rgb_[0]) * 0.6)), ((int) (((double)rgb_[1]) * 0.6)), ((int) (((double)rgb_[2]) * 0.6)));
        glBegin(GL_TRIANGLE_FAN);
        myglVertex2d(x_,y_);
        for(int i=0; i<shape_m_; i++)
        {
            double xx = x_ + shape_scale_ * shape_rho_[i] * cos(DEG2RAD * shape_agl_res_ * ((double)i));
            double yy = y_ + shape_scale_ * shape_rho_[i] * sin(DEG2RAD * shape_agl_res_ * ((double)i));
            myglVertex2d(xx,yy);
        }
        myglVertex2d(x_ + shape_scale_ * shape_rho_[0] * cos(DEG2RAD * shape_agl_res_ * ((double)0)), y_ + shape_scale_ * shape_rho_[0] * sin(DEG2RAD * shape_agl_res_ * ((double)0)));
        
        glEnd();
        glColor3ub(line_rgb_[0], line_rgb_[1], line_rgb_[2]);
        glLineWidth((float)line_width_);
        glBegin(GL_LINE_LOOP);
        for(int i=0; i<shape_m_; i++)
        {
            double xx = x_ + shape_scale_ * shape_rho_[i] * cos(DEG2RAD * shape_agl_res_ * ((double)i));
            double yy = y_ + shape_scale_ * shape_rho_[i] * sin(DEG2RAD * shape_agl_res_ * ((double)i));
            myglVertex2d(xx,yy);
        }
        glEnd();
        
    }
}



void ColorObj::moveRandom(double dt, int random_type){ //random_type = 0
    if(random_type == 0){
        double agl = myRand(0, 360);
        double alpha = 0.1;
        vx_ = (1 - alpha) * vx_ + alpha * ( v_ * cos(DEG2RAD * agl) );
        vy_ = (1 - alpha) * vy_ + alpha * ( v_ * sin(DEG2RAD * agl) );
        double x_new = x_ + vx_ * dt;
        double y_new = y_ + vy_ * dt;
        if(isInside2(x_new, y_new)){
            x_ = x_new;
            y_ = y_new;
        }
    }
    else{
        double x_new = x_ + vx_ * dt;
        double y_new = y_ + vy_ * dt;
        if(isInside2(x_new, y_new)){
            x_ = x_new;
            y_ = y_new;
        }
        else{
            double agl = myRand(0, 360);
            vx_ = v_ * cos(DEG2RAD * agl);
            vy_ = v_ * sin(DEG2RAD * agl);
        }
    }
}

void ColorObj::moveUp(double dt, bool flag_up){
    vx_ = 0;
    if(flag_up){
        vy_ = v_;
    }
    else{
        vy_ = -v_;
    }
    double y_new = y_ + vy_ * dt;
    if(isInside2(x_, y_new)){
        y_ = y_new;
    }
    if(!isInside()){
        y_ = y_new;
    }
}

void ColorObj::moveRight(double dt, bool flag_right){
    vy_ = 0;
    if(flag_right){
        vx_ = v_;
    }
    else{
        vx_ = -v_;
    }
    double x_new = x_ + vx_ * dt;
    if(isInside2(x_new, y_)){
        x_ = x_new;
    }
    if(!isInside()){
        x_ = x_new;
    }
}

int ColorObj::move(double dt){
    if(state_ > 0){
        x_ += vx_ * dt;
        y_ += vy_ * dt;
    }
    if(!isInside(WIN_MARGIN_METER)){
        state_ = 0;
    }
    return state_;
}

void ColorObj::randomShape(){
    shape_scale_ *= myRand(0.8, 1.2);
    for(int i = 0; i < shape_n_; i++){
        shape_x_[i] *= myRand(0.97, 1.03);
        shape_y_[i] *= myRand(0.97, 1.03);
    }
}
