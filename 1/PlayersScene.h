#ifndef __Players_SCENE_H__
#define __Players_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "TableScene.h"

class Players : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Players);
};

#endif // __Players_SCENE_H__
