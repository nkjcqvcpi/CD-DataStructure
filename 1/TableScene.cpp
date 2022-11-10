#include "TableScene.h"

USING_NS_CC;

bool player_win = false;
bool dealer_win = false;

int bets = 0;
char decks[4][13][5] = {
    {u8"🂡",u8"🂢",u8"🂣",u8"🂤",u8"🂥",u8"🂦",u8"🂧",u8"🂨",u8"🂩",u8"🂪",u8"🂫",u8"🂭",u8"🂮"},
    {u8"🂱",u8"🂲",u8"🂳",u8"🂴",u8"🂵",u8"🂶",u8"🂷",u8"🂸",u8"🂹",u8"🂺",u8"🂻",u8"🂽",u8"🂾"},
    {u8"🃁",u8"🃂",u8"🃃",u8"🃄",u8"🃅",u8"🃆",u8"🃇",u8"🃈",u8"🃉",u8"🃊",u8"🃋",u8"🃍",u8"🃎"},
    {u8"🃑",u8"🃒",u8"🃓",u8"🃔",u8"🃕",u8"🃖",u8"🃗",u8"🃘",u8"🃙",u8"🃚",u8"🃛",u8"🃝",u8"🃞"} };
auto dealer = Dealer();
auto player = Player();

Vec2 player_card[5] = {Vec2(850, 150), Vec2(1000, 150), Vec2(1150, 150), Vec2(1300, 150), Vec2(1450, 150)};
Vec2 dealer_card[5] = {Vec2(750, 800), Vec2(900, 800), Vec2(1050, 800), Vec2(1200, 800), Vec2(1350, 800)};

LNode *player_curr;
LNode *dealer_curr;

Scene* Table::createScene(){
    return Table::create();
}

void Table::deck(){
    int x = 375,y = 800;
    auto shoe = Layer::create();
    for (int i = 0;i<10;i++){
        auto card = Label::createWithSystemFont("🂠", "Arial", 200);
        card->setPosition(x+i*20, y);
        card->setRotation(i-3);
        shoe->addChild(card, 0);
    }
    this->addChild(shoe, 3);
}

void Table::card_table(){
    auto table = DrawNode::create();
    table->drawQuadBezier(Vec2(100, 463), Vec2(750, 116), Vec2(1400, 463), 50, Color4F(1, 1, 1, 100));
    table->drawLine(Vec2(100, 463), Vec2(200, 463), Color4F(1, 1, 1, 100));
    table->drawQuadBezier(Vec2(200, 463), Vec2(750, 232), Vec2(1300, 463), 50, Color4F(1, 1, 1, 100));
    table->drawLine(Vec2(1300, 463), Vec2(1400, 463), Color4F(1, 1, 1, 100));
    
    table->drawRect(Vec2(650, 76), Vec2(750, 232), Color4F(1, 1, 1, 0.5));
    this->addChild(table, 1);
    
    auto dig = Label::createWithSystemFont(StringUtils::format("分数\n%d", bets), "Arial", 32);
    dig->setColor(Color3B(128, 128, 128));
    dig->setPosition(700, 154);
    this->addChild(dig, 2);
}

void Table::blackjack_judgement(Dealer dealer, Player player){
    if ((dealer.hard_totals == 21 || dealer.soft_totals == 21) && (player.hard_totals == 21 || player.soft_totals == 21)) {
        dealer_win = true;player_win = true;
        show_dealer(dealer.cards.next->next->data, Vec2(900, 600), true, true);
        this->runAction(Sequence::create(DelayTime::create(5), CallFunc::create([&](){
            Director::getInstance()->replaceScene(End::createScene());}), NULL));
    }
    else if (dealer.hard_totals == 21 || dealer.soft_totals == 21) {
        dealer_win = true;
        show_dealer(dealer.cards.next->next->data, Vec2(900, 600), true, true);
        this->runAction(Sequence::create(DelayTime::create(5), CallFunc::create([&](){
            Director::getInstance()->replaceScene(End::createScene());}), NULL));
    }
    else if (player.hard_totals == 21 || player.soft_totals == 21) {
        player_win = true;
        show_dealer(dealer.cards.next->next->data, Vec2(900, 600), true, true);
        this->runAction(Sequence::create(DelayTime::create(5), CallFunc::create([&](){
            Director::getInstance()->replaceScene(End::createScene());}), NULL));
    }
}

