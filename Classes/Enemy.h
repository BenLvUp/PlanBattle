#ifndef __plangame__Enemy__
#define __plangame__Enemy__

#include <iostream>
#include "cocos2d.h"
#include "Bullet.h"
#include "HelloWorldScene.h"
USING_NS_CC;

class PlaneStruct;

//1.敌机基类
class EnemyBase : public CCLayer
{
public:
    int activePlaneNum1, activePlaneNum2, activePlaneNum3;
    EnemyBase();
    ~EnemyBase();
    virtual bool init();
    static CCArray *enemyArr;
    void deleteobj(CCNode* sender, void* t);
    void heroExplode();
    void deletePlayer();
    void moveEnemy(float dt);
    void collisionDetection(float dt);
    
    void addEnemy(float dt);
    void EnemyExplode(PlaneStruct *objp, CCSprite *bullet);
    
    CREATE_FUNC(EnemyBase);
};

class PlaneStruct : public CCNode
{
public:
    CCSprite *plane;
    int tag;
    CREATE_FUNC(PlaneStruct);
};


#endif /* defined(__plangame__Enemy__) */
