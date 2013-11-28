#include "StartLayer.h"
#include "SimpleAudioEngine.h"

//1.
CCScene* StartLayer1::scene()
{
    CCScene *scene = CCScene::create();
    StartLayer1 *layer = StartLayer1::create();
    scene->addChild(layer);
    return scene;
}


bool StartLayer1::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *player = CCSprite::createWithSpriteFrameName("game_loading2.png");
    addChild(player);
    player->setPosition(ccp(size.width/2, size.height/2));
    
    CCAnimation *animation = CCAnimation::create();
    for (int i = 1; i <= 4; i++)
    {
        animation->addSpriteFrameWithFileName(CCString::createWithFormat("game_loading%d.png",i)->getCString());
    }
    animation->setDelayPerUnit(0.4f);
    CCAnimate *action = CCAnimate::create(animation);
    CCSequence *seq = CCSequence::create(action,
                                         CCCallFunc::create(this, callfunc_selector(StartLayer2::changeScene) ),
                                         NULL );
    player->runAction(seq);
    return true;
}

void StartLayer1::changeScene(CCObject *obj)
{
    CCScene *layer = StartLayer2::scene();
    CCDirector::sharedDirector()->replaceScene(layer);
}


/////////////////////////////////////////////////////////////////////////
//2.
CCScene* StartLayer2::scene()
{
    CCScene *scene = CCScene::create();
    StartLayer2 *layer = StartLayer2::create();
    scene->addChild(layer);
    return scene;
}


bool StartLayer2::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    //1.
    CCSprite *bg = CCSprite::createWithSpriteFrameName("background.png");
    addChild(bg);
    bg->setPosition(ccp(size.width/2, size.height/2));
    
    //2.
    CCSprite *bgIcom = CCSprite::createWithSpriteFrameName("shoot_copyright.png");
    addChild(bgIcom);
    bgIcom->setPosition(ccp(size.width/2, size.height/2));
    
//    //3.退出游戏按钮
//    CCMenuItemImage *item = CCMenuItemImage::create("btn_finish.png",
//                                                    "btn_finish.png",
//                                                    this,
//                                                    menu_selector(StartLayer2::menuCloseCallback));
//	item->setPosition(ccp(size.width - 100, 50));
//    CCMenu* menu = CCMenu::create(item, NULL);
//    menu->setPosition(CCPointZero);
//    this->addChild(menu, 1);
    
    
    //切换到战斗场景
    CCAnimation *animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName("background.png");
    CCAnimate *action = CCAnimate::create(animation);
    CCSequence *seq = CCSequence::create(action,
                                         CCDelayTime::create(1.0),
                                         CCCallFunc::create(this, callfunc_selector(StartLayer2::changeScene)),
                                         NULL );
    bg->runAction(seq);
    return true;
}

void StartLayer2::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void StartLayer2::changeScene()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("game_over.mp3"); 
    CCScene *layer = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(layer);
}



/////////////////////////////////////////////////////////////////////////

CCScene* PauseLayer::scene()
{
    CCScene *scene = CCScene::create();
    PauseLayer *layer = PauseLayer::create();
    scene->addChild(layer);
    return scene;
}

///////////////////////////////////////////////////////////////
//3.
bool PauseLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("achievement.mp3");
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    setTouchEnabled(true);
    
    //灰色半透明背景
    ccColor4B color = ccc4(0, 0, 0, 100);
    colorLayer = CCLayerColor::create(color);
    CCSize c_size(size.width, size.height);    //宽和高
    colorLayer->setPosition(ccp(0, 0)); //设置位置，注意，CCLayerColor 的贴图点是左下角，而且还改不了……
    colorLayer->setContentSize(c_size); //设置这块区域的大小
    this->addChild(colorLayer, 0);
    
    
    //恢复游戏按钮
    CCMenuItemImage *item = CCMenuItemImage::create("game_resume_nor.png",
                                                    "game_resume_pressed.png",
                                                    this,
                                                    menu_selector(PauseLayer::backToGame));
	item->setPosition(ccp(size.width/2, size.height/2));
    CCMenu* menu = CCMenu::create(item, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu, 1);
    return true;
}

void PauseLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}



void PauseLayer::backToGame(cocos2d::CCObject *pSender)
{
    this->removeFromParentAndCleanup(true);
    CCDirector::sharedDirector()->resume();
}



///////////////////////////////////////////////////////////////
//4.

CCScene* GameOverLayer::scene()
{
    CCScene *scene = CCScene::create();
    GameOverLayer *layer = GameOverLayer::create();
    scene->addChild(layer);
    return scene;
}


bool GameOverLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("game_over.mp3");    
    //1.
    CCSprite *bg = CCSprite::createWithSpriteFrameName("gameover.png");
    addChild(bg);
    bg->setPosition(ccp(size.width/2, size.height/2));
    
    //2.显示得分
    char s[10];
    sprintf(s, "%d", HelloWorld::score);
    
    CCLabelBMFont *label = CCLabelBMFont::create(s, "font.fnt");
    this->addChild(label);
    label->setPosition(ccp(size.width/2, size.height*5/9));

    
    //3.重新开始游戏按钮
    CCMenuItemImage *item = CCMenuItemImage::create("btn_finish.png",
                                                    "btn_finish.png",
                                                    this,
                                                    menu_selector(StartLayer1::changeScene));
	item->setPosition(ccp(size.width/2, 50));
    CCMenu* menu = CCMenu::create(item, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu, 1);
    return true;
}
























