#include "BlackJackScene.h"

USING_NS_CC;

Scene* BlackJack::createScene(){
    return BlackJack::create();
}

bool BlackJack::init(){
    if ( !Scene::init() )  return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto Background = LayerColor::create(Color4B(0, 255, 0, 100), 1500, 927);
    this->addChild(Background, 0);
    
    auto Title = Label::createWithSystemFont("Blackjack", "Arial", 128);
    Title->setPosition(1125, 695);
    this->addChild(Title, 1);
    
    auto A1 = Label::createWithSystemFont("🃑", "Arial", 512);
    A1->setPosition(300, 464);
    A1->setRotation(-15);
    this->addChild(A1, 1);
    
    auto D10 = Label::createWithSystemFont("🃊", "Arial", 512);
    D10->setTextColor(Color4B(255, 0, 0, 100));
    D10->setRotation(15);
    D10->setPosition(450, 464);
    this->addChild(D10, 2);
    
    auto Start = Label::createWithSystemFont("开始", "黑体", 64);
    auto StartButton = MenuItemLabel::create(Start, CC_CALLBACK_1(BlackJack::menuStartCallback, this));
    StartButton->setPosition(0, -100);
    auto Quit = Label::createWithSystemFont("退出", "黑体", 64);
    auto QuitButton = MenuItemLabel::create(Quit, CC_CALLBACK_1(BlackJack::menuQuitCallback, this));
    QuitButton->setPosition(0, -200);
    
    auto MainMenu = Menu::create(StartButton, QuitButton, NULL);
    MainMenu->setPosition(1125, 463);
    this->addChild(MainMenu, 1);
    
    return true;
}


void BlackJack::menuQuitCallback(Ref* pSender){
    Director::getInstance()->end();
}

void BlackJack::menuStartCallback(Ref* pSender){
    Director::getInstance()->replaceScene(Players::createScene());
}
