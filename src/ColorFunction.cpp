
#include "ColorFunction.hpp"
#include "ColorObj.hpp"
#include "ColorCircle.hpp"
#include "ColorQuad.hpp"
#include "Bullet.hpp"
#include <math.h>

//static
bool ColorFunction::checkCollision(ColorObj* clr1, ColorObj* clr2){
    
    bool flag_collision = false;
    double threshold = 1;
    
    
    if(clr1->_state()==1 && clr2->_state()==1){
        double x1 = clr1->_x();
        double x2 = clr2->_x();
        double y1 = clr1->_y();
        double y2 = clr2->_y();
        double agl1 = myAtan2(y2 - y1, x2 - x1);
        double agl2 = agl1 + 180;
        if(agl2 >= 360){
            agl2 -= 360;
        }
        double rho1 = clr1->getRho(agl1);
        double rho2 = clr2->getRho(agl2);
        double dist = sqrt( (y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1) );
        if( dist < rho1 + rho2 - threshold ){
            flag_collision = true;
        }
    }
    
    return flag_collision;
}

//static
bool ColorFunction::checkCollision(ColorObj* clr1, ColorCircle* clr2){
    
    bool flag_collision = false;
    double threshold = clr2->getRho() / 5;
    if( threshold > 1){
        threshold = 1;
    }
    
    if(clr1->_state()==1 && clr2->_state()==1){
        double x1 = clr1->_x();
        double x2 = clr2->_x();
        double y1 = clr1->_y();
        double y2 = clr2->_y();
        double agl1 = myAtan2(y2 - y1, x2 - x1);
        double agl2 = agl1 + 180;
        if(agl2 >= 360){
            agl2 -= 360;
        }
        double rho1 = clr1->getRho(agl1);
        double rho2 = clr2->getRho(agl2);
        double dist = sqrt( (y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1) );
        if( dist < rho1 + rho2 - threshold ){
            flag_collision = true;
        }
    }
    
    return flag_collision;
}

//static
bool ColorFunction::checkCollision(ColorObj* clr1, ColorQuad* clr2){
    
    bool flag_collision = false;
    double threshold = clr2->getRho() / 5;
    if( threshold > 1){
        threshold = 1;
    }
    
    if(clr1->_state()==1 && clr2->_state()==1){
        double x1 = clr1->_x();
        double x2 = clr2->_x();
        double y1 = clr1->_y();
        double y2 = clr2->_y();
        double agl1 = myAtan2(y2 - y1, x2 - x1);
        double agl2 = agl1 + 180;
        if(agl2 >= 360){
            agl2 -= 360;
        }
        double rho1 = clr1->getRho(agl1);
        double rho2 = clr2->getRho(agl2);
        double dist = sqrt( (y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1) );
        if( dist < rho1 + rho2 - threshold ){
            flag_collision = true;
        }
    }
    
    return flag_collision;
}



//static
bool ColorFunction::checkCollision(ColorCircle* clr1, ColorCircle* clr2){
    
    bool flag_collision = false;
    
    if(clr1->_state()==1 && clr2->_state()==1){
        double rho1 = clr1->getRho();
        double rho2 = clr2->getRho();
        
        double threshold = rho1 / 5;
        if( threshold > rho2 / 5){
            threshold = rho2 / 5;
        }
        if( threshold > 1 ){
            threshold = 1;
        }
        
        if(rho1 < 1.5 && rho2 < 1.5){
            threshold = -1;
        }
        
        double x1 = clr1->_x();
        double x2 = clr2->_x();
        double y1 = clr1->_y();
        double y2 = clr2->_y();
        
        double dist = sqrt( (y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1) );
        if( dist < rho1 + rho2 - threshold ){
            flag_collision = true;
            //                printf("(%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f)\n", x1,y1,x2,y2,rho1,rho2,dist);
        }
    }
    
    return flag_collision;
}

//static
bool ColorFunction::checkCollision(ColorQuad* clr1, ColorCircle* clr2){
    
    bool flag_collision = false;
    
    if(clr1->_state()==1 && clr2->_state()==1){
        double rho1 = clr1->getRho();
        double rho2 = clr2->getRho();
        
        double threshold = rho1 / 5;
        if( threshold > rho2 / 5){
            threshold = rho2 / 5;
        }
        if( threshold > 1 ){
            threshold = 1;
        }
        
        double x1 = clr1->_x();
        double x2 = clr2->_x();
        double y1 = clr1->_y();
        double y2 = clr2->_y();
        
        double dist = sqrt( (y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1) );
        if( dist < rho1 + rho2 - threshold ){
            flag_collision = true;
        }
    }
    
    return flag_collision;
}

