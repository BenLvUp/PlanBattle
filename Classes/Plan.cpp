#include "Plan.h"
Plan* Plan::sharPlayer=NULL;

bool Plan::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    setTouchEnabled(true);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *player = CCSprite::create("hero2.png");
    addChild(player,0,747);
    
    
    CCAnimation *animation = CCAnimation::create();
    for (int i = 1; i <= 2; i++)
    {
        animation->addSpriteFrameWithFileName(CCString::createWithFormat("hero%d.png",i)->getCString());
    }
    animation->setDelayPerUnit(0.1f);
    CCAnimate *action = CCAnimate::create(animation);
    player->runAction(CCRepeatForever::create(action));
    
    player->setPosition(ccp(size.width/2, player->getContentSize().height/2));
    return true;
    
}

Plan* Plan::create()
{
    Plan *pRet = new Plan();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
		sharPlayer=pRet;
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

//触摸事件
void Plan::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool Plan::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSprite *player = (CCSprite*)Plan::sharPlayer->getChildByTag(747);
    CCPoint touchPoint = pTouch->getLocation();
    if (player->boundingBox().containsPoint(touchPoint))
    {
        deltax = touchPoint.x - player->getPositionX();
        deltay = touchPoint.y - player->getPositionY();
        return true;
    }
    else
    {
        return false;
    }
}

void Plan::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPoint = pTouch->getLocation();
    float x = touchPoint.x - deltax;
    float y = touchPoint.y - deltay;
    
    CCSprite *player = (CCSprite*)Plan::sharPlayer->getChildByTag(747);
    player->setPosition(ccp(x, y));
}





