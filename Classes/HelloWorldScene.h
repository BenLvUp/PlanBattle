#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Plan.h"
#include "Bullet.h"
#include "Enemy.h"
#include "StartLayer.h"
USING_NS_CC;

class HelloWorld : public cocos2d::CCLayer
{
public:
    CCSprite *bg1;
    CCSprite *bg2;
    static CCLabelBMFont *label;
    static int score;
    
    Plan *plan;
    Bullet *bullet;
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(HelloWorld);
    
    void moveBg(float t);
    static void changeToGameOverLayer();//切换到游戏结束场景
    void changeToPause(CCObject *obj);//游戏暂停
};

#endif // __HELLOWORLD_SCENE_H__
