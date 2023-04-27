/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream> //I/O Library
#include <cstdlib>  //Random Function
#include <ctime>  //Time to set the random seed
#include <string>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <fstream>
#include <stack>
#include "game.h"
using namespace std;

Game::Game(){
    //Set the random number seed here
    srand(static_cast<unsigned int>(time(0)));
    //Declare all variables for this function
    map<string, int> jobs{{"Assassin", 10},{"Herald", 15},{"Knight", 20},{"Warrior", 25} };
    // Basic(x) is the armor the corresponds with the class
    map<string, int> armor{{"BasicA", 1}, {"BasicH", 1}, {"BasicK", 3}, {"BasicW", 2}};
    map<string, int> weapon{{"BasicA", 3}, {"BasicH", 2}, {"BasicK", 1}, {"BasicW", 2}};
    // To save score
    set<string> save;
    // to save which enemies were beaten
    stack<string> victory;
    //To Obtain save data and store it in a list
    list<string> sdata;
    // name of highscore
    string nhigh; 
    // two converts into int from string
    int c1;
    // temp value that is the size of a string
    int tsize;
    // saves the highest score 
    int chigh=0;
    // save the counter that has the highest
    int scounter;
    //Mob Data
    queue<string> mnames;
    mnames.push("Goblin");
    mnames.push("Skeleton");
    mnames.push("Ogre");
    mnames.push("Skeleton Giant");
    mnames.push("Dragon");
    // 5 Rounds, will stop after 5 rounds 
    queue<int> mhp;
    mhp.push(15);
    mhp.push(20);
    mhp.push(30);
    mhp.push(56);
    mhp.push(100);
    // Mob values 
    queue<int> matk;
    matk.push(1);
    matk.push(2);
    matk.push(5);
    matk.push(10);
    matk.push(15);
    queue<int> mdef;
    mdef.push(0);
    mdef.push(0);
    mdef.push(1);
    mdef.push(2);
    mdef.push(3);
    int userinput=99;
    //Class Choice
    string choicec;
    string cweapon;
    string carmor;
    string name;
    // seperate calculation for later
    int bonus;
    int pattack;
    int mattack;
    // used to save player's orginal hp ( with upgrades)
    int php;
    // declared if your character died or not 
    bool death = false;
    // actions 
    int stam=3;
    // save file
    string temp;
    fstream saves;
    int counter=0;
    saves.open("save.txt", ios::in | ios::out);
    //Before Game Start
    cout << "Start[1] -----------  View Past Scores[2]" << endl;
    while(userinput>2 || userinput <1){
        cin>>userinput;
    }
    // If user wants to view past scores 
    if(userinput == 2){
        while(getline(saves, temp)){
            sdata.push_back(temp);
        }
        for (string x: sdata){
            // specific looks into the file 
            if(counter%2 == 1){
                tsize = x.size();
                temp = x[8];
                for(int i=8; i<tsize; i++){
                    temp+=x[i];
                }
                int c1=stoi(temp);
                // if c1 is higher than chigh than save the counter
                scounter = (c1 > chigh)? counter : scounter;
                // if the current c1 is higher than chigh change it to chigh to c1
                chigh = (c1 > chigh)? c1 : chigh;
                
            }
            counter++;
        }
        counter = 0;
        list<string>::iterator i;
        list<string>::iterator i2;
        // this is shitty but for me the best way to implement it 
        for (string x: sdata){
            if(counter+1 == scounter){
                nhigh = x;
                i = find(sdata.begin(), sdata.end(), nhigh);
                sdata.erase(i);
            }
            if(counter == scounter) {
                i2 = find(sdata.begin(), sdata.end(), x);
                sdata.erase(i2);
            }
            counter++;
        }
        cout << "High Score Player: " << nhigh << endl;
        cout << "Score of the Player: " << chigh << endl;
        cout << "Full List of Player Score from earliest played to latest" << endl;
        for (string x: sdata){
            cout << x <<endl;
        }
    }
    cout << "Enter your name that will be saved in the save file: " << endl;
    cin >> name;
    // resets the future while loop
    userinput = 99;
    //Game start
    cout<< "Welcome to Dark Souls the Board Game Simplified V1" << endl;
    cout<< "This current version does not support score saves" <<endl;
    cout<<"Please Pick your class" << endl;
    cout << "1 for Assassin, 2 for Herald, 3 for Knight, and 4 for Warrior" << endl;
    //To prevent userinput error
    while(userinput>4 || userinput <1){
        cin>>userinput;
    }
    // Memorizes choice 
    choicec = (userinput == 1) ? "Assassin" : (userinput == 2) ? 
        "Herald" : (userinput == 3) ? "Knight"  : "Warrior";
    cweapon = (userinput == 1) ? "BasicA" : (userinput == 2) ? 
        "BasicH" : (userinput == 3) ? "BasicK"  : "BasicW";
    carmor = (userinput == 1) ? "BasicA" : (userinput == 2) ? 
        "BasicH" : (userinput == 3) ? "BasicK"  : "BasicW";
    cout << "You choose " << choicec << endl;
    cout << "Welcome Mr." << choicec <<endl;
    cout<< "You start your journey in the Dungeon and is currently "
        "walking down it "<< endl;
    php = jobs[choicec];
    //if player dies stop the while loop or if game is completed
    while(!(mnames.empty() || death)){
        // Basic Text to introduce the game
        cout << "You encounter a" << mnames.front() << endl;
        cout << "You get into battle position" << endl;
        while(mhp.front()>0){
            cout << "You have " << jobs[choicec] << " hp" << endl;
            cout << mnames.front() << "has " << mhp.front() << " hp" << endl;
            cout << mnames.front() << "has " << matk.front() << " atk" << endl;
            cout << mnames.front() << "has " << mdef.front() << " def" << endl;
            cout << "You have " << stam << "actions" << endl;
            cout << "Press 1 to do a powerful attack(1 Action), "
                    "Press 2(Gain 1 Action(MAX3) and Defense) to Defense, "
                    "Press 3 to Quick Attack(0 Actions Cost or Gain" << endl;
            cin >> userinput;
            if(userinput>0 && userinput<4){
                cout << "The " << mnames.front() << "attacks" << endl;
                //If the user defends use up a bonus
                bonus = (userinput == 2)? 1: 0;
                // basic calculation base on random number generator
                mattack = dmgcalc(matk.front() ,armor[carmor], 0 ,bonus);
                //Outputs result of the attack
                cout << "The " << mnames.front() << " deals " << mattack << 
                        " damage" <<endl;
                jobs[choicec] -= mattack;
                // player attacks
                bonus = (userinput == 1 && stam>0)? 2: 0;
                stam -= (userinput == 1 && stam>0)? 1: 0; 
                pattack = dmgcalc(weapon[cweapon], mdef.front(), bonus, 0);
                cout << "You done " << pattack << " damage" << endl;
                mhp.front()-=pattack;
                
                
                
            }else{
                cout<<"You enter an incorrect input you did nothing " <<endl;
                bonus = (userinput == 2)? 1: 0;
                // basic calculation base on random number generator
                mattack = dmgcalc(matk.front() ,armor[carmor], 0 ,bonus);
                //Outputs result of the attack
                cout << "The " << mnames.front() << " deals " << mattack << 
                        " damage" <<endl;
                jobs[choicec] -= mattack;
            }
            if(mhp.front() == 0){
                cout << " You have slained the " << mnames.front() << endl;
                victory.push(mnames.front());
            }
            if(jobs[choicec]<1){
                cout << " You have died from your injuries " << endl;
                death = true;
                mhp.front()=0;
            }
            jobs[choicec] = php;
        }
        mhp.pop();
        mnames.pop();
        matk.pop();
        mdef.pop();
    }
    //check for victory 
    if(victory.top() == "Dragon"){
        cout << "Congrats, You have beaten the game" <<endl;
    }
    //Save
    int score = victory.size();
    saves << "Name: " << name << endl;
    saves << "Score: " << score << endl;
}
int Game::diceroll(int type, int bonus){
    int num=0;
    // Represent what Number on the dice it is 
    int dice = rand() % 6; 
    if(type == 1){
        num = (dice == 0)? 0 : (dice == 1)? 0 : (dice == 2)? 1 : (dice == 3)? 1 
                : (dice == 4)? 1 : (dice == 5)? 2 : 2;
    } 
    if(type == 2){
        num = (dice == 0)? 0 : (dice == 1)? 1 : (dice == 2)? 1 : (dice == 3)? 2 
                : (dice == 4)? 2 : (dice == 5)? 3 : 3;
    } 
    if(type == 3){
        num = (dice == 0)? 0 : (dice == 1)? 0 : (dice == 2)? 2 : (dice == 3)? 2 
                : (dice== 4)? 3 : (dice == 5)? 4 : 4;
    } 
    cout << "You rolled a " << num << endl;
    cout << "Adding Bonus of " << bonus << endl;
    num += bonus;
    return num;
}
int Game::dmgcalc(int atk, int def, int bonus1, int bonus2){
    int vatk = diceroll(atk, bonus1);
    int vdef = diceroll(def, bonus2);
    int total = vatk - def;
    return total;
}