//static
bool ColorFunction::checkCollision(ColorQuad* clr1, ColorQuad* clr2){
    
    bool flag_collision = false;
    
    if(clr1->_state()==1 && clr2->_state()==1){
        double rho1 = clr1->getRho();
        double rho2 = clr2->getRho();
        
        double threshold = rho1 / 5;
        if( threshold > rho2 / 5){
            threshold = rho2 / 5;
        }
        if( threshold > 1 ){
            threshold = 1;
        }
        
        double x1 = clr1->_x();
        double x2 = clr2->_x();
        double y1 = clr1->_y();
        double y2 = clr2->_y();
        
        double dist = sqrt( (y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1) );
        if( dist < rho1 + rho2 - threshold ){
            flag_collision = true;
        }
    }
    
    return flag_collision;
}

bool ColorFunction::fire(Colored* c, Bullet** bullet, int bullet_num, double x, double y, double vx, double vy, int fire_type, int shoot_max){ //fire_type = 0, shoot_max = 16
    bool flag_fire = false;
    
    double r_set = 0.6;
    int shape_n_set = 12;
    
    switch (fire_type) {
        case 0:{ //normal
            double v = sqrt(vx * vx + vy * vy );
            for(int j = 0; j < bullet_num; j++){
                if(bullet[j]->_state() == 0){
                    bullet[j]->setShape(r_set, shape_n_set, 1);
                    bullet[j]->setV(v);
                    bullet[j]->setVxy(vx, vy);
                    bullet[j]->shoot(x, y, 0);
                    flag_fire = true;
                    break;
                }
            }
            break;
        }
        case 1:{ // circle
            double v = vx;
            double start_agl = vy;
            double r = 0.8 * c->getRho(0);
            int shoot_count = 0;
            double agl_res = 360 / shoot_max;
            for(int j = 0; j < bullet_num; j++){
                if(bullet[j]->_state() == 0){
                    bullet[j]->setShape(r_set, shape_n_set, 1);
                    bullet[j]->setV(v);
                    double agl = (start_agl + agl_res * ((double)shoot_count) ) * DEG2RAD;
                    bullet[j]->setVxy(v * cos(agl), v * sin(agl));
                    bullet[j]->shoot(x + r * cos(agl), y + r * sin(agl), 0);
                    flag_fire = true;
                    shoot_count++;
                    if(shoot_count >= shoot_max){
                        break;
                    }
                }
            }
            break;
        }
        case 2:{ //line
            double v = sqrt(vx * vx + vy * vy );
            double r = 0.8 * c->getRho(0);
            int shoot_count = 0;
            for(int j = 0; j < bullet_num; j++){
                if(bullet[j]->_state() == 0){
                    bullet[j]->setShape(r_set, shape_n_set, 1);
                    bullet[j]->setV(v);
                    bullet[j]->setVxy(vx, vy);
                    double x_temp = x +  ((double)shoot_count) / ((double) shoot_max ) * 2 * r - r;
                    bullet[j]->shoot(x_temp , y, 0);
                    flag_fire = true;
                    shoot_count++;
                    if(shoot_count > shoot_max){
                        break;
                    }
                }
            }
            break;
        }
        case 3:{ //throw
            double v = vx;
            double start_agl = vy;
            double r = c->getRho(0) * 0.9;
            double rand_ratio = 1;
            int shoot_count = 0;
            double agl_res = 180 / shoot_max;
            for(int j = 0; j < bullet_num; j++){
                if(bullet[j]->_state() == 0){
                    bullet[j]->setShape(1.2, 36, 2);
                    bullet[j]->setV(v);
                    double agl = (start_agl + agl_res * ((double)shoot_count) ) * DEG2RAD;
                    bullet[j]->setVxy(v * cos(agl) + myRand(-rand_ratio, rand_ratio) * v, v * sin(agl) + myRand(0, rand_ratio) * v);
                    if(agl < MYPI / 2){
                        bullet[j]->shoot(x + r, y, 1);
                    }
                    else{
                        bullet[j]->shoot(x - r, y, 1);
                    }
                    flag_fire = true;
                    shoot_count++;
                    if(shoot_count >= shoot_max){
                        break;
                    }
                }
            }
            break;
        }
        case 4:{ // explode
            double v = vx;
            double start_agl = vy;
            double r = c->getRho(0);
            double ratio = 1;
            double rand_ratio = 0.5;
            double agl_res = 360 / shoot_max;
            int j = 0;
            for(double r_use = 0.2 * r; r_use < 1.1 * r; r_use += 0.2 * r){
                int shoot_count = 0;
                for(; j < bullet_num; j++){
                    if(bullet[j]->_state() == 0){
                        bullet[j]->setShape(myRand(0.6, 2), 36, 2);
                        bullet[j]->setV(v);
                        double agl = (start_agl + agl_res * ((double)shoot_count) ) * DEG2RAD;
                        bullet[j]->setVxy( r_use * ratio * cos(agl) + myRand(-1, 1) * rand_ratio * v, r_use * ratio * sin(agl) + myRand(-0.5, 1) * rand_ratio * v);
                        bullet[j]->shoot(x+r_use*cos(agl), y+r_use*sin(agl), 1);
                        flag_fire = true;
                        shoot_count++;
                        if(shoot_count >= shoot_max){
                            break;
                        }
                    }
                }
            }
            break;
        }
            
        default:
            break;
    }
    
    return flag_fire;
}

