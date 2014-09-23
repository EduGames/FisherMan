#include "NumbersGame.h"
#include "SimpleAudioEngine.h"

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

    _score = 0;
    _hook_has_fish = false;
    //create game screen elements
    createGameScreen();
    //create object pools
    createPools();
    //create CCActions
    createActions();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(NumbersGame::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(NumbersGame::onTouchEnded, this);
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
    
    _hook = Sprite::create("hook.png");
    _hook->setScale(0.1);
    _hook->setPosition(Vec2(_screenSize.width * 0.5f, _hook->getBoundingBox().size.height * 0.5));
    this->addChild(_hook, kMiddleground);
    
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
    
    _fishTimer += dt;
    if (_fishTimer > _fishInterval) {
        _fishTimer = 0;
        this->resetFish();
    }
    
    if(_hook_has_fish) return;
    
    if (_hook_pull){
        _hook->setPosition(_hook->getPositionX(),_hook->getPositionY() + 5);
        if(_hook->getPositionY() > _screenSize.height - _hook->getBoundingBox().size.height /2)
            _hook->setPositionY( _screenSize.height - _hook->getBoundingBox().size.height /2);
        
        for (auto fish: this->_fishPool)
        {
            if(fish->getBoundingBox().intersectsRect(_hook->getBoundingBox()))
            {
                fish->stopAllActions();
                _hook_has_fish = true;
                _hook_pull = false;
                
                auto fishing = MoveTo::create(
                    ( (_screenSize.height - _hook->getPositionY()) * 0.002)
                    , Vec2(_hook->getPositionX(),_screenSize.height));
                auto rotate = RotateTo::create(0.2,90);
                fish->runAction(
                 CCSequence::create(
                    fishing->clone(),
                    CCCallFuncN::create(this, callfuncN_selector(NumbersGame::fishingDone)),
                    NULL)
                );
                fish->runAction(rotate);
                _hook->runAction(fishing);
                _hook->setVisible(false);
            }
        }
    }else{
        _hook->setPosition(_hook->getPositionX(),_hook->getPositionY() - 3);
        if(_hook->getPositionY() < _hook->getBoundingBox().size.height /2)
            _hook->setPositionY( _hook->getBoundingBox().size.height /2);
    }
}
bool NumbersGame::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event){
    if (!_running) _running = true;
    _hook_pull = true;
    return true;
}
void NumbersGame::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event){
    _hook_pull = false;
}

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

void NumbersGame::fishingDone (Node* pSender) {
    pSender->setVisible(false);
    pSender->setRotation(0);
    pSender->setPosition(0,0);
    _score++;
    auto name = CCString::createWithFormat("%i", _score);
    _scoreDisplay->setString(name->_string);
    _scoreDisplayLarge->setString(name->_string);
    _scoreDisplayLarge->setVisible(true);

    char numstr[21]; // enough to hold all numbers up to 64-bits
    std::sprintf(numstr, "%i", _score);
    std::string result__ = numstr + std::string("_.wav");
    const char * audio_file = result__.c_str();
    if(_score < 11)
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(audio_file);

    _scoreDisplayLarge->runAction(CCSequence::create(
        EaseBackOut::create(ScaleTo::create(4,1)),
        CCCallFuncN::create(this, callfuncN_selector(NumbersGame::bigScoreDone)),
        NULL)
    );
}
void NumbersGame::bigScoreDone (Node* pSender) {
    pSender->setScale(0.2);
    pSender->setVisible(false);
    _hook_has_fish = false;
    _hook->setVisible(true);
}