void Table::judgement(Dealer dealer, Player player){
    if (player.hard_totals>21) {
        dealer_win = true;
        show_dealer(dealer.cards.next->next->data, Vec2(900, 600), true, true);
        this->runAction(Sequence::create(DelayTime::create(5), CallFunc::create([&](){
            Director::getInstance()->replaceScene(End::createScene());}), NULL));
    }
    else if (dealer.hard_totals>21) {
        player_win = true;
        show_dealer(dealer.cards.next->next->data, Vec2(900, 600), true, true);
        this->runAction(Sequence::create(DelayTime::create(5), CallFunc::create([&](){
            Director::getInstance()->replaceScene(End::createScene());}), NULL));
    }
    if ((dealer.soft_totals>=17||dealer.hard_totals>=17)){
        if (dealer.soft_totals>player.soft_totals||dealer.hard_totals>player.soft_totals) {
            dealer_win = true;
            show_dealer(dealer.cards.next->next->data, Vec2(900, 600), true, true);
            this->runAction(Sequence::create(DelayTime::create(5), CallFunc::create([&](){
                Director::getInstance()->replaceScene(End::createScene());}), NULL));
        }
        else if (player.soft_totals>dealer.soft_totals||player.hard_totals>dealer.soft_totals) {
            player_win = true;
            show_dealer(dealer.cards.next->next->data, Vec2(900, 600), true, true);
            this->runAction(Sequence::create(DelayTime::create(5), CallFunc::create([&](){
                Director::getInstance()->replaceScene(End::createScene());}), NULL));
        }
        else if (dealer.soft_totals==player.soft_totals) {
            dealer_win = true;player_win = true;
            show_dealer(dealer.cards.next->next->data, Vec2(900, 600), true, true);
            this->runAction(Sequence::create(DelayTime::create(5), CallFunc::create([&](){
                Director::getInstance()->replaceScene(End::createScene());}), NULL));
        }
    }
}

void Table::insurance(){
    for (int i = 0; i < 4; i++) if (LocateElem(dealer.cards, decks[i][0])){
        auto insurance_button = cocos2d::ui::Button::create();
        insurance_button->setTitleLabel(Label::createWithSystemFont("购买\n保险", "黑体", 32));
        insurance_button->setPosition(Vec2(1400, 50));
        insurance_button->setColor(Color3B(128, 128, 128));
        insurance_button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
            switch (type){
                case cocos2d::ui::Widget::TouchEventType::ENDED:
                    player.insurance = true;break;
                default:
                    break;
            }
        });
        this->addChild(insurance_button, 6);
    }
}

void Table::decision(){
    auto decision_layer = Layer::create();
    this->addChild(decision_layer, 5);
    
    auto dd_button = cocos2d::ui::Button::create();
    dd_button->setTitleLabel(Label::createWithSystemFont("双倍\n下注", "黑体", 32));
    dd_button->setPosition(Vec2(50, 50));
    dd_button->setColor(Color3B(128, 128, 128));
    dd_button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                player.double_down();break;
            default:
                break;
        }
    });
    decision_layer->addChild(dd_button, 6);
    
    auto split_button = cocos2d::ui::Button::create();
    split_button->setTitleLabel(Label::createWithSystemFont("分牌", "黑体", 32));
    split_button->setPosition(Vec2(150, 50));
    split_button->setColor(Color3B(128, 128, 128));
    split_button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                player.split();break;
            default:
                break;
        }
    });
    decision_layer->addChild(split_button, 6);
    
    auto surrender_button = cocos2d::ui::Button::create();
    surrender_button->setTitleLabel(Label::createWithSystemFont("投降", "黑体", 32));
    surrender_button->setPosition(Vec2(250, 50));
    surrender_button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                Director::getInstance()->replaceScene(End::createScene());break;
            default:
                break;
        }
    });
    decision_layer->addChild(surrender_button, 6);
    
    auto hit_button = cocos2d::ui::Button::create();
    hit_button->setTitleLabel(Label::createWithSystemFont("要牌", "黑体", 32));
    hit_button->setPosition(Vec2(350, 50));
    hit_button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                player.hit(&dealer.Cards);
                player_curr = player_curr->next;
                deal(player_curr->data, player_card[player.num_card-1], true, false);
                break;
            default:
                break;
        }
    });
    decision_layer->addChild(hit_button, 6);
    
    auto pass_button = cocos2d::ui::Button::create();
    pass_button->setTitleLabel(Label::createWithSystemFont("跳过", "黑体", 32));
    pass_button->setPosition(Vec2(450, 50));
    pass_button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type){
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                if (dealer.hard_totals<17){
                    dealer.deal();
                    dealer_curr = dealer_curr->next;
                    deal(dealer_curr->data, dealer_card[dealer.num_card-1], true, true);
                }
                this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([&](){
                    judgement(dealer, player);}), NULL));
                break;
            default:
                break;
        }
    });
    decision_layer->addChild(pass_button, 6);
    
}

