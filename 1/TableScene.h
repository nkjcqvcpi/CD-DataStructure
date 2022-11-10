#ifndef __TABLE_SCENE_H__
#define __TABLE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Dealer.h"
#include "Player.h"
#include <unistd.h>
#include "EndScene.h"

extern bool player_win;
extern bool dealer_win;

class Table : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void shu();
    
    void card_table();
    void deck();
    void card();
    void scores();
    
    void game();
    void insurance();
    
    void decision();
    char hit();
    void deal(char* card, cocos2d::Vec2 pos, bool mode, bool dealer);
    void show_dealer(char* card, cocos2d::Vec2 pos, bool mode, bool dealer);
    void judgement(Dealer dealer, Player player);
    void blackjack_judgement(Dealer dealer, Player player);
    
    // a selector callback
    
    // implement the "static create()" method manually
    CREATE_FUNC(Table);
};

#endif // __Table_SCENE_H__
