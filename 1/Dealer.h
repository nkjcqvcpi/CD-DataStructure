//
//  Dealer.h
//  Black-Jack
//
//  Created by Houtong Lei on 2021/4/23.
//

#ifndef Dealer_h
#define Dealer_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "list.h"
#include "stack.h"
#include <string>

class Dealer
{
public:
    bool win;
    int score;
    int num_card;
    LNode cards;
    int hard_totals;
    int soft_totals;
    
    bool bust;
    void total();

    int num_player;
    void deal();
    SqStack Cards;
    void shuffle(int num);
    Dealer();
    bool insurance();
    void decision();
};

#endif /* Dealer_h */
