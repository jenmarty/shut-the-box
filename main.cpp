//
//  main.cpp
//  shutthebox
//
//  Created by Jennifer Marty on 4/11/20.
//  Copyright © 2020 Jennifer Marty. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

struct box_flap {
    int number;
    char status;
};

class Player {
public:
    string name;
    int score = 0;
    vector<box_flap> box;
    
    Player(string Name) : name(Name) {
        box.resize(12);
        for (size_t i = 0; i < 12; i++) {
            box[i].number = static_cast<int>(i) + 1;
            box[i].status = 'o';
        }
    }
    
    bool all_closed() {
        bool temp = true;
        for (size_t i = 0; i < 12; i++) {
            if (box[i].status == 'o') {
                temp = false;
                break;
            }
        }
        return temp;
    }
    
    void reset_box() {
        for (size_t i = 0; i < 12; i++) {
            box[i].status = 'o';
        }
    }
    

    
};

bool is_game_over(vector<Player> &players) {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].score > 100) {
            return true;
        }
    }
    return false;
}

int roll_dice() {
    int dice_roll = rand() % 10;
    
    if (dice_roll > 6) {
        dice_roll = dice_roll - 3;
    }
    if (dice_roll == 0) {
        dice_roll = 1;
    }
    return dice_roll;
}

void print_box(Player temp) {
    for (int i = 0; i < 12; i++) {
        if (temp.box[i].status == 'o') {
            cout << "|" << temp.box[i].number << "| ";
        }
        else {
            cout << "__ ";
        }
    }
    cout << endl << endl;
}

void take_turn(Player &temp) {
    cout << temp.name << " is rolling the dice! " << endl;
    int temp1 = roll_dice();
    int temp2 = roll_dice();

        cout << "Dice one is a " << temp1 << " and dice two is a " << temp2;
        cout << " for a total of " << temp1 + temp2 << '\n' << endl;
        
        cout << "Here is your current board: " << '\n';
        print_box(temp);
        
        bool print = true;
        while (print) {
            cout << "Do you want to shut any flaps? Enter 'y' or 'n' ";
            char y_n;
            cin >> y_n;
            
            if (y_n == 'n') {
                print = false;
            }
            
            else {
                cout << "Please enter the number of the flap: ";
                int num;
                cin >> num;
                size_t temppp = static_cast<size_t>(num) - 1;
                
                temp.box[temppp].status = 'c';
                cout << endl;
                
                cout << "Flap " << num << " is closed. Heres your current";
                cout << " board." << endl;
                print_box(temp);
                
            }
        }
    
}

int main() {
    
    //num players and vector of player structs
    int player_num;
    vector<Player> players;
    
    
    srand(static_cast<unsigned>(time(NULL)));
    
    
    cout << "Hey, welcome to shut the box!" << '\n' << endl;
    cout << "How many people are going to be playing?" << '\n';
    cout << "People: ";
    
    cin >> player_num;
    players.reserve(player_num);
    
    for (size_t i = 0; i < player_num; i++) {
        cout << "Enter name of player " << static_cast<int>(i) + 1 << ": ";
        string name;
        cin >> name;
        
        Player temp(name);
        players.push_back(temp);
        cout << '\n';
    }
    
    cout << '\n' << "Cool! Let's start." << '\n' << '\n';
    
    bool game_over = false;
    while (!game_over) {
        for (size_t i = 0; i < players.size(); i++) {
            Player &current = players[i];
            
            take_turn(current);
            
            char y_n;
            cout << "Are you able to keep rolling? enter 'y' or 'n': ";
            cin >> y_n;
            cout << endl;
            while (y_n == 'y') {
                take_turn(current);
                
                cout << "Are you able to keep rolling? enter 'y' or 'n': ";
                cin >> y_n;
                cout << endl;
            }
        
        if (current.all_closed()) {
            cout << "Congrats you shut the box! Score for this round = 0";
            cout << endl << endl;
            current.reset_box();
        }
        else {
            int temp_score = 0;
            for (size_t i = 0; i < 12; i++) {
                if (current.box[i].status == 'o') {
                    temp_score += current.box[i].number;
                }
            }
            current.score += temp_score;
            cout << "Your turn is over. Your score for this round was ";
            cout << temp_score << ". Your total score is " << current.score;
            cout << endl << endl;
            current.reset_box();
        }
    }
        game_over = is_game_over(players);
    }
    
    string winner_name;
    int temp = 1000;
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].score < temp) {
            temp = players[i].score;
            winner_name = players[i].name;
        }
    }
    cout << "Game over! Someone scored over 100!" << endl;
    cout << "The winner is " << winner_name << "!" << endl;
    cout << "Thanks for playing :P" << endl;
    return 0;
}
