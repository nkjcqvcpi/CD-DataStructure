#include "PlayersScene.h"

USING_NS_CC;

int num = 1;

Scene* Players::createScene()
{
    return Players::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in PlayersScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Players::init(){
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() ) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto Background = LayerColor::create(Color4B(0, 255, 0, 100), 1500, 927);
    this->addChild(Background, 0);
    
    auto Title = Label::createWithSystemFont("你想和\n多少人\n一起玩？", "Arial", 100);
    Title->setPosition(375, 463);
    this->addChild(Title, 1);
    
    auto Num = cocos2d::ui::Button::create();
    Num->setPosition(Vec2(1125, 463));
    auto num_label = Label::createWithSystemFont(std::to_string(num), "Arial", 64);
    Num->setTitleLabel(num_label);
    Num->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                Director::getInstance()->replaceScene(Table::createScene());
                break;
            default:
                break;
        }
    });
    this->addChild(Num, 1);
    
    auto Add = cocos2d::ui::Button::create();
    Add->setTitleLabel(Label::createWithSystemFont("∧", "Arial", 100));
    Add->setPosition(Vec2(1125, 695));
    Add->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                ++num;
                break;
            default:
                break;
        }
    });
    this->addChild(Add, 1);
    
    auto Sub = cocos2d::ui::Button::create();
    Sub->setTitleLabel(Label::createWithSystemFont("∨", "Arial", 100));
    Sub->setPosition(Vec2(1125, 232));
    Sub->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                --num;
                break;
            default:break;
        }
    });
    this->addChild(Sub, 1);
    
    return true;
}
