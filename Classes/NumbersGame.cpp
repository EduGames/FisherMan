#include "NumbersGame.h"

USING_NS_CC;
NumbersGame::NumbersGame() : _fishPool(20)
{
}
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
    
    _screenSize = Director::getInstance()->getVisibleSize();
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

void NumbersGame::createGameScreen () {
    Sprite * bg = Sprite::create("bg.png");
    bg->setPosition(Vec2(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(bg, kBackground);
    
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprites.plist");
    _gameBatchNode = SpriteBatchNode::create("sprites.png", 100);

    this->addChild(_gameBatchNode, kForeground);
    
    
}
void NumbersGame::createPools () {
    Sprite * sprite;
    int i,output;
    
    _fishPoolIndex = 0;
    for (i = 0; i < _fishPool.capacity(); i++) {
        output = 1 + (rand() % (int)(6 - 2));
        auto name = CCString::createWithFormat("fish_%i.png", output);
        sprite = Sprite::createWithSpriteFrameName(name->_string);
        sprite->setVisible(false);
        sprite->setScale(0.2);
        _gameBatchNode->addChild(sprite, kMiddleground);
        _fishPool.pushBack(sprite);
    }
}
void NumbersGame::createActions () {
    
}
void NumbersGame::update (float dt) {
    if (!_running) return;
    //update timers
    _fishTimer += dt;

    if (_fishTimer > _fishInterval) {
        _fishTimer = 0;
        this->resetFish();
    }
}
bool NumbersGame::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event){
    if (!_running) _running = true;
    return true;
}
void NumbersGame::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event){}

void NumbersGame::resetFish(){
    Sprite * fish = (Sprite *) _fishPool.at(_fishPoolIndex);
    _fishPoolIndex++;
    if (_fishPoolIndex == _fishPool.size())   _fishPoolIndex = 0;

    int meteor_y = rand() % (int) (_screenSize.height * 0.8f) + _screenSize.height * 0.1f;

    fish->stopAllActions();
    
    fish->setPosition(Vec2(_screenSize.width + fish->getBoundingBox().size.width * 0.5,meteor_y));
    auto swim = MoveTo::create(_fishSpeed, Vec2(0-fish->getBoundingBox().size.width * 0.5,meteor_y));

    fish->setVisible ( true );
    fish->runAction(swim);
}