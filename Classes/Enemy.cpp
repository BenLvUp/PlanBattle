#include "Enemy.h"
#include "SimpleAudioEngine.h"

CCArray* EnemyBase::enemyArr = NULL;

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
    enemyArr->release();
}

bool EnemyBase::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    activePlaneNum1 = activePlaneNum2 = activePlaneNum3 = 0;
    
    enemyArr = CCArray::create();
    enemyArr->retain();
    this->schedule(schedule_selector(EnemyBase::addEnemy),0.7f);
    this->schedule(schedule_selector(EnemyBase::moveEnemy),0.1f);
    this->schedule(schedule_selector(EnemyBase::collisionDetection), 0.1f);  //碰撞检测（同时分数更新）
    return true;
}

void EnemyBase::moveEnemy(float dt)
{
    CCObject *obj = NULL;
    CCARRAY_FOREACH(enemyArr, obj)
    {
        PlaneStruct *objp = (PlaneStruct*)obj;
        if (objp->tag == 3)
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("big_spaceship_flying.mp3");
        }
        CCSprite *plane = objp->plane;
        plane->setPositionY(plane->getPositionY()- 20);
        if (plane->getPositionY() < 0)
        {
            enemyArr->removeObject(obj);
            plane->removeFromParentAndCleanup(true);
        }
    }
}

//碰撞检测
void EnemyBase::collisionDetection(float dt)
{
    CCArray *bullerArr = Bullet::bulletArr;
    CCObject *objBullet=NULL, *objEnemy=NULL;
    CCARRAY_FOREACH(enemyArr, objEnemy)
    {
        PlaneStruct *objp = (PlaneStruct*)objEnemy;
        CCSprite *enemy = objp->plane;
        
        //1.敌机和子弹
        CCARRAY_FOREACH(bullerArr, objBullet)
        {
            CCSprite *bullet = (CCSprite*)objBullet;
            if (bullet->boundingBox().intersectsRect(enemy->boundingBox())) //相撞
            {
                EnemyExplode(objp, bullet);//爆炸动画
                bullerArr->removeObject(objBullet);
                enemyArr->removeObject(objp);
                
                //更新分数
                //CCLabelBMFont *label = (CCLabelBMFont*)getChildByTag(20);
                HelloWorld::score += 50;
                char s[10];
                sprintf(s, "%d", HelloWorld::score);
                HelloWorld::label->setString(s);
                
            }
        }
        
        //2.敌机和player
        CCSprite* palyer = (CCSprite*)Plan::sharPlayer->getChildByTag(747);
        if (palyer->boundingBox().intersectsRect(enemy->boundingBox())) //相撞
        {
            Bullet::isActive = false;
            heroExplode();
            EnemyExplode(objp, NULL);
            enemyArr->removeObject(objEnemy);
        }
    }
}

//操作hero部分
void EnemyBase::heroExplode()
{
    CCSprite* palyer = (CCSprite*)Plan::sharPlayer->getChildByTag(747);
    //爆炸的动画
    CCAnimation *animation = CCAnimation::create();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("use_bomb.mp3");
    for (int i = 1; i <= 4; i++)
    {
        animation->addSpriteFrameWithFileName(CCString::createWithFormat("hero_blowup_n%d.png",i)->getCString());
    }
    animation->setDelayPerUnit(0.2f);
    CCAnimate *action2 = CCAnimate::create(animation); //飞机爆炸
    CCActionInterval*  action1 = CCBlink::create(1, 3);//飞机闪几下
    CCActionInterval* action3 = CCFadeOut::create(0.2f); //飞机变暗消失
    CCSequence *seq = CCSequence::create(action1,
                                         action2,
                                         action3,
                                         CCCallFunc::create(this, callfunc_selector(EnemyBase::deletePlayer)),
                                         NULL );
    palyer->runAction(seq);
}

void EnemyBase::deletePlayer()
{
    CCSprite* palyer = (CCSprite*)Plan::sharPlayer->getChildByTag(747);
    palyer->setVisible(false);
    
    HelloWorld::changeToGameOverLayer();
}

