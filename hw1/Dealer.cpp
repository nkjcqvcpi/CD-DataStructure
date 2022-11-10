//
//  Dealer.cpp
//  Black-Jack
//
//  Created by Houtong Lei on 2021/4/23.
//

#include "Dealer.h"

char dealer_deck[4][13][5] = {
    {u8"🂡",u8"🂢",u8"🂣",u8"🂤",u8"🂥",u8"🂦",u8"🂧",u8"🂨",u8"🂩",u8"🂪",u8"🂫",u8"🂭",u8"🂮"},
    {u8"🂱",u8"🂲",u8"🂳",u8"🂴",u8"🂵",u8"🂶",u8"🂷",u8"🂸",u8"🂹",u8"🂺",u8"🂻",u8"🂽",u8"🂾"},
    {u8"🃁",u8"🃂",u8"🃃",u8"🃄",u8"🃅",u8"🃆",u8"🃇",u8"🃈",u8"🃉",u8"🃊",u8"🃋",u8"🃍",u8"🃎"},
    {u8"🃑",u8"🃒",u8"🃓",u8"🃔",u8"🃕",u8"🃖",u8"🃗",u8"🃘",u8"🃙",u8"🃚",u8"🃛",u8"🃝",u8"🃞"} };

void Dealer::shuffle(int num) {
    InitStack(&Cards);
    num *= 52;
    bool card_status[416] = { 0 };
    int i = 0, c, row, column;
    while (i < num) {
        c = rand() % 416;
        srand((unsigned int)clock());
        if (card_status[c] == false) {
            row = (c % 52) / 13;
            column = (c % 52) % 13;
            card_status[c] = true;
            Push(&Cards, dealer_deck[row][column]);
            i++;
        }
    }
}

void Dealer::deal() {
    ElemType card;
    Pop(&Cards, &card);
    ListInsert(&cards, num_card+1, card);
    num_card++;
    total();
}

Dealer::Dealer() {
    num_card = 0;
    score = 0;
    bust = false;
    InitList(&cards);
}

bool Dealer::insurance(){
    for (int i = 0; i < 4; i++) if (LocateElem(cards, dealer_deck[i][0]))
        return true;
    return false;
}

void Dealer::total(){
    soft_totals = 0;
    LNode* p;
    p = cards.next;
    while (p != NULL) {
        char *card = p->data;
        for (int row=0;row<4;row++){
            for (int column=0;column<13;column++){
                if (strcmp(card, dealer_deck[row][column])==0){
                    if (column==0) soft_totals+=11;
                    else if (column>=9) soft_totals+=10;
                    else soft_totals+=column+1;
                }
            }
        }
        p = p->next;
    };
    
    hard_totals = 0;
    p = cards.next;
    while (p != NULL) {
        char *card = p->data;
        for (int row=0;row<4;row++){
            for (int column=0;column<13;column++){
                if (strcmp(card, dealer_deck[row][column])==0){
                    if (column==0) hard_totals+=1;
                    else if (column>=9) hard_totals+=10;
                    else hard_totals+=column+1;
                }
            }
        }
        p = p->next;
    };
    
    if (hard_totals == 21||soft_totals == 21) win = true;
}

void Dealer::decision(){
    if (soft_totals<17) deal();
    total();
}
