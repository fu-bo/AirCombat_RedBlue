#include "Bullet.hpp"

bool Bullet::shoot(double x, double y, int type){ //type = 0
    bool flag_shoot = false;
    if(state_ == 0){
        x_ = x;
        y_ = y;
        hp_ = hp_max_;
        state_ = 1;
        type_ = type;
        flag_shoot = true;
    }
    return flag_shoot;
}
int Bullet::move(double dt){
    if(state_ > 0){
        switch (type_) {
            case 1:
                fall(dt);
                break;
            default:
                x_ += vx_ * dt;
                y_ += vy_ * dt;
                break;
        }
    }
    if(!isInside(WIN_MARGIN_METER)){
        state_ = 0;
    }
    return state_;
}