void EnemyBase::deleteobj(CCNode* sender, void* t)
{
    CCSprite *e = (CCSprite*)sender;
    CCSprite *b = (CCSprite*)t;
    if (e != NULL)
    {
        e->removeFromParentAndCleanup(true);
    }
    if (t != NULL)
    {
        b->removeFromParentAndCleanup(true);
    }
}


/*************************************************************************/

void EnemyBase::addEnemy(float dt)
{
    if (activePlaneNum1 != 0 && activePlaneNum1 % 10 == 0) //创建中飞机
    {
        activePlaneNum1++;
        activePlaneNum2++;
        
        CCSprite *enemyPlane2;
        enemyPlane2 = CCSprite::createWithSpriteFrameName("enemy2.png");
        
        PlaneStruct *enemyPlane = PlaneStruct::create();
        enemyPlane->plane = enemyPlane2;
        enemyPlane->tag = 2;
        addChild(enemyPlane2);
        float x = CCRANDOM_0_1() * (CCDirector::sharedDirector()->getWinSize().width - enemyPlane2->getContentSize().width)
        + enemyPlane2->getContentSize().width/2 ;
        float y = CCDirector::sharedDirector()->getWinSize().height;
        enemyPlane2->setPosition(ccp(x, y));
        enemyArr->addObject(enemyPlane);
        
        
    }
    else if (activePlaneNum1 != 0 && activePlaneNum1 % 25 == 0) //打飞机
    {
        activePlaneNum1++;
        activePlaneNum3++;
        
        CCSprite *enemyPlane3;
        enemyPlane3 = CCSprite::createWithSpriteFrameName("enemy1.png");
        PlaneStruct *enemyPlane = PlaneStruct::create();
        enemyPlane->plane = enemyPlane3;
        enemyPlane->tag = 3;
        addChild(enemyPlane3);
        float x = CCRANDOM_0_1() * (CCDirector::sharedDirector()->getWinSize().width - enemyPlane3->getContentSize().width)
        + enemyPlane3->getContentSize().width/2 ;
        float y = CCDirector::sharedDirector()->getWinSize().height;
        enemyPlane3->setPosition(ccp(x, y));
        enemyArr->addObject(enemyPlane);
    }
    else //小飞机
    {
        activePlaneNum1++;
        CCSprite *enemyPlane1;
        enemyPlane1 = CCSprite::createWithSpriteFrameName("enemy1.png");
        PlaneStruct *enemyPlane = PlaneStruct::create();
        enemyPlane->plane = enemyPlane1;
        enemyPlane->tag = 1;
        addChild(enemyPlane1);
        float x = CCRANDOM_0_1() * (CCDirector::sharedDirector()->getWinSize().width - enemyPlane1->getContentSize().width)
        + enemyPlane1->getContentSize().width/2 ;
        float y = CCDirector::sharedDirector()->getWinSize().height;
        enemyPlane1->setPosition(ccp(x, y));
        enemyArr->addObject(enemyPlane);
    }

}


void EnemyBase::EnemyExplode(PlaneStruct *objp, CCSprite *bullet)
{
    //爆炸的动画
    CCSprite *enemy = objp->plane;
    CCAnimation *animation = CCAnimation::create();
    if (objp->tag == 1)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("enemy1_down.mp3");
        for (int i = 1; i <= 4; i++)
        {
            animation->addSpriteFrameWithFileName(CCString::createWithFormat("enemy1_down%d.png",i)->getCString());
        }
    }
    else if(objp->tag == 2)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("enemy2_down.mp3");
        for (int i = 1; i <= 4; i++)
        {
            animation->addSpriteFrameWithFileName(CCString::createWithFormat("enemy2_down%d.png",i)->getCString());
        }
    }
    else if(objp->tag == 3)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("enemy3_down.mp3");
        for (int i = 1; i <= 6; i++)
        {
            animation->addSpriteFrameWithFileName(CCString::createWithFormat("enemy3_down%d.png",i)->getCString());
        }
    }
    

    
    animation->setDelayPerUnit(0.1f);
    CCAnimate *action = CCAnimate::create(animation);
    
    //飞机消失
    CCSequence *seq = CCSequence::create(action,
                                         CCCallFuncND::create(this, callfuncND_selector(EnemyBase::deleteobj), (void*)bullet),
                                         NULL );
    enemy->runAction(seq);
}


















