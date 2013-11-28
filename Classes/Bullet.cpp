#include "Bullet.h"
#include <list>
#include "SimpleAudioEngine.h"
using namespace std;
CCArray* Bullet::bulletArr = NULL;
bool Bullet::isActive = true;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
    bulletArr->release();
}

bool Bullet::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    isActive = true;
    bulletArr = CCArray::create();
    bulletArr->retain();
    schedule(schedule_selector(Bullet::addbullet),0.1f);
    schedule(schedule_selector(Bullet::movebullet),0.1f);
    return true;
}

//添加一个子弹
void Bullet::addbullet(float t)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bullet.mp3");
    CCSprite* palyer = (CCSprite*)Plan::sharPlayer->getChildByTag(747);
    if (palyer->isVisible() == true && isActive == true )
    {
        CCSprite *bullet = CCSprite::createWithSpriteFrameName("bullet1.png");
        addChild(bullet);
        
        bullet->setPosition(ccp(palyer->getPositionX(),palyer->getPositionY()+palyer->getContentSize().height/2));
        bulletArr->addObject(bullet);
    }
}

//所有的子弹移动
void Bullet::movebullet(float t)
{
    CCObject *obj = NULL;
    list<CCObject*> elementToRemove;
    CCARRAY_FOREACH(bulletArr, obj)
    {
        CCSprite *bullet = (CCSprite*)obj;
        bullet->setPositionY(bullet->getPositionY()+30);
        if (bullet->getPositionY() > 800)//移除对象
        {
            elementToRemove.push_back(obj);
        }
    }
    
    for (list<CCObject*>::iterator iter = elementToRemove.begin(); iter != elementToRemove.end(); ++iter)
    {
        CCSprite *bullet1 = (CCSprite*)*iter;
        bulletArr->removeObject(*iter);
        bullet1->removeFromParentAndCleanup(true);
    }
}







