#include <time.h>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "Common.hpp"
#include "StringPaser.hpp"
#include "Colored.hpp"
#include "ColorObj.hpp"
#include "ColorCircle.hpp"
#include "ColorQuad.hpp"
#include "Bullet.hpp"
#include "ColorFunction.hpp"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

//Copyright Credit to the Sound Data
//These are copyright free under "Personal Use" or "Attribution 3.0".

//Click-SoundBible.com-1387633738            http://soundbible.com/783-Click.html        Attribution 3.0
//Click2-Sebastian-759472264.wav            http://soundbible.com/1705-Click2.html        Attribution 3.0
//Bomb 2-SoundBible.com-953367492.wav        http://soundbible.com/476-Bomb-2.html        Personal Use Only
//Water Splash-SoundBible.com-800223477.wav    http://soundbible.com/1460-Water-Splash.html    Attribution 3.0
//Upper Cut-SoundBible.com-1272257235.wav        http://soundbible.com/993-Upper-Cut.html    Attribution 3.0
//Ta Da-SoundBible.com-1884170640            http://soundbible.com/1003-Ta-Da.html        Attribution 3.0

const int ba_num = 50;
const int ra_num = 500;
const int r2_num = 24;
const int r3_num = 2;
const int w1_num = 5;
const int w2_num = 5;
const int w3_num = 10;

ColorObj* r1 = new ColorObj();
ColorObj* r2[r2_num];
ColorObj* r3[r3_num];

ColorObj* b1 = new ColorObj();
Bullet* ba[ba_num];
Bullet* ra[ra_num];

ColorObj* w1[w1_num];
ColorObj* w2[w2_num];
ColorCircle* w3[w3_num];



//ColorQuad* clr2 = new ColorQuad();


void Render(void *)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    for(int i = 0; i < w1_num; i++){
        w1[i]->show();
    }
    
    for(int i = 0; i < r2_num; i++){
        r2[i]->show();
    }
    for(int i = 0; i < ra_num; i++){
        ra[i]->show();
    }
    r1->show();
    r3[0]->showLine(false);
    r3[1]->showLine(false);
    
    b1->show();
    for(int i = 0; i < ba_num; i++){
        ba[i]->show();
    }
    
    for(int i = 0; i < w2_num; i++){
        w2[i]->show();
    }
    for(int i = 0; i < w3_num; i++){
        w3[i]->show();
    }
    
    FsSwapBuffers();
}

void Int2Char(int x, char c[], int maxlen){
    if(maxlen <= 1){
        return;
    }
    if(x == 0){
        c[0] = '0';
        c[1] = 0;
    }
    int x_content[30];
    int num = 0;
    while(x != 0){
        x_content[num] = x % 10;
        x /= 10;
        num++;
    }
    int num_copy = num;
    if(num_copy > maxlen - 1){
        num_copy = maxlen - 1;
    }
    for(int i = 0; i < num_copy; i++){
        c[num_copy - 1 - i] = '0' + x_content[i];
    }
    c[num_copy] = 0;
}