void Table::shu(){
    auto label = Label::createWithSystemFont("正在洗牌", "黑体", 64);
    label->setPosition(750, 463);
    this->addChild(label, 10);
    auto fadein = FadeIn::create(3.0f);
    label->runAction(fadein);
    auto fadeout = FadeOut::create(3.0f);
    label->runAction(fadeout);
    
}

void Table::game(){
    dealer.shuffle(8);
    
    FiniteTimeAction* shuffle_d = Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(Table::shu, this)), NULL);
    this->runAction(shuffle_d);
    
    FiniteTimeAction* deck_d = Sequence::create(DelayTime::create(4), CallFunc::create(CC_CALLBACK_0(Table::deck, this)), NULL);
    this->runAction(deck_d);
    
    this->runAction(Sequence::create(DelayTime::create(5), CallFunc::create([&](){
        player.hit(&dealer.Cards);
        player_curr = player.cards.next;
        deal(player_curr->data, player_card[player.num_card-1], true, false);
    }), NULL));
    
    this->runAction(Sequence::create(DelayTime::create(6), CallFunc::create([&](){
        dealer.deal();
        dealer_curr = dealer.cards.next;
        deal(dealer_curr->data, dealer_card[dealer.num_card-1], true, true);
    }), NULL));
    
    this->runAction(Sequence::create(DelayTime::create(7), CallFunc::create([&](){
        player.hit(&dealer.Cards);
        player_curr = player_curr->next;
        deal(player_curr->data, player_card[player.num_card-1], true, false);
    }), NULL));
    
    this->runAction(Sequence::create(DelayTime::create(8), CallFunc::create([&](){
        blackjack_judgement(dealer, player);
    }), NULL));
    
    this->runAction(Sequence::create(DelayTime::create(9), CallFunc::create([&](){
        dealer.deal();
        dealer_curr = dealer_curr->next;
        deal(dealer_curr->data, dealer_card[dealer.num_card-1], false, true);
    }), NULL));
    
    this->runAction(Sequence::create(DelayTime::create(10), CallFunc::create([&](){
        blackjack_judgement(dealer, player);
    }), NULL));
    
    this->runAction(Sequence::create(DelayTime::create(11), CallFunc::create([&](){
        insurance();
    }), NULL));

    this->runAction(Sequence::create(DelayTime::create(12), CallFunc::create([&](){
        decision();
    }), NULL));
    
//    this->runAction(Sequence::create(DelayTime::create(13), CallFunc::create([&](){
//
//    }), NULL));
}

void Table::deal(char* card, Vec2 pos, bool mode, bool dealer){
    auto moveTo = MoveTo::create(2, pos);
    if (dealer) moveTo->setDuration(1);
    auto d_card = Label::createWithSystemFont(card, "Arial", 200);
    if (!mode) d_card->setString("🂠");
    d_card->setPosition(662, 800);
    d_card->runAction(moveTo);
    this->addChild(d_card, 3);
}

void Table::show_dealer(char* card, cocos2d::Vec2 pos, bool mode, bool dealer){
    auto moveTo = MoveTo::create(2, pos);
    if (dealer) moveTo->setDuration(1);
    auto d_card = Label::createWithSystemFont(card, "Arial", 200);
    if (!mode) d_card->setString("🂠");
    d_card->setPosition(900, 800);
    d_card->runAction(moveTo);
    this->addChild(d_card, 3);
}

bool Table::init(){
    if ( !Scene::init() ) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto Background = LayerColor::create(Color4B(0, 255, 0, 100), 1500, 927);
    this->addChild(Background, 0);
    
    card_table();
    game();
    return true;
    
}



