//
//  Player.cpp
//  Black-Jack
//
//  Created by Houtong Lei on 2021/4/23.
//

#include "Player.h"

char player_deck[4][13][5] = {
    {u8"🂡",u8"🂢",u8"🂣",u8"🂤",u8"🂥",u8"🂦",u8"🂧",u8"🂨",u8"🂩",u8"🂪",u8"🂫",u8"🂭",u8"🂮"},
    {u8"🂱",u8"🂲",u8"🂳",u8"🂴",u8"🂵",u8"🂶",u8"🂷",u8"🂸",u8"🂹",u8"🂺",u8"🂻",u8"🂽",u8"🂾"},
    {u8"🃁",u8"🃂",u8"🃃",u8"🃄",u8"🃅",u8"🃆",u8"🃇",u8"🃈",u8"🃉",u8"🃊",u8"🃋",u8"🃍",u8"🃎"},
    {u8"🃑",u8"🃒",u8"🃓",u8"🃔",u8"🃕",u8"🃖",u8"🃗",u8"🃘",u8"🃙",u8"🃚",u8"🃛",u8"🃝",u8"🃞"} };

Player::Player() {
    player_id = 0;
    score = 0;
    num_card = 0;
    insurance = false;
    InitList(&cards);
}

void Player::make_insurance()
{
    puts("Make a insurance or not?");
    char status;
    scanf("%c",&status);
    if (status=='y') insurance = true;
}

void Player::hit(SqStack* Cards){
    ElemType card;
    Pop(Cards, &card);
    ListInsert(&cards, num_card+1, card);
    num_card++;
    total();
}

void Player::stand(){
    
}

void Player::double_down()
{
}

void Player::split()
{
}

void Player::surrender(){
    win = false;
}

void Player::total(){
    soft_totals = 0;
    LNode* p;
    p = cards.next;
    while (p != NULL) {
        char *card = p->data;
        for (int row=0;row<4;row++){
            for (int column=0;column<13;column++){
                if (strcmp(card, player_deck[row][column])==0){
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
                if (strcmp(card, player_deck[row][column])==0){
                    if (column==0) hard_totals+=1;
                    else if (column>=9) hard_totals+=10;
                    else hard_totals+=column+1;
                }
            }
        }
        p = p->next;
    };
    if (hard_totals>21) bust=true;
    if (hard_totals==21||soft_totals==21) win = true;
}

char Player::decision(){
    puts("Choose your disicion:");
    char dici;
    scanf("%c", &dici);
    switch(dici){
        case 'h':return 'h';break;
        case 's':stand();break;
        case 'd':double_down();break;
        case 'p':split();break;
        case 'u':surrender();break;
    }
    
}
