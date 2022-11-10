//
//  main.cpp
//  test
//
//  Created by Houtong Lei on 2021/4/23.
//

#include <stdio.h>
#include <unistd.h>
#include "Dealer.h"
#include "Player.h"

void player_win(){
    puts("Player Win");
    exit(0);
}

void dealer_win(){
    puts("Dealer Win");
    exit(0);
}

void push(){
    puts("Push");
    exit(0);
}

void judgement(Dealer dealer, Player player){
    if ((dealer.hard_totals == 21 || dealer.soft_totals == 21) && (player.hard_totals == 21 || player.soft_totals == 21)) push();
    else if (dealer.hard_totals == 21 || dealer.soft_totals == 21) dealer_win();
    else if (player.hard_totals == 21 || player.soft_totals == 21) player_win();
    
    if (dealer.hard_totals>21) player_win();
    else if (player.hard_totals>21) dealer_win();
    
    if (dealer.soft_totals>=17||dealer.hard_totals>=17){
        if (dealer.soft_totals>player.soft_totals||dealer.hard_totals>player.soft_totals) dealer_win();
        else if (player.soft_totals>dealer.soft_totals||player.hard_totals>dealer.soft_totals) player_win();
        else if (dealer.soft_totals==player.soft_totals) push();
    }
}


int main(void){
    puts("Black-Jack Game");
    sleep(1);
    puts("InitDealer");
    Dealer dealer;
    puts("InitPlayer");
    Player player;
    puts("shuffing");
    dealer.shuffle(2);
    player.hit(&dealer.Cards);

    dealer.deal();
    
    player.hit(&dealer.Cards);
    judgement(dealer, player);
    
    dealer.deal();
    judgement(dealer, player);
    bool insu = dealer.insurance();
    if (insu) player.make_insurance();
    
    while(1){
        player.decision(&dealer);
        judgement(dealer, player);
        dealer.decision();
        judgement(dealer, player);
    }
}
