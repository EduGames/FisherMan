#include "NumbersGame.h"

USING_NS_CC;

Scene* NumbersGame::createScene()
{
    auto scene = Scene::create();
    auto layer = NumbersGame::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool NumbersGame::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //create game screen elements
    createGameScreen();
    //create object pools
    createPools();
    //create CCActions
    createActions();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(NumbersGame::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(NumbersGame::onTouchMoved, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        
    this->schedule(schedule_selector(NumbersGame::update));
    return true;
}

void NumbersGame::createGameScreen () {}
void NumbersGame::createPools () {}
void NumbersGame::createActions () {}
void NumbersGame::update (float dt) {}
bool NumbersGame::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event){return true;}
void NumbersGame::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event){}