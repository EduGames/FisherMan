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

    return true;
}
