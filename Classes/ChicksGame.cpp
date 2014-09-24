/* 
 * File:   ChicksGame.cpp
 * Author: thedreamer
 * 
 * Created on September 24, 2014, 9:00 PM
 */

#include "ChicksGame.h"
USING_NS_CC;

ChicksGame::~ChicksGame() {
}
ChicksGame::ChicksGame() {
}
Scene* ChicksGame::createScene()
{
    auto scene = Scene::create();
    auto layer = ChicksGame::create();
    scene->addChild(layer);
    return scene;
}
bool ChicksGame::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    _screenSize = Director::getInstance()->getVisibleSize();
    
     _score = 0;
    //create game screen elements
    createGameScreen();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(ChicksGame::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ChicksGame::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ChicksGame::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        
    this->schedule(schedule_selector(ChicksGame::update));
    return true;
}

void ChicksGame::createGameScreen () {
    Sprite * bg = Sprite::create("farm_bg.png");
    bg->setPosition(Vec2(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(bg, kBackground);
    
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("chicks_sprites.plist");
    _gameBatchNode = SpriteBatchNode::create("chicks_sprites.png", 100);

    this->addChild(_gameBatchNode, kForeground);
}

void ChicksGame::update (float dt) {
}

bool ChicksGame::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event){
    return true;
}
void ChicksGame::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event){

}
void ChicksGame::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event){

}