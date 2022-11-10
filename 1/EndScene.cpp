//
//  EndScene.cpp
//  Black-Jack
//
//  Created by Houtong Lei on 2021/4/25.
//

#include "EndScene.h"

USING_NS_CC;

Scene* End::createScene(){
    return End::create();
}

bool End::init(){
    if ( !Scene::init() ) return false;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto Background = LayerColor::create(Color4B(0, 255, 0, 100), 1500, 927);
    this->addChild(Background, 0);
    
    if (player_win&&!dealer_win) {
        auto Title = Label::createWithSystemFont("你赢了", "Arial", 100);
        Title->setPosition(750, 463);
        this->addChild(Title, 1);
    }
    else if (!player_win&&dealer_win) {
        auto Title = Label::createWithSystemFont("你输了", "Arial", 100);
        Title->setPosition(750, 463);
        this->addChild(Title, 1);
    }
    else {
        auto Title = Label::createWithSystemFont("平局", "Arial", 100);
        Title->setPosition(750, 463);
        this->addChild(Title, 1);
    }
    
    
    
    auto Exit = cocos2d::ui::Button::create();
    Exit->setTitleLabel(Label::createWithSystemFont("掀桌", "Arial", 64));
    Exit->setPosition(Vec2(375, 232));
    Exit->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                Director::getInstance()->end();
                break;
            default:
                break;
        }
    });
    this->addChild(Exit, 1);
    
    auto Retry = cocos2d::ui::Button::create();
    Retry->setTitleLabel(Label::createWithSystemFont("再来一局", "Arial", 64));
    Retry->setPosition(Vec2(1125, 232));
    Retry->setColor(Color3B(128,128,128));
    Retry->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                Director::getInstance()->replaceScene(BlackJack::createScene());
                break;
            default:break;
        }
    });
    this->addChild(Retry, 1);
    
    return true;
    
}
