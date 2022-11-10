//
//  EndScene.hpp
//  Black-Jack
//
//  Created by Houtong Lei on 2021/4/25.
//

#ifndef EndScene_hpp
#define EndScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BlackJackScene.h"


class End : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    // a selector callback
    
    // implement the "static create()" method manually
    CREATE_FUNC(End);
};

#endif /* EndScene_hpp */
