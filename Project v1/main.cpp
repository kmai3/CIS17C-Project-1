/* 
 * File:   main.cpp
 * Author: 
 * Created on June 23, 2020, 8:39 AM
 * Purpose: Template which is to be copied
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
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes
int diceroll(int, int);  
int dmgcalc(int, int, int, int );
//Execution of Code Begins here
int main(int argc, char** argv) {
    //Set the random number seed here
    srand(static_cast<unsigned int>(time(0)));
    
    
    //Declare all variables for this function
    map<string, int> jobs{{"Assassin", 10},{"Herald", 15},{"Knight", 20},{"Warrior", 25} };
    // Basic(x) is the armor the corresponds with the class
    map<string, int> armor{{"BasicA", 1}, {"BasicH", 1}, {"BasicK", 3}, {"BasicW", 2}};
    map<string, int> weapon{{"BasicA", 3}, {"BasicH", 2}, {"BasicK", 1}, {"BasicW", 2}};
    set<string> victory;
    queue<string> mnames;
    mnames.push("Goblin");
    mnames.push("Skeleton");
    mnames.push("Ogre");
    mnames.push("Skeleton Giant");
    mnames.push("Dragon");
    // 5 Rounds will stop after 5 rounds 
    queue<int> mhp;
    mhp.push(15);
    mhp.push(20);
    mhp.push(30);
    mhp.push(56);
    mhp.push(100);
    
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
    //Game start
    // Basic Text to introduce the game
    cout << "Choose to Start Game or View High Scores, " << endl;
    cout<< "Welcome to Dark Souls the Board Game Simplified V2" << endl;
    cout<< "This current version does not support score saves" <<endl;
        
    cout<<"Please Pick your class" << endl;
    cout << "1 for Assassin, 2 for Herald, 3 for Knight, and 4 for Warrior" << endl;
    //Makes sure to get a valid answer
    while(userinput>4 || userinput <1){
        cin>>userinput;
    }
    php = jobs[choicec];
    // Converts Class Choice to String for Map
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
    //if player dies stop the while loop or if game is completed
    while(!mnames.empty() || !death){
        cout << "You encounter a" << mnames.front() << endl;
        cout << "You get into battle position" << endl;
        
        while(mhp.front()!=0){
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
            }
            if(jobs[choicec]<1){
                cout << " You have died from your injuries " << endl;
                death = true;
                mhp.front()=0;
            }
        }
        mhp.pop();
        mnames.pop();
        matk.pop();
        mdef.pop();
        //Score System
        
    }

    //Exit stage right
    return 0;
}
// this calculates pratically everything taking damage, doing damage, all base on dice roll
int diceroll(int type, int bonus){
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
    num += bonus;
    return num;
}
int dmgcalc(int atk, int def, int bonus1, int bonus2){
    int vatk = diceroll(atk, bonus1);
    int vdef = diceroll(def, bonus2);
    int total = vatk - def;
    return total;
}