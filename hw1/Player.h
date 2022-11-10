//
//  Player.h
//  Black-Jack
//
//  Created by Houtong Lei on 2021/4/23.
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "list.h"
#include <string>

class Player
{
public:
    int player_id;

    int score;
    int counter;
    int num_card;
    LNode cards;
    int hard_totals;
    int soft_totals;
    bool bust;
    bool win;

    Player();
    bool insurance;
    void make_insurance();
    void hit(SqStack* Cards);
    void stand();
    void double_down();
    void split();
    void surrender();
    void total();
    char decision();
};

#endif /* Player_h */
