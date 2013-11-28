#ifndef __plangame__Plan__
#define __plangame__Plan__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;


class Plan : public CCLayer
{
public:
    int deltax, deltay;
    
    virtual bool init();
    static Plan *sharPlayer;
    static Plan* create();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    
    
};

#endif /* defined(__plangame__Plan__) */
