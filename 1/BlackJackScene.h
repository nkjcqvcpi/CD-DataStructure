#ifndef __BLACKJACK_SCENE_H__
#define __BLACKJACK_SCENE_H__

#include "cocos2d.h"
#include "PlayersScene.h"

class BlackJack : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuQuitCallback(cocos2d::Ref* pSender);
    
    void menuStartCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BlackJack);
};

#endif // __BLACKJACK_SCENE_H__
