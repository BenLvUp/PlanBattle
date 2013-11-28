#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

int HelloWorld::score = 0;
CCLabelBMFont* HelloWorld::label = NULL;

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic( "game_music.mp3", true);
    
    score = 0;
    //1.添加基本元素
    bg1 = CCSprite::createWithSpriteFrameName("background.png");
    addChild(bg1);
    bg1->setAnchorPoint(ccp(0,0));
    bg1->setPosition(ccp(0, 0));
    
    bg2 = CCSprite::createWithSpriteFrameName("background.png");
    addChild(bg2);
    bg2->setAnchorPoint(ccp(0, 0));
    bg2->setPosition(ccp(0, 680));
    
    //飞机
    plan = Plan::create();
    addChild(plan);
    
    //子弹
    bullet = Bullet::create();
    addChild(bullet);
    
    //敌机
    EnemyBase *enemy = EnemyBase::create();
    addChild(enemy);

    
    //2.暂停按钮
    CCMenuItemImage *item = CCMenuItemImage::create("game_pause_nor.png",
                                                    "game_pause_pressed.png",
                                                    this,
                                                    menu_selector(HelloWorld::changeToPause));
	item->setPosition(ccp(50, size.height-50));
    CCMenu* menu = CCMenu::create(item, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu, 1);
    
    //3.分数级数
    label = CCLabelBMFont::create("0000", "font.fnt");
    this->addChild(label);
    label->setAnchorPoint(ccp(0, 0.5));
    label->setPosition(ccp(item->getPosition().x+30, size.height-50));
    label->setTag(20);
    
    //4.监听事件和其他
    schedule(schedule_selector(HelloWorld::moveBg), 0.1f); //屏幕背景滚动
    scheduleUpdate();

    return true;
}


void HelloWorld::moveBg(float t) //不断调整bg1的位置，bg2一直紧跟着bg1
{
    bg1->setPositionY(bg1->getPositionY()-5);
    bg2->setPositionY(bg1->getPositionY()+680);
    if(bg2->getPositionY() == 0)
    {
        bg1->setPositionY(0);
    }
}

void HelloWorld::changeToPause(CCObject *obj)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
    CCDirector::sharedDirector()->pause();
    //this->pauseSchedulerAndActions();
    //plan->pauseSchedulerAndActions();
    //bullet->pauseSchedulerAndActions();
    //enemy->pauseSchedulerAndActions();
    
    CCScene *pauseLayer = PauseLayer::scene();
    addChild(pauseLayer);
}


void HelloWorld::changeToGameOverLayer()
{
    CCScene *layer = GameOverLayer::scene();
    CCDirector::sharedDirector()->replaceScene(layer);
}






















