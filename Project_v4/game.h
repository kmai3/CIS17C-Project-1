/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game.h
 * Author: xWing
 *
 * Created on April 26, 2023, 3:23 PM
 */
#ifndef GAME_H
#define GAME_H
#include <string>
using namespace std;
class Game{
private:
    int diceroll(int, int);  
    int dmgcalc(int, int, int, int );
    bool hardmode(int &);
    bool medmode(int &);
    bool easymode(int &);
    // for hard mode specifically 
    string weaponchoice(int, int&);
    int correction(int, int);
    int hdmgcalc(int, int, int, int , int);
    void special(int ,int &, int &, int, int &, int &);
public:
    Game();
    // This may not be needed
};


#endif /* GAME_H */

