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
    srand(static_cast<unsigned int>(time(0)));
    bool victory;
    string name;
    int score=0;
    // save the counter that has the highest
    int scounter;
    // name of highscore
    string nhigh; 
    // two converts into int from string
    int c1;
    // temp value that is the size of a string
    int tsize;
    // saves the highest score 
    int chigh=0;
    string temp;
    list<string> sdata;
    fstream saves;
    int counter=0;
    saves.open("save.txt", ios::in | ios::out);
    int userinput = 99;
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
    userinput = 99;
    cout << "Enter your name that will be saved in the save file: " << endl;
    cin >> name;
    cout << "Some base Game Information" << endl;
    cout << "Easy Mode: Regeneration after each combat" << endl;
    cout << "Enemies have less attack and are more likely to miss" << endl;
    cout << "Less game mechanics to learn such as different equipment" <<endl;
    cout << "Would you like to play easy mode[1], hard mode[2] or medium mode[3]" << endl;
    while(userinput>3 || userinput <1){
        cin>>userinput;
    }
    if(userinput == 1){
        victory = easymode(score);
    }
    if (userinput == 2) {
        victory = hardmode(score);
        if(victory){
            score+=100;
        }
    }
    if (userinput == 3){
        victory = medmode(score);
    }
    //Save
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
    cout << "The Dice Rolls! " << num << " has been rolled!" << endl;
    cout << "Adding Bonus of " << bonus << endl;
    num += bonus;
    return num;
}
int Game::dmgcalc(int atk, int def, int bonus1, int bonus2){
    int vatk = diceroll(atk, bonus1);
    int vdef = diceroll(def, bonus2);
    int total = vatk - def;
    // Checks if total is a negative value
    total = (total<=0)?0:total;
    return total;
}
bool Game::easymode(int &score){
    //Declare all variables for this function
    map<string, int> jobs{{"Assassin", 10},{"Herald", 15},{"Knight", 20},{"Warrior", 25} };
    // Basic(x) is the armor the corresponds with the class
    map<string, int> armor{{"BasicA", 1}, {"BasicH", 1}, {"BasicK", 3}, {"BasicW", 2}};
    map<string, int> weapon{{"BasicA", 3}, {"BasicH", 2}, {"BasicK", 1}, {"BasicW", 2}};
    // To save score
    set<string> save;
    // to save which enemies were beaten
    stack<string> victory;
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
    //Before Game Start
    //Game start
    cout<< "Welcome to Dark Souls the Board Game Simplified V1" << endl;
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
                if (mattack = 0){
                    cout << mnames.front() << " has missed" <<endl;
                }
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
        return true;
    }
    score = victory.size();
    return false;
}
bool Game::hardmode(int &score){
    //Declare all variables for this function
    map<string, int> jobs{{"Assassin", 10},{"Herald", 15},{"Knight", 20},{"Warrior", 25}}; 
    // Basic(x) is the armor the corresponds with the class
    map<string, int> weapon{{"BasicA", 2}, {"BasicH", 2}, {"BasicK", 6}, {"BasicW", 4},
    {"Assassin's Flame Dagger", 1} , {"Assassin's Steel Dagger", 1}, 
    {"Assassin's Ice Dagger", 1}, {"Herald's Flame Staff", 1} , {"Herald's Steel Staff", 1}
    , {"Herald's Water Staff", 1}, {"Knight's Fire Long Sword", 3}, 
   {"Knight's Ice Long Sword", 3}, {"Knight's Steel Long Sword", 3}, 
   {"Warrior's Fire Sword", 2},
    {"Warrior's Ice Sword ", 2}, {"Warrior's Steel Sword", 2}};
    map<string, int> armor{{"BasicA", 3}, {"BasicH", 2}, {"BasicK", 1}, {"BasicW", 2}};
    // To save score
    set<string> save;
    // to save which enemies were beaten
    stack<string> victory;
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
    // Allows to upgrade your sword
    int sharpen=0;
    //Role numerical representation
    int role;
    // Weapon string saved
    // Element representation in numbers
    int ele;
    int dice;
    bool heal=false;
    // life steal
    bool ls = false;
    //Game start
    cout<< "Welcome to Dark Souls the Board Game Simplified V1" << endl;
    cout<< "This current version does not support score saves" <<endl;
    cout<<"Please Pick your class" << endl;
    cout << "1 for Assassin, 2 for Herald, 3 for Knight, and 4 for Warrior" << endl;
    //To prevent userinput error
    while(userinput>4 || userinput <1){
        cin>>userinput;
    }
    choicec = (userinput == 1) ? "Assassin" : (userinput == 2) ? 
        "Herald" : (userinput == 3) ? "Knight"  : "Warrior";
    role = userinput;
    cout << "You choose " << choicec << endl;
    cout << "These are the weapons list and there damages " << endl;
    cout << "Although you can only use the weapon with your class" <<endl;
    // Uses iterator to show all maps
    map<string, int>::iterator it;
    for(it = weapon.begin(); it != weapon.end(); it++){
        cout << it->first << " dmg: " << it->second << endl;
    }
    cout <<endl;
    cout << "You can equip different weapons mid combat however this will skip a turn" <<endl;
    cout << "Choose your weapon correctly to win out" << endl;
    php = jobs[choicec];
    dice = (role == 1)? 1 : (role == 2) ? 1 : (role == 3) ?  3 : 2;
    cweapon = weaponchoice(role, ele);
    cout <<"Alright Last Equipment option" << endl;
    cout << "What type of artifact do you want?" << endl;
    cout << "Life Steal Artifact (Heals 50% of your damage)(doesn't work with ultimate) abilities [1]" <<endl;
    cout << "Level up = Heal Artifact [2]" <<endl;
    cout << "I'm Crazy no artifact [3]" <<endl;
    userinput = correction(1,3);
    switch(userinput){
        // this ls is terrible
        case 1: ls = true; break;
        case 2: heal = true; break;
        case 3: score+= 100; break;
    }
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
            cout << "Press 1 to do a powerful attack(1 Action), " << endl;
            cout << "Press 2(Gain 1 Action(MAX3) and Defense) to Defense, " << endl;
            cout << "Press 3 to Quick Attack(0 Actions Cost or Gain)" << endl;
            cout << "Press 4 to Change equipment" <<endl;
            cout << "Press 5 to use Role's Special Ability " << endl;
            cin >> userinput;
            if(userinput>=1 && userinput<=5){
                cout << "The " << mnames.front() << "attacks" << endl;
                //If the user defends use up a bonus
                bonus = (userinput == 2)? 1: 0;
                // basic calculation base on random number generator
                mattack = (matk.front() ,armor[carmor], 1 ,bonus, rand () %1+3);
                //Outputs result of the attack
                cout << "The " << mnames.front() << " deals " << mattack << 
                        " damage" <<endl;
                jobs[choicec] -= mattack;
                // player's turn
                switch(userinput){
                    case 1: pattack = (stam>1)? hdmgcalc(weapon[cweapon], 
                            mdef.front(), 0 , 1, dice): 0 ; stam -= (stam > 0 )? 1: 0;break;
                    case 2: pattack = 0; stam += (stam>3)? 0: 1; break;
                    case 3: pattack = hdmgcalc(weapon[cweapon], 
                            mdef.front(), 1, 0, dice); break;
                    case 4: pattack = 0; weaponchoice(role, ele); break;
                    case 5: pattack = 0; if(stam==3){special(weapon[cweapon], mhp.front(), 
                            jobs[choicec], role, php, sharpen); stam=0;}
                    else{cout<<"You don't have enough stam to perform your special ability"
                            <<endl;}break;
                }
                //checks for supereffectiveness
                pattack = (mnames.size()==5 && ele == 2)? 3*(pattack+sharpen):
                    (mnames.size()==4 && ele == 4)? 3*(pattack+sharpen):
                        (mnames.size()==3 && ele == 2)? 3*(pattack+sharpen):
                            (mnames.size()==2 && ele == 4)? 3*(pattack+sharpen):
                                (mnames.size()==1 && ele == 2)? 3*(pattack+sharpen)
                        : pattack;
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
        if(!death){
            cout << "Congrats on beating the monster, you can now improve one of your stats" << endl;
            cout << "Max Hp[1] or Sharpness of your weapon[2]" << endl;
            userinput = correction(1,2);
            switch(userinput){
                case 1: php+=5;break; 
                case 2: sharpen+=1;break;
            }
        }
        mhp.pop();
        mnames.pop();
        matk.pop();
        mdef.pop();
    }
    //check for victory 
    if(victory.top() == "Dragon"){
        cout << "Congrats, You have beaten the game" <<endl;
        return true;
    }
    score += victory.size();
    return false;
}
string Game::weaponchoice(int role, int &ele){
    string weapon;
    cout << " Pick the weapon you chose to equip" << endl;
    if(role == 1){
        cout << "Basic Dagger[1] Flame Dagger[2] Ice Dagger[3] Steel Dagger[4]" <<endl;
        ele = correction(1,4);
        weapon = (ele == 1)? "BasicA" : (ele == 2)?
            "Assassin's Flame Dagger": (ele == 3)?"Assassin's Ice Dagger" : 
                "Assassin's Steel Dagger"; 
    }
    if(role == 2){
        cout << "Basic Dagger[1] Flame Dagger[2] Ice Dagger[3] Steel Dagger[4]" <<endl;
        ele = correction(1,4);
        weapon = (ele == 1)? "BasicH" : (ele == 2)?
            "Herald's Flame Staff": (ele == 3)?"Herald's Water Staff" : 
                "Herald's Steel Staff" ; 
    }
    if(role == 3){
        cout << "Basic Dagger[1] Flame Dagger[2] Ice Dagger[3] Steel Dagger[4]" <<endl;
        ele = correction(1,4);
        weapon = (ele == 1)? "BasicK" : (ele == 2)?
            "Knight's Fire Long Sword": (ele == 3)?"Knight's Ice Long Sword" : 
                "Knight's Steel Long Sword" ; 
    }
    if(role == 4){
        cout << "Basic Dagger[1] Flame Dagger[2] Ice Dagger[3] Steel Dagger[4]" <<endl;
        ele = correction(1,4);
        weapon = (ele == 1)? "BasicW" : (ele == 2)?
            "Warrior's Fire Sword": (ele == 3)?"Warrior's Ice Sword" : 
                "Warrior's Steel Sword" ; 
    }
    return weapon;
}
int Game::correction(int low , int high){
    int userinput = high +1;
    while(userinput> high || userinput < low){
        cin>>userinput;
    }
    return userinput;
}
int Game::hdmgcalc(int atk, int def, int bonus1, int bonus2 , int dice){
    int vatk = diceroll(dice, bonus1);
    int vdef = diceroll(dice, bonus2);
    vatk + atk;
    int total = vatk - def;
    // Checks if total is a negative value
    total = (total<=0)?0:total;
    return total;
}
// Special ability of the role of said character
void Game::special(int atk, int &mhp, int &php, int role, int &maxhp, int &sharpen ){
    // Assassin's special ability
    if(role == 1){
        cout << "You used death lotus" << endl;
        mhp -= 5 * (atk+sharpen); 
    }
    // for Herald
    if(role == 2){
        cout <<"You used Breaht of Life" << endl;
        maxhp += 5;
        php = maxhp;
    }
    // for Knight
    if(role == 3){
        // increases sword strenght
        cout << "You used Grandmasters at Arms" <<endl;
        sharpen+=2;
        mhp -= 3 * (atk+sharpen);
    }
    if(role == 4){
        cout << "You used Undying Rage" <<endl;
        maxhp+=1;
        sharpen+=1;
        mhp -= 3 * (atk+sharpen);  
    }
}
bool Game::medmode(int &score){
    //Declare all variables for this function
    map<string, int> jobs{{"Assassin", 10},{"Herald", 15},{"Knight", 20},{"Warrior", 25}}; 
    // Basic(x) is the armor the corresponds with the class
    map<string, int> weapon{{"BasicA", 2}, {"BasicH", 2}, {"BasicK", 6}, {"BasicW", 4},
    {"Assassin's Flame Dagger", 1} , {"Assassin's Steel Dagger", 1}, 
    {"Assassin's Ice Dagger", 1}, {"Herald's Flame Staff", 1} , {"Herald's Steel Staff", 1}
    , {"Herald's Water Staff", 1}, {"Knight's Fire Long Sword", 3}, 
   {"Knight's Ice Long Sword", 3}, {"Knight's Steel Long Sword", 3}, 
   {"Warrior's Fire Sword", 2},
    {"Warrior's Ice Sword ", 2}, {"Warrior's Steel Sword", 2}};
    map<string, int> armor{{"BasicA", 3}, {"BasicH", 2}, {"BasicK", 1}, {"BasicW", 2}};
    // To save score
    set<string> save;
    // to save which enemies were beaten
    stack<string> victory;
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
    // Allows to upgrade your sword
    int sharpen=0;
    //Role numerical representation
    int role;
    // Weapon string saved
    // Element representation in numbers
    int ele;
    int dice;
    bool heal=false;
    // life steal
    bool ls = false;
    //Game start
    cout<< "Welcome to Dark Souls the Board Game Simplified V1" << endl;
    cout<< "This current version does not support score saves" <<endl;
    cout<<"Please Pick your class" << endl;
    cout << "1 for Assassin, 2 for Herald, 3 for Knight, and 4 for Warrior" << endl;
    //To prevent userinput error
    while(userinput>4 || userinput <1){
        cin>>userinput;
    }
    choicec = (userinput == 1) ? "Assassin" : (userinput == 2) ? 
        "Herald" : (userinput == 3) ? "Knight"  : "Warrior";
    role = userinput;
    cout << "You choose " << choicec << endl;
    cout << "These are the weapons list and there damages " << endl;
    cout << "Although you can only use the weapon with your class" <<endl;
    // Uses iterator to show all maps
    map<string, int>::iterator it;
    for(it = weapon.begin(); it != weapon.end(); it++){
        cout << it->first << " dmg: " << it->second << endl;
    }
    cout <<endl;
    cout << "You can equip different weapons mid combat however this will skip a turn" <<endl;
    cout << "Choose your weapon correctly to win out" << endl;
    php = jobs[choicec];
    dice = (role == 1)? 1 : (role == 2) ? 1 : (role == 3) ?  3 : 2;
    cweapon = weaponchoice(role, ele);
    cout <<"Alright Last Equipment option" << endl;
    cout << "What type of artifact do you want?" << endl;
    cout << "Life Steal Artifact (Heals 50% of your damage)(doesn't work with ultimate) abilities [1]" <<endl;
    cout << "Level up = Heal Artifact [2]" <<endl;
    cout << "I'm Crazy no artifact [3]" <<endl;
    userinput = correction(1,3);
    switch(userinput){
        // this ls is terrible
        case 1: ls = true; break;
        case 2: heal = true; break;
        case 3: score+= 100; break;
    }
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
            cout << "Press 1 to do a powerful attack(1 Action), " << endl;
            cout << "Press 2(Gain 1 Action(MAX3) and Defense) to Defense, " << endl;
            cout << "Press 3 to Quick Attack(0 Actions Cost or Gain)" << endl;
            cout << "Press 4 to Change equipment" <<endl;
            cout << "Press 5 to use Role's Special Ability " << endl;
            cin >> userinput;
            if(userinput>=1 && userinput<=5){
                cout << "The " << mnames.front() << "attacks" << endl;
                //If the user defends use up a bonus
                bonus = (userinput == 2)? 1: 0;
                // basic calculation base on random number generator
                mattack = (matk.front() ,armor[carmor], 0 ,bonus, rand () %1+2);
                //Outputs result of the attack
                cout << "The " << mnames.front() << " deals " << mattack << 
                        " damage" <<endl;
                jobs[choicec] -= mattack;
                // player's turn
                switch(userinput){
                    case 1: pattack = (stam>1)? hdmgcalc(weapon[cweapon], 
                            mdef.front(), 0 , 1, dice): 0 ; stam -= (stam > 0 )? 1: 0;break;
                    case 2: pattack = 0; stam += (stam>3)? 0: 1; break;
                    case 3: pattack = hdmgcalc(weapon[cweapon], 
                            mdef.front(), 1, 0, dice); break;
                    case 4: pattack = 0; weaponchoice(role, ele); break;
                    case 5: pattack = 0; if(stam==3){special(weapon[cweapon], mhp.front(), 
                            jobs[choicec], role, php, sharpen); stam=0;}
                    else{cout<<"You don't have enough stam to perform your special ability"
                            <<endl;}break;
                }
                //checks for supereffectiveness
                pattack = (mnames.size()==5 && ele == 2)? 3*(pattack+sharpen):
                    (mnames.size()==4 && ele == 4)? 3*(pattack+sharpen):
                        (mnames.size()==3 && ele == 2)? 3*(pattack+sharpen):
                            (mnames.size()==2 && ele == 4)? 3*(pattack+sharpen):
                                (mnames.size()==1 && ele == 2)? 3*(pattack+sharpen)
                        : pattack;
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
        if(!death){
            cout << "Congrats on beating the monster, you can now improve one of your stats" << endl;
            cout << "Max Hp[1] or Sharpness of your weapon[2]" << endl;
            userinput = correction(1,2);
            switch(userinput){
                case 1: php+=5;break; 
                case 2: sharpen+=1;break;
            }
        }
        mhp.pop();
        mnames.pop();
        matk.pop();
        mdef.pop();
    }
    //check for victory 
    if(victory.top() == "Dragon"){
        cout << "Congrats, You have beaten the game" <<endl;
        return true;
    }
    score += victory.size();
    return false;
}