void ColorFunction::showLife(int count_life, int count_large, int max_life, int max_large, ColorObj** life, ColorCircle** large){
    for(int i = 0; i < max_life; i++){
        if(i < count_life){
            life[i]->setState(1);
        }
        else{
            life[i]->setState(0);
        }
    }
    for(int i = 0; i < max_large; i++){
        if(i < count_large){
            large[i]->setState(1);
        }
        else{
            large[i]->setState(0);
        }
    }
}

//static
void ColorFunction::setPlane(int plane_id, ColorObj* clr){
    
    switch (plane_id) {
        case 1:{
            double shape_x[] = {0.208, 0.210, 0.210, 0.165, 0.128, 0.093, 0.073, 0.075, 0.083, 0.083, 0.048, 0.008, -0.043, -0.068, -0.065, -0.060, -0.065, -0.098, -0.130, -0.170, -0.218, -0.218, -0.220, -0.263, -0.320, -0.385, -0.328, -0.258, -0.195, -0.125, -0.103, -0.060, -0.010, 0.038, 0.090, 0.120, 0.173, 0.238, 0.285, 0.328, 0.360, 0.318, 0.280, 0.258, 0.225};
            double shape_y[] = {0.121, 0.176, 0.223, 0.194, 0.170, 0.215, 0.244, 0.309, 0.383, 0.446, 0.490, 0.514, 0.467, 0.441, 0.388, 0.320, 0.254, 0.218, 0.170, 0.197, 0.212, 0.160, 0.121, 0.063, 0.005, -0.058, -0.068, -0.068, -0.076, -0.079, -0.118, -0.142, -0.152, -0.149, -0.126, -0.071, -0.073, -0.081, -0.081, -0.081, -0.079, -0.026, 0.013, 0.045, 0.084};
            int shape_n = 45;
            double hp_max = 10;
            clr->setColorObj(20, 10, 0, -1, hp_max, shape_n, 5, shape_x, shape_y);
            //bool setColorObj(int x, int y, int state, int color, double hp_max, int shape_n, int shape_agl_res, double* shape_x, double* shape_y)
            clr->setScale(10);
            break;
        }
        case 2:{
            double shape_x[] = {0.406, 0.385, 0.361, 0.300, 0.244, 0.197, 0.135, 0.130, 0.135, 0.125, 0.104, 0.064, 0.011, -0.048, -0.101, -0.125, -0.138, -0.135, -0.138, -0.135, -0.191, -0.244, -0.298, -0.351, -0.383, -0.396, -0.398, -0.377, -0.332, -0.290, -0.231, -0.162, -0.125, -0.104, -0.077, -0.029, 0.016, 0.056, 0.090, 0.112, 0.122, 0.173, 0.228, 0.292, 0.337, 0.385};
            double shape_y[] = {-0.036, 0.003, 0.028, 0.055, 0.072, 0.077, 0.086, 0.135, 0.196, 0.257, 0.295, 0.342, 0.353, 0.348, 0.306, 0.271, 0.210, 0.163, 0.116, 0.077, 0.069, 0.061, 0.052, 0.044, 0.019, -0.022, -0.063, -0.102, -0.116, -0.124, -0.121, -0.121, -0.119, -0.168, -0.204, -0.226, -0.240, -0.224, -0.188, -0.130, -0.105, -0.099, -0.099, -0.102, -0.091, -0.069};
            int shape_n = 46;
            double hp_max = 5;
            clr->setColorObj(20, 10, 0, -1, hp_max, shape_n, 5, shape_x, shape_y);
            //bool setColorObj(int x, int y, int state, int color, double hp_max, int shape_n, int shape_agl_res, double* shape_x, double* shape_y)
            clr->setScale(10);
            break;
        }
        case 3:{
            double shape_x[] = {0.225, 0.258, 0.280, 0.318, 0.360, 0.328, 0.285, 0.238, 0.173, 0.120, 0.090, 0.038, -0.010, -0.060, -0.103, -0.125, -0.195, -0.258, -0.328, -0.385, -0.320, -0.263, -0.220, -0.218, -0.218, -0.170, -0.130, -0.098, -0.065, -0.060, -0.065, -0.068, -0.043, 0.008, 0.048, 0.083, 0.083, 0.075, 0.073, 0.093, 0.128, 0.165, 0.210, 0.210, 0.208};
            double shape_y[] = {-0.084, -0.045, -0.013, 0.026, 0.079, 0.081, 0.081, 0.081, 0.073, 0.071, 0.126, 0.149, 0.152, 0.142, 0.118, 0.079, 0.076, 0.068, 0.068, 0.058, -0.005, -0.063, -0.121, -0.160, -0.212, -0.197, -0.170, -0.218, -0.254, -0.320, -0.388, -0.441, -0.467, -0.514, -0.490, -0.446, -0.383, -0.309, -0.244, -0.215, -0.170, -0.194, -0.223, -0.176, -0.121};
            int shape_n = 45;
            double hp_max = 5;
            clr->setColorObj(40, 30, 0, 1, hp_max, shape_n, 5, shape_x, shape_y);
            //bool setColorObj(int x, int y, int state, int color, double hp_max, int shape_n, int shape_agl_res, double* shape_x, double* shape_y)
            clr->setScale(10);
            break;
        }
        case 4:{
            double shape_x[] = {0.385, 0.337, 0.292, 0.228, 0.173, 0.122, 0.112, 0.090, 0.056, 0.016, -0.029, -0.077, -0.104, -0.125, -0.162, -0.231, -0.290, -0.332, -0.377, -0.398, -0.396, -0.383, -0.351, -0.298, -0.244, -0.191, -0.135, -0.138, -0.135, -0.138, -0.125, -0.101, -0.048, 0.011, 0.064, 0.104, 0.125, 0.135, 0.130, 0.135, 0.197, 0.244, 0.300, 0.361, 0.385, 0.406};
            double shape_y[] = {0.069, 0.091, 0.102, 0.099, 0.099, 0.105, 0.130, 0.188, 0.224, 0.240, 0.226, 0.204, 0.168, 0.119, 0.121, 0.121, 0.124, 0.116, 0.102, 0.063, 0.022, -0.019, -0.044, -0.052, -0.061, -0.069, -0.077, -0.116, -0.163, -0.210, -0.271, -0.306, -0.348, -0.353, -0.342, -0.295, -0.257, -0.196, -0.135, -0.086, -0.077, -0.072, -0.055, -0.028, -0.003, 0.036};
            int shape_n = 46;
            double hp_max = 5;
            clr->setColorObj(40, 30, 0, 1, hp_max, shape_n, 5, shape_x, shape_y);
            //bool setColorObj(int x, int y, int state, int color, double hp_max, int shape_n, int shape_agl_res, double* shape_x, double* shape_y)
            clr->setScale(10);
            break;
        }
        case 5:{
            double shape_x[] = {0.372, 0.362, 0.353, 0.344, 0.328, 0.301, 0.278, 0.243, 0.216, 0.212, 0.216, 0.213, 0.213, 0.205, 0.193, 0.181, 0.176, 0.170, 0.164, 0.146, 0.132, 0.121, 0.109, 0.089, 0.060, 0.032, -0.005, -0.050, -0.083, -0.099, -0.107, -0.122, -0.142, -0.150, -0.160, -0.183, -0.201, -0.209, -0.220, -0.226, -0.227, -0.230, -0.234, -0.279, -0.322, -0.344, -0.358, -0.366, -0.328, -0.289, -0.262, -0.226, -0.223, -0.222, -0.222, -0.220, -0.197, -0.158, -0.153, -0.141, -0.119, -0.093, -0.075, -0.059, -0.032, 0.004, 0.030, 0.054, 0.075, 0.094, 0.105, 0.121, 0.149, 0.160, 0.165, 0.181, 0.212, 0.213, 0.219, 0.223, 0.219, 0.251, 0.277, 0.321};
            double shape_y[] = {-0.091, -0.055, -0.030, -0.002, 0.017, 0.032, 0.038, 0.043, 0.044, 0.084, 0.120, 0.159, 0.205, 0.236, 0.262, 0.285, 0.317, 0.347, 0.369, 0.345, 0.321, 0.301, 0.277, 0.282, 0.282, 0.282, 0.277, 0.280, 0.280, 0.315, 0.350, 0.369, 0.336, 0.307, 0.282, 0.269, 0.257, 0.214, 0.181, 0.140, 0.104, 0.066, 0.033, 0.028, 0.002, -0.028, -0.066, -0.095, -0.096, -0.096, -0.096, -0.087, -0.118, -0.150, -0.175, -0.200, -0.227, -0.228, -0.262, -0.290, -0.306, -0.295, -0.268, -0.233, -0.230, -0.230, -0.232, -0.232, -0.230, -0.249, -0.276, -0.298, -0.301, -0.271, -0.238, -0.222, -0.222, -0.184, -0.145, -0.107, -0.084, -0.085, -0.084, -0.088};
            int shape_n = 83;
            double hp_max = 100;
            clr->setColorObj(40, 30, 0, 1, hp_max, shape_n, 5, shape_x, shape_y);
            //bool setColorObj(int x, int y, int state, int color, double hp_max, int shape_n, int shape_agl_res, double* shape_x, double* shape_y)
            clr->setScale(40);
            break;
        }
        case 6:{
            double shape_x[] = {-0.401, -0.403, -0.405, -0.406, -0.406, -0.407, -0.405, -0.407, -0.405, -0.407, -0.407, -0.405, -0.397, -0.385, -0.366, -0.342, -0.316, -0.293, -0.253, -0.219, -0.161, -0.118, -0.075, -0.019, 0.026, 0.082, 0.129, 0.182, 0.234, 0.293, 0.327, 0.362, 0.381, 0.392, 0.401, 0.401, 0.403, 0.403, 0.399, 0.401, 0.399, 0.401, 0.404, 0.402, 0.402, 0.402, 0.400, 0.393, 0.383, 0.375, 0.361, 0.339, 0.314, 0.261, 0.221, 0.177, 0.140, 0.098, 0.070, 0.029, 0.008, -0.028, -0.053, -0.083, -0.113, -0.154, -0.189, -0.220, -0.261, -0.291, -0.329, -0.363, -0.382, -0.391, -0.395};
            double shape_y[] = {0.251, 0.181, 0.128, 0.071, 0.022, -0.023, -0.066, -0.106, -0.157, -0.198, -0.238, -0.262, -0.276, -0.286, -0.288, -0.288, -0.288, -0.288, -0.288, -0.287, -0.285, -0.286, -0.285, -0.285, -0.283, -0.280, -0.282, -0.280, -0.283, -0.281, -0.285, -0.281, -0.269, -0.257, -0.240, -0.226, -0.176, -0.125, -0.086, -0.044, 0.002, 0.041, 0.090, 0.128, 0.165, 0.203, 0.235, 0.266, 0.276, 0.285, 0.290, 0.290, 0.291, 0.297, 0.292, 0.291, 0.291, 0.285, 0.290, 0.286, 0.286, 0.286, 0.286, 0.286, 0.286, 0.286, 0.288, 0.291, 0.286, 0.288, 0.290, 0.291, 0.281, 0.274, 0.266};
            int shape_n = 75;
            double hp_max = 100;
            clr->setColorObj(WIN_LENGTH_METER/2, WIN_HEIGHT_METER/2, 0, 1, hp_max, shape_n, 5, shape_x, shape_y);
            //bool setColorObj(int x, int y, int state, int color, double hp_max, int shape_n, int shape_agl_res, double* shape_x, double* shape_y)
            clr->setScale(50);
            break;
        }
        case 101:{
            double shape_x[] = {-0.456, -0.405, -0.308, -0.242, -0.174, 0.113, 0.026, 0.018, -0.060, 0.018, 0.113, 0.253, 0.248, 0.470, 0.478};
            double shape_y[] = {0.139, -0.185, 0.130, -0.178, 0.146, 0.148, 0.146, -0.174, -0.182, -0.176, -0.182, -0.180, 0.156, -0.187, 0.170};
            int shape_n = 15;
            double hp_max = 1;
            clr->setColorObj(WIN_LENGTH_METER/2, WIN_HEIGHT_METER/2, 0, 1, hp_max, shape_n, 5, shape_x, shape_y);
            //bool setColorObj(int x, int y, int state, int color, double hp_max, int shape_n, int shape_agl_res, double* shape_x, double* shape_y)
            clr->setScale(40);
            break;
        }
        case 102:{
            double shape_x[] = {-0.417, -0.438, -0.209, -0.055, -0.093, -0.116, -0.138, -0.151, -0.157, -0.164, -0.155, -0.141, -0.119, -0.097, -0.060, -0.022, 0.007, 0.025, 0.036, 0.038, 0.034, 0.027, 0.022, 0.011, 0.001, -0.012, -0.052, 0.033, 0.087, 0.114, 0.145, 0.171, 0.150, 0.127, 0.112, 0.100, 0.111, 0.127, 0.149, 0.172, 0.194, 0.213, 0.230, 0.248, 0.251, 0.235, 0.210, 0.181, 0.152, 0.136, 0.132, 0.124, 0.111, 0.121, 0.133, 0.146, 0.167, 0.192, 0.221, 0.247, 0.285, 0.317, 0.449, 0.283, 0.287, 0.444, 0.288, 0.283, 0.444};
            double shape_y[] = {0.202, -0.244, -0.248, -0.245, -0.231, -0.213, -0.173, -0.120, -0.069, -0.016, 0.050, 0.103, 0.163, 0.198, 0.213, 0.202, 0.176, 0.136, 0.087, 0.024, -0.034, -0.080, -0.127, -0.166, -0.194, -0.226, -0.247, -0.248, -0.247, -0.248, -0.247, -0.248, -0.242, -0.231, -0.213, -0.192, -0.213, -0.232, -0.241, -0.250, -0.242, -0.220, -0.186, -0.137, -0.109, -0.095, -0.077, -0.059, -0.037, -0.018, -0.001, 0.024, 0.077, 0.093, 0.118, 0.133, 0.149, 0.160, 0.170, 0.174, 0.186, 0.186, 0.180, 0.185, -0.013, -0.016, -0.015, -0.233, -0.238};
            int shape_n = 69;
            double hp_max = 1;
            clr->setColorObj(WIN_LENGTH_METER/2, WIN_HEIGHT_METER/2, 0, 1, hp_max, shape_n, 5, shape_x, shape_y);
            //bool setColorObj(int x, int y, int state, int color, double hp_max, int shape_n, int shape_agl_res, double* shape_x, double* shape_y)
            clr->setScale(40);
            break;
        }
            
        case 100:{
            double shape_x[] = {0.000, 0.007, 0.035, 0.106, 0.207, 0.261, 0.280, 0.243, 0.318, 0.370, 0.393, 0.391, 0.353, 0.313, 0.252, 0.193, 0.170, 0.170, 0.141, 0.108, 0.042, -0.016, -0.057, -0.087, -0.139, -0.214, -0.266, -0.285, -0.273, -0.250, -0.207, -0.299, -0.349, -0.386, -0.396, -0.389, -0.360, -0.313, -0.273, -0.247, -0.203, -0.167, -0.148, -0.153, -0.127, -0.078, -0.026};
            double shape_y[] = {-0.190, -0.240, -0.314, -0.340, -0.327, -0.290, -0.206, -0.142, -0.132, -0.076, -0.005, 0.063, 0.121, 0.150, 0.161, 0.137, 0.119, 0.161, 0.232, 0.261, 0.264, 0.214, 0.156, 0.222, 0.272, 0.274, 0.222, 0.156, 0.100, 0.053, 0.013, 0.008, -0.011, -0.045, -0.079, -0.132, -0.200, -0.235, -0.248, -0.245, -0.222, -0.190, -0.158, -0.227, -0.269, -0.277, -0.248};
            int shape_n = 47;
            double hp_max = 200;
            clr->setColorObj(40, 20, 0, 100, hp_max, shape_n, 5, shape_x, shape_y);
            //bool setColorObj(int x, int y, int state, int color, double hp_max, int shape_n, int shape_agl_res, double* shape_x, double* shape_y)
            clr->setScale(20);
            break;
        }
        default:
            break;
    }
    
}
