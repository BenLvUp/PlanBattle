#ifndef __plangame__StartLayer__
#define __plangame__StartLayer__

#include <iostream>
#include "cocos2d.h"
#include "HelloWorldScene.h"
USING_NS_CC;


//1.
class StartLayer1 : public CCLayer
{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(StartLayer1);
    
    void changeScene(CCObject* obj);
};

//2.
class StartLayer2 : public CCLayer
{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(StartLayer2);
    
    void menuCloseCallback(CCObject* pSender);
    void changeScene();
    
};


//////////////////////////////////////////////////
//3.
class PauseLayer : public CCLayer
{
public:
    CCLayerColor *colorLayer;
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(PauseLayer);
    void backToGame(CCObject* pSender);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;}
    void registerWithTouchDispatcher();
    //void changeScene();

};


//4.
class GameOverLayer : public CCLayer
{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameOverLayer);
    
    void menuCloseCallback(CCObject* pSender);
    void changeScene();
};



#endif /* defined(__plangame__StartLayer__) */