int main(void)
{
    int start_time = (int)time(nullptr);
    
    
    thesrand((int)time(nullptr));
    // thesrand(13229837);
    bool terminate = false;
    
    
    for(int i = 0; i < r3_num; i++){
        r3[i] = new ColorObj();
    }
    ColorFunction::setPlane(101, r3[0]);
    ColorFunction::setPlane(102, r3[1]);
    ColorFunction::setPlane(5, r1);
    r1->setHpMax1(80);
    
    ColorFunction::setPlane(1, b1);
    b1->setState(1);
    b1->setV(40);
    
    bool flag_sound = true;
    
    for(int i = 0; i < w1_num; i++){
        w1[i] = new ColorObj();
        ColorFunction::setPlane(100, w1[i]);
        w1[i]->setScale(20);
        w1[i]->setHpMax1(30);
    }
    for(int i = 0; i < w2_num; i++){
        w2[i] = new ColorObj();
        ColorFunction::setPlane(1, w2[i]);
        w2[i]->setScale(3);
        w2[i]->setXY(WIN_LENGTH_METER - 2*(((double)i)+1), WIN_HEIGHT_METER-2);
    }
    for(int i = 0; i < w3_num; i++){
        w3[i] = new ColorCircle();
        w3[i]->setColorCircle(2*(((double)i)+1), WIN_HEIGHT_METER-2, 0, -1, 2, 1, 12);
        w3[i]->setScale(1);
        w3[i]->setHp(1);
    }
    
    for(int i = 0; i < r2_num; i++){
        r2[i] = new ColorObj();
        if(i < r2_num / 3 * 1){
            ColorFunction::setPlane(3, r2[i]);
        }
        else if(i < r2_num / 3 * 2){
            ColorFunction::setPlane(4, r2[i]);
        }
        else if(i < r2_num-1){
            ColorFunction::setPlane(5, r2[i]);
            r2[i]->setScale(20);
            r2[i]->setHpMax1(30);
        }
        else{
            ColorFunction::setPlane(6, r2[i]);
        }
    }
    
    for(int i = 0; i < ba_num; i++){
        ba[i] = new Bullet();
        ba[i]->setColorCircle(40, 20, 0, -1, 1, 0.6, 12);
        ba[i]->setV(60);
        ba[i]->setVxy(0, 60);
    }
    for(int i = 0; i < ra_num; i++){
        ra[i] = new Bullet();
        ra[i]->setColorCircle(40, 20, 0, 1, 1, 0.6, 12);
        ra[i]->setV(60);
        ra[i]->setVxy(0, -60);
    }
    
    YsSoundPlayer::SoundData sound_shoot_b; // shoot
    YsSoundPlayer::SoundData sound_shoot_b1; // big shoot
    YsSoundPlayer::SoundData sound_shoot_r; // shoot
    YsSoundPlayer::SoundData sound_shoot_r1; // throw
    YsSoundPlayer::SoundData sound_shoot_r2; // explode
    YsSoundPlayer::SoundData sound_win; // win
    
    sound_shoot_b.LoadWav("data/Click-SoundBible.com-1387633738.wav"); // Blop-Mark_DiAngelo-79054334.wav
    sound_shoot_b1.LoadWav("data/Water Splash-SoundBible.com-800223477.wav");
    // sound_shoot_r.LoadWav("data/karate_kid_punch-Mike_Koenig-732906088.wav");
    sound_shoot_r.LoadWav("data/Click2-Sebastian-759472264.wav");
    // sound_shoot_r.LoadWav("data/Click2-Sebastian-759472264.wav");
    // sound_shoot_r.LoadWav("data/Fuzzy Beep-SoundBible.com-1580329899.wav");
    
    sound_shoot_r1.LoadWav("data/Upper Cut-SoundBible.com-1272257235.wav");
    sound_shoot_r2.LoadWav("data/Bomb 2-SoundBible.com-953367492.wav");
    sound_win.LoadWav("data/Ta Da-SoundBible.com-1884170640.wav");
    
    YsSoundPlayer sound_player;
    sound_player.Start();
    
    int flag_write = -1;
    FILE *fp;
    if(flag_write == 1){
        fp = fopen("target_file.txt", "w");
    }
    else if (flag_write == 0){
        fp = fopen("target_file.txt", "r");
    }
    const int key_num = 7;
    StringPaser paser;
    int word_num = 0;
    const int str_max = 256;
    
    
    int count_life = 3;
    bool flag_life = true;
    bool flag_revive = false;
    int life_time = 0;
    
    //    int terminate_time = 0;
    //    int terminate_now = 0;
    bool flag_final_start = false;
    
    int round = 0;
    //const int max_round = 3;
    int count = 0;
    int r1_count = 1;
    int count_prev = 0;
    double dt = 0.01;
    double hp_minus = 1;
    double hp_minustime = 4;
    
    int b1_shoot_time = 300;
    int r2_shoot_time = 1000;
    //int r1_shoot_time = 500;
    int r1_shoot_gap = 5000;
    double r1_shoot_agl = 0;
    double r2_shoot_agl = 0;
    double r2_v = 20;
    double r1_v = 20;
    
    double cloud_time = 2000;
    double cloud_time_prev = 0;
    
    int count_large = 10;
    bool flag_inside = false;
    int flag_win = -1;
    
    long long int time_start = FsSubSecondTimer();
    FsOpenWindow(0,0,WIN_LENGTH,WIN_HEIGHT,1);
    FsRegisterOnPaintCallBack(Render, nullptr);
    
    int index_time = 0;
    while(true!=terminate)
    {
        int key_list[key_num] = {0};
        for(int i = 0; i < key_num; i++){
            key_list[0] = 0;
        }
        
        FsPollDevice();
        auto key=FsInkey();
        
        bool flag_key_terminate = FSKEY_ESC==key;
        bool flag_key_up = 0!=FsGetKeyState(FSKEY_UP);
        bool flag_key_down = 0!=FsGetKeyState(FSKEY_DOWN);
        bool flag_key_right = 0!=FsGetKeyState(FSKEY_RIGHT);
        bool flag_key_left = 0!=FsGetKeyState(FSKEY_LEFT);
        bool flag_key_space = 0!=FsGetKeyState(FSKEY_SPACE);
        bool flag_key_a = 0!=FsGetKeyState(FSKEY_A);
        
        if(flag_write == 0){
//            while(true){
                word_num = paser.GetString(str_max, fp);
//            printf("(%d, %d)\n", index_time, paser.GetInt(0));
//                if(index_time <= paser.GetInt(0)){
//                    pr
//                    break;
//                }
//            }
            
            if(word_num == 0){
                break;
            }
            if(word_num >= 8)
            flag_key_terminate = paser.GetInt(1) == 1;
            flag_key_up = paser.GetInt(2) == 1;
            flag_key_down = paser.GetInt(3) == 1;
            flag_key_right = paser.GetInt(4) == 1;
            flag_key_left = paser.GetInt(5) == 1;
            flag_key_space = paser.GetInt(6) == 1;
            flag_key_a = paser.GetInt(7) == 1;
        }
        
        if(flag_key_terminate || FSKEY_ESC==key ){
            terminate = true;
            key_list[0] = 1;
        }
        
        if(flag_key_up){
            b1->moveUp(dt, true);
            key_list[1] = 1;
        }
        if(flag_key_down){
            b1->moveUp(dt, false);
            key_list[2] = 1;
        }
        if(flag_key_right){
            b1->moveRight(dt, true);
            key_list[3] = 1;
        }
        if(flag_key_left){
            b1->moveRight(dt, false);
            key_list[4] = 1;
        }
        if(flag_key_space){
            key_list[5] = 1;
            int time_curr = (int) (FsSubSecondTimer() - time_start);
            if(time_curr - b1->_time_prev() > b1_shoot_time && b1->_state()>0){
                for(int i = 0; i < ba_num-1; i++){
                    if(ba[i]->shoot(b1->_x(), b1->_y() + 5)){
                        if(flag_sound){
                            sound_player.Stop(sound_shoot_b);
                            sound_player.PlayOneShot(sound_shoot_b);
                        }
                        break;
                    }
                }
                b1->setTimePrev(time_curr);
            }
            
        }
        if(flag_key_a){
            key_list[6] = 1;
            if(b1->_state() > 0){
                if(count_large > 0 && ba[ba_num-1]->_state() == 0){
                    int time_curr = (int) (FsSubSecondTimer() - time_start);
                    if(time_curr - b1->_time_prev() > b1_shoot_time){
                        ba[ba_num-1]->setColorCircle(40, 20, 0, -1, 30, 10, 36);
                        ba[ba_num-1]->setV(20);
                        ba[ba_num-1]->setVxy(0, 20);
                        ba[ba_num-1]->shoot(b1->_x(), b1->_y() + 10);
                        count_large -= 1;
                        b1->setTimePrev(time_curr);
                        if(flag_sound){
                            sound_player.Stop(sound_shoot_b1);
                            sound_player.PlayOneShot(sound_shoot_b1);
                        }
                    }
                }
            }
        }
        //        if(0!=FsGetKeyState(FSKEY_1)){
        //            b1->setHp(b1->_hp()-1);
        //        }
        //        if(0!=FsGetKeyState(FSKEY_2)){
        //            b1->setHp(b1->_hp()+1);
        //        }
        
        if(flag_write == 1){
            fprintf(fp, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", index_time, key_list[0], key_list[1], key_list[2], key_list[3], key_list[4], key_list[5], key_list[6]);
        }
        
        
        int cloud_time_curr = (int) (FsSubSecondTimer() - time_start);
        if(cloud_time_curr - cloud_time_prev > cloud_time){
            if(Colored::myRand(0, 1) > 0.5){
                for(int i = 0; i < w1_num; i++){
                    if(w1[i]->_state() == 0){
                        ColorFunction::setPlane(100, w1[i]);
                        w1[i]->randomShape();
                        w1[i]->setVxy(0, -15);
                        w1[i]->setXY(WIN_LENGTH_METER * Colored::myRand(-0.2, 1.2), WIN_HEIGHT_METER + 10);
                        w1[i]->setState(1);
                        break;
                    }
                }
            }
            cloud_time_prev = cloud_time_curr;
        }
        for(int i = 0; i < w1_num; i++){
            if(w1[i]->_state() > 0){
                w1[i]->move(dt);
            }
        }
        
        
        if(count == 0){
            if(round == 0){
                for(int i = 0; i < r2_num/3 * 1; i++){
                    r2[i]->setXY(Colored::myRand(10, WIN_LENGTH_METER-10), Colored::myRand(WIN_HEIGHT_METER, WIN_HEIGHT_METER-5));
                    r2[i]->setV(20);
                    r2[i]->setHp(0,1);
                    r2[i]->setState(1);
                    count++;
                }
                round++;
            }
            else if(round == 1){
                for(int i = r2_num/3*1; i < r2_num/3*2; i++){
                    r2[i]->setXY(Colored::myRand(WIN_LENGTH_METER, WIN_LENGTH_METER+5), Colored::myRand(50, WIN_HEIGHT_METER-5));
                    r2[i]->setV(20);
                    r2[i]->setHp(0,1);
                    r2[i]->setState(1);
                    count++;
                }
                round++;
            }
            else if(round == 2){
                for(int i = r2_num/3-2; i < r2_num/3+2; i++){
                    r2[i]->setXY(Colored::myRand(WIN_LENGTH_METER, WIN_LENGTH_METER+5), Colored::myRand(50, WIN_HEIGHT_METER-5));
                    r2[i]->setV(20);
                    r2[i]->setHp(0,1);
                    r2[i]->setState(1);
                    count++;
                }
                r1->setXY(WIN_LENGTH_METER/2, Colored::myRand(WIN_HEIGHT_METER, WIN_HEIGHT_METER-5));
                r1->setV(20);
                r1->setHp(0,1);
                r1->setState(1);
                count++;
                round++;
            }
        }
        
        if(true){
            if(round == 1){
                for(int i = 0; i < r2_num/3; i++){
                    if(!r2[i]->isInside(0)){
                        r2[i]->moveUp(dt, false);
                    }
                    else{
                        r2[i]->moveRandom(dt);
                        int time_curr = (int) (FsSubSecondTimer() - time_start);
                        if(time_curr - r2[i]->_time_prev() > r2_shoot_time && r2[i]->_state() > 0){
                            if(Colored::myRand(0, 1) > 0.6){
                                //                                for(int j = 0; j < ra_num; j++){
                                //                                    if(ra[j]->_state() == 0){
                                //                                        ra[j]->setV(r2_v);
                                //                                        ra[j]->setVxy(0, -r2_v);
                                //                                        ra[j]->shoot(r2[i]->_x(), r2[i]->_y() - 5);
                                //                                        break;
                                //                                    }
                                //                                }
                                ColorFunction::fire(r2[i], ra, ra_num, r2[i]->_x(), r2[i]->_y() - 5, 0, -r2_v);
                                if(flag_sound){
                                    sound_player.PlayOneShot(sound_shoot_r);
                                }
                            }
                            r2[i]->setTimePrev(time_curr);
                        }
                    }
                }
            }
            else if(round == 2){
                for(int i = r2_num/3*1; i < r2_num/3*2; i++){
                    if(!r2[i]->isInside(0)){
                        r2[i]->moveRight(dt, false);
                    }
                    else{
                        r2[i]->moveRandom(dt, 1);
                        int time_curr = (int) (FsSubSecondTimer() - time_start);
                        if(time_curr - r2[i]->_time_prev() > r2_shoot_time && r2[i]->_state() > 0){
                            if(Colored::myRand(0, 1) > 0.2){
                                ColorFunction::fire(r2[i], ra, ra_num, r2[i]->_x(), r2[i]->_y() - 5, 0, -r2_v);
                                if(flag_sound){
                                    sound_player.PlayOneShot(sound_shoot_r);
                                }
                            }
                            r2[i]->setTimePrev(time_curr);
                        }
                    }
                }
            }
            else if(round <= 4){
                for(int i = 0; i < r2_num/3*2; i++){
                    if(r2[i]->_state() > 0){
                        if(!r2[i]->isInside(0)){
                            r2[i]->moveRight(dt, false);
                        }
                        else{
                            r2[i]->moveRandom(dt, 1);
                            int time_curr = (int) (FsSubSecondTimer() - time_start);
                            if(time_curr - r2[i]->_time_prev() > r2_shoot_time && r2[i]->_state() > 0){
                                if(Colored::myRand(0, 1) > 0.6){
                                    ColorFunction::fire(r2[i], ra, ra_num, r2[i]->_x(), r2[i]->_y() - 5, 0, -r2_v);
                                    if(flag_sound){
                                        //sound_player.Stop(sound_shoot_r);
                                        sound_player.PlayOneShot(sound_shoot_r);
                                    }
                                }
                                r2[i]->setTimePrev(time_curr);
                            }
                        }
                    }
                }
                for(int i = r2_num/3*2; i < r2_num/3*2 + 4; i++){
                    if(r2[i]->_state() > 0){
                        r2[i]->moveRandom(dt, 0);
                        int time_curr = (int) (FsSubSecondTimer() - time_start);
                        int plane_id = i%4;
                        if (plane_id == 0){
                            if(time_curr - r2[i]->_time_prev() > 500){
                                if (therand()%4==0){
                                    ColorFunction::fire(r2[i], ra, ra_num, r2[i]->_x(), r2[i]->_y(), 0, -r1_v, 2, 2);
                                    if(flag_sound){
                                        sound_player.Stop(sound_shoot_r);
                                        sound_player.PlayOneShot(sound_shoot_r);
                                    }
                                }
                                r2[i]->setTimePrev(time_curr);
                            }
                        }
                        else if (plane_id == 1){
                            if(time_curr - r2[i]->_time_prev() > 1000){
                                if (therand()%4==0){
                                    ColorFunction::fire(r2[i], ra, ra_num, r2[i]->_x(), r2[i]->_y(), r1_v, 0, 1);
                                    if(flag_sound){
                                        sound_player.Stop(sound_shoot_r);
                                        sound_player.PlayOneShot(sound_shoot_r);
                                    }
                                }
                                r2[i]->setTimePrev(time_curr);
                            }
                        }
                        else if (plane_id == 2){
                            if(time_curr - r2[i]->_time_prev() > 3000){
                                if (therand()%4==0){
                                    ColorFunction::fire(r2[i], ra, ra_num, r2[i]->_x(), r2[i]->_y(), r1_v/4, 0, 3, 8);
                                    if(flag_sound){
                                        sound_player.Stop(sound_shoot_r);
                                        sound_player.PlayOneShot(sound_shoot_r1);
                                    }
                                }
                                r2[i]->setTimePrev(time_curr);
                            }
                        }
                        else if(plane_id == 3){
                            if(time_curr - r2[i]->_time_prev() > 400){
                                if (therand()%4<=4){
                                    ColorFunction::fire(r2[i], ra, ra_num, r2[i]->_x(), r2[i]->_y(), 10, r2_shoot_agl, 1, 4);
                                    r2_shoot_agl += 5;
                                    if(flag_sound){
                                        sound_player.Stop(sound_shoot_r);
                                        sound_player.PlayOneShot(sound_shoot_r);
                                    }
                                }
                                r2[i]->setTimePrev(time_curr);
                            }
                        }
                    }
                }
                if(r1->_state() > 0){
                    if( r1->_y() > WIN_HEIGHT_METER - 25 && !flag_inside){
                        r1->moveUp(dt, false);
                    }
                    else{
                        r1->moveRandom(dt);
                        flag_inside = true;
                        int time_curr = (int) (FsSubSecondTimer() - time_start);
                        int r1_time = (time_curr / r1_shoot_gap) % 5 ;
                        if (r1_time <= 0){
                            if(time_curr - r1->_time_prev() > 200 && r1->_state() > 0){
                                ColorFunction::fire(r1, ra, ra_num, r1->_x(), r1->_y(), 0, -r1_v, 2, 2);
                                r1->setTimePrev(time_curr);
                                if(flag_sound){
                                    sound_player.Stop(sound_shoot_r);
                                    sound_player.PlayOneShot(sound_shoot_r);
                                }
                            }
                        }
                        else if (r1_time <= 1){
                            if(time_curr - r1->_time_prev() > 1000 && r1->_state() > 0){
                                ColorFunction::fire(r1, ra, ra_num, r1->_x(), r1->_y(), r1_v, 0, 1);
                                r1->setTimePrev(time_curr);
                                if(flag_sound){
                                    sound_player.Stop(sound_shoot_r);
                                    sound_player.PlayOneShot(sound_shoot_r);
                                }
                            }
                        }
                        else if (r1_time <= 3){
                            if(time_curr - r1->_time_prev() > 3000 && r1->_state() > 0){
                                ColorFunction::fire(r1, ra, ra_num, r1->_x(), r1->_y(), r1_v/4, 0, 3, 12);
                                r1->setTimePrev(time_curr);
                                if(flag_sound){
                                    sound_player.Stop(sound_shoot_r);
                                    sound_player.PlayOneShot(sound_shoot_r1);
                                }
                            }
                        }
                        else if(r1_time <= 4){
                            if(time_curr - r1->_time_prev() > 200 && r1->_state() > 0){
                                ColorFunction::fire(r1, ra, ra_num, r1->_x(), r1->_y(), 20, r1_shoot_agl, 1, 8);
                                r1_shoot_agl += 5;
                                r1->setTimePrev(time_curr);
                                if(flag_sound){
                                    sound_player.Stop(sound_shoot_r);
                                    sound_player.PlayOneShot(sound_shoot_r);
                                }
                            }
                        }
                    }
                }
                else{
                    if(r1_count > 0){
                        round++;
                        ColorFunction::fire(r1, ra, ra_num, r1->_x(), r1->_y(), r1_v/2, 0, 4, 50);
                        if(flag_sound){
                            sound_player.Stop(sound_shoot_r2);
                            sound_player.PlayOneShot(sound_shoot_r2);
                        }
                        r1_count -= 1;
                        for(int i = r2_num/3*2; i < r2_num/3*2+4; i++){
                            if(i%4==0){
                                r2[i]->setXY(r1->_x()-3, r1->_y()-3);
                            }
                            else if(i%4==1){
                                r2[i]->setXY(r1->_x()-3, r1->_y()+3);
                            }
                            else if(i%4==2){
                                r2[i]->setXY(r1->_x()+3, r1->_y()-3);
                            }
                            else if(i%4==3){
                                r2[i]->setXY(r1->_x()+3, r1->_y()+3);
                            }
                            r2[i]->setV(20);
                            r2[i]->setHp(0,1);
                            r2[i]->setState(1);
                            count++;
                        }
                    }
                }
            }
            else if(round == 5){
                if(r2[r2_num-1]->_state() > 0 && b1->_state() > 0){
                    int time_curr = (int) (FsSubSecondTimer() - time_start);
                    if(time_curr - r2[r2_num-1]->_time_prev() > 5000){
                        ColorFunction::fire(r2[r2_num-1], ra, ra_num, r2[r2_num-1]->_x(), r2[r2_num-1]->_y(), r1_v/2, 0, 4, 50);
                        r2[r2_num-1]->setTimePrev(time_curr);
                        if(flag_sound){
                            sound_player.Stop(sound_shoot_r2);
                            sound_player.PlayOneShot(sound_shoot_r2);
                        }
                    }
                }
            }
        }
        
        
        for(int i = 0; i < ba_num; i++){
            ba[i]->move(dt);
        }
        for(int i = 0; i < ra_num; i++){
            ra[i]->move(dt);
        }
        
        if(!flag_final_start && r2[r2_num-1]->_state()>0){
            if(r2[r2_num-1]->_hp() < 0.8 * r2[r2_num-1]->_hp_max1()){
                round++;
                flag_final_start = true;
            }
        }
        
        // Show life and power
        ColorFunction::showLife(count_life, count_large, w2_num, w3_num, w2, w3);
        
        
        // Check collision
        
        // Plane with Plane
        if(ColorFunction::checkCollision(r1, b1) ){
            double hp_min = Colored::getMinHp(r1, b1, hp_minustime * dt);
            r1->minusHp(hp_min);
            b1->minusHp(hp_min);
        }
        for(int i = 0; i < r2_num; i++){
            if(ColorFunction::checkCollision(r2[i], b1) ){
                double hp_min = Colored::getMinHp(r2[i], b1, hp_minustime * dt);
                r2[i]->minusHp(hp_min);
                b1->minusHp(hp_min);
            }
        }
        
        
        // Bullet with Plane
        for(int i = 0; i < ba_num; i++){
            if(ColorFunction::checkCollision(r1, ba[i]) ){
                double hp_min = Colored::getMinHp(r1, ba[i], hp_minus);
                //                if(i < ba_num-1){
                //                    hp_min = Colored::getMinHp(r1, ba[i], hp_minus);
                //                }
                //                else{
                //                    hp_min = Colored::getMinHp(r1, ba[i], 2 * hp_minustime * dt);
                //                }
                r1->minusHp(hp_min);
                ba[i]->minusHp(hp_min);
            }
        }
        for(int i = 0; i < ba_num; i++){
            if(ba[i]->_state() > 0){
                for(int j = 0; j < r2_num; j++){
                    if(ColorFunction::checkCollision(r2[j], ba[i]) ){
                        double hp_min = Colored::getMinHp(r2[j], ba[i], hp_minus);
                        //                    if(i < ba_num-1){
                        //                        hp_min = Colored::getMinHp(r2[j], ba[i], hp_minus);
                        //                    }
                        //                    else{
                        //                        hp_min = Colored::getMinHp(r2[j], ba[i], 2 * hp_minustime * dt);
                        //                    }
                        
                        r2[j]->minusHp(hp_min);
                        ba[i]->minusHp(hp_min);
                        break;
                    }
                }
            }
        }
        for(int i = 0; i < ra_num; i++){
            if(ra[i]->_state() > 0){
                if(ColorFunction::checkCollision(b1, ra[i]) ){
                    double hp_min = Colored::getMinHp(b1, ra[i], hp_minus);
                    b1->minusHp(hp_min);
                    ra[i]->minusHp(hp_min);
                }
            }
        }
        
        // Bullet with Bullet
        for(int i = 0; i < ba_num; i++){
            for(int j = 0; j < ra_num; j++){
                if(ColorFunction::checkCollision(ba[i], ra[j]) ){
                    double hp_min = Colored::getMinHp(ba[i], ra[j], hp_minus);
                    ba[i]->minusHp(hp_min);
                    ra[j]->minusHp(hp_min);
                }
            }
        }
        
        count = ((int) (r1->_state() > 0));
        for(int i = 0; i < r2_num; i++){
            count += ((int) (r2[i]->_state() > 0));
        }
        
        printf("Current target number: %d\n", count);
        count_prev = count;
        
        if(flag_life){
            if(b1->_state() == 0){
                flag_life = false;
                life_time = (int) (FsSubSecondTimer() - time_start);
            }
            if(flag_revive){
                if(b1->_hp() < b1->_hp_max1()){
                    b1->setHp(b1->_hp()+0.1);
                }
                else{
                    flag_revive = 0;
                }
            }
            
        }
        else{
            if(count_life > 0){
                int life_time_now = (int) (FsSubSecondTimer() - time_start);
                if(life_time_now - life_time > 3000){
                    flag_revive = true;
                    flag_life = true;
                    count_life -= 1;
                    b1->setHp(b1->_hp_max1()/2);
                    b1->setState(1);
                    b1->setXY(20, 10);
                }
            }
        }
        
        
        
        if(round >=4 && count == 0){
            r3[0]->setState(1);
            r3[1]->setState(0);
            if(!flag_final_start){
                r2[r2_num-1]->setState(1);
                count++;
            }
            if(flag_win != 1){
                flag_win = 1;
                if(flag_sound){
                    sound_player.Stop(sound_win);
                    sound_player.PlayOneShot(sound_win);
                }
            }
            //printf("\n\nMission completed!\n");
            //break;
        }
        if(b1->_state()==0 && count_life ==0){
            r3[0]->setState(0);
            r3[1]->setState(1);
            if(flag_win != 0){
                flag_win = 0;
                if(flag_sound){
                    sound_player.Stop(sound_win);
                    sound_player.PlayOneShot(sound_win);
                }
            }
            //printf("\n\nGame over!\n");
            //break;
        }
        if(flag_sound){
            sound_player.KeepPlaying();
        }
        FsPushOnPaintEvent();
        FsSleep(10);
        index_time++;
    }
    
    FsCloseWindow();
    
    sound_player.End();
    
    if(flag_write <= 1){
        fclose(fp);
    }
    
    delete r1;
    for(int i = 0; i< r3_num; i++){
        delete r3[i];
    }
    for(int i = 0; i < r2_num; i++){
        delete r2[i];
    }
    delete b1;
    for(int i = 0; i < ba_num; i++){
        delete ba[i];
    }
    for(int i = 0; i < ra_num; i++){
        delete ra[i];
    }
    
    for(int i = 0; i < w1_num; i++){
        delete w1[i];
    }
    for(int i = 0; i < w2_num; i++){
        delete w2[i];
    }
    for(int i = 0; i < w3_num; i++){
        delete w3[i];
    }
    
    return 0;
}

