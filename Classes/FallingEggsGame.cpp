/* 
 * File:   FallingEggsGame.cpp
 * Author: thedreamer
 * 
 * Created on October 1, 2014, 9:57 PM
 */

#include "FallingEggsGame.h"
USING_NS_CC;
FallingEggsGame::FallingEggsGame() : _eggPool(20)
{
}
Scene* FallingEggsGame::createScene()
{
    auto scene = Scene::create();
    auto layer = FallingEggsGame::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool FallingEggsGame::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    _screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _score = 0;
    //create game screen elements
    createGameScreen();
    //create object pools
    //createPools();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(FallingEggsGame::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(FallingEggsGame::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(FallingEggsGame::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        
    this->schedule(schedule_selector(FallingEggsGame::update));
    return true;
}


void FallingEggsGame::createGameScreen () {
    Sprite * bg = Sprite::create("bg.png");
    bg->setPosition(Vec2(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(bg, kBackground);
    
//    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprites.plist");
//    _gameBatchNode = SpriteBatchNode::create("sprites.png", 100);
//
//    this->addChild(_gameBatchNode, kForeground);
    
    _scoreDisplay = LabelTTF::create();
    _scoreDisplay->setFontName("fonts/font.ttf");
    _scoreDisplay->setAnchorPoint(Vec2(1,0.5));
    _scoreDisplay->setFontSize(20);
    _scoreDisplay->setPosition(Vec2(_screenSize.width * 0.9f, _screenSize.height * 0.94f));
    _scoreDisplay->setString("0");
    this->addChild(_scoreDisplay,kForeground);
    
    
    _scoreDisplayLarge = LabelTTF::create();
    _scoreDisplayLarge->setFontSize(300);
    _scoreDisplayLarge->setFontName("fonts/font.ttf");
    _scoreDisplayLarge->setPosition(Vec2(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    _scoreDisplayLarge->setScale(0.2);
    _scoreDisplayLarge->setString("0");
    _scoreDisplayLarge->setVisible(false);
    this->addChild(_scoreDisplayLarge,kForeground);
}


void FallingEggsGame::update (float dt) {
    if (!_running) return;
}

bool FallingEggsGame::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event){
    if (!_running) _running = true;
    return true;
}
void FallingEggsGame::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event){

}
void FallingEggsGame::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event){

}

void FallingEggsGame::resetEgg(){

}

void FallingEggsGame::bigScoreDone (Node* pSender) {
    pSender->setScale(0.2);
    pSender->setVisible(false);
}

FallingEggsGame::~FallingEggsGame() {
}

