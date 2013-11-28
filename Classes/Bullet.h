#ifndef __plangame__Bullet__
#define __plangame__Bullet__

#include <iostream>
#include "cocos2d.h"
#include "Plan.h"
USING_NS_CC;

class Bullet : public CCLayer
{
public:
    Bullet();
    ~Bullet();
    virtual bool init();
    static CCArray *bulletArr;
    void addbullet(float t);
    void movebullet(float t);
    
    static bool isActive;
    
    CREATE_FUNC(Bullet);
    
};

#endif /* defined(__plangame__Bullet__) */
