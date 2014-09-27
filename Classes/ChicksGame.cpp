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
ChicksGame::ChicksGame(): _chicks (5), black_chicks(5) {
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
    
    _scoring = false;
    
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
    
    createChicks();
    
    _scoreDisplayLarge = LabelTTF::create();
    _scoreDisplayLarge->setFontSize(300);
    _scoreDisplayLarge->setFontName("fonts/font.ttf");
    _scoreDisplayLarge->setPosition(Vec2(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    _scoreDisplayLarge->setScale(0.2);
    _scoreDisplayLarge->setString("0");
    _scoreDisplayLarge->setVisible(false);
    this->addChild(_scoreDisplayLarge,kForeground);
}

void ChicksGame::update (float dt) {
}

bool ChicksGame::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event){
    if (_scoring) return true;
    for (auto chick: this->_chicks){
        if(chick->getBoundingBox().containsPoint(touch->getLocation())){
            chick->setIsTouched(true);
        }
    }
    
    return true;
}
void ChicksGame::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event){
    for (auto chick: this->_chicks){
        if(chick->getIsTouched()){
            if(!chick->getIsSolved())
                chick->setPosition(touch->getLocation());
        }
    }

}
void ChicksGame::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event){
    for (auto chick: this->_chicks){
        if(chick->getIsTouched() && !chick->getIsSolved()){
            Sprite * black_chick = black_chicks.at(_chicks.getIndex(chick));
            chick->setIsTouched(false);
            if(chick->getBoundingBox().containsPoint(black_chick->getPosition())){
                chick->setPosition(black_chick->getPosition());
                chick->setIsSolved(true);
                addScore();
            }else{
                chick->setPosition(chick->getOriginalPosition());
            }
        }
    }
}

void ChicksGame::createChicks(){
    std::string levelsFile = CCFileUtils::sharedFileUtils()->fullPathForFilename("data/chicks.plist");
    auto _chickss = Dictionary::createWithContentsOfFileThreadSafe(levelsFile.c_str());
    
    Chick *sprite;
    Sprite * black;
    int i= 1;
    DictElement* pElement = NULL;
    CCDICT_FOREACH(_chickss, pElement){
        Dictionary * chickk = (Dictionary *) pElement->getObject();
        auto x = chickk->valueForKey("x")->floatValue();
        auto y = chickk->valueForKey("y")->floatValue();
        auto x_black = chickk->valueForKey("x_black")->floatValue();
        auto y_black = chickk->valueForKey("y_black")->floatValue();
        
        auto name = CCString::createWithFormat("chick_%i.png", i);
        sprite = Chick::createChick(name->_string.c_str(), Vec2( x,y));
        
        sprite->setIsSolved(false);
        sprite->setIsTouched(false);
        _gameBatchNode->addChild(sprite, kForeground);
        _chicks.pushBack(sprite);
        
        black = Sprite::createWithSpriteFrameName(name->_string.c_str());
        black->setPosition(Vec2(x_black,y_black));
        black->setColor(Color3B::BLACK);
        _gameBatchNode->addChild(black, kMiddleground);
        black_chicks.pushBack(black);
        
        i++;
    }
}
void ChicksGame::addScore(){
    _scoring = true;
    _score++;
    auto name = CCString::createWithFormat("%i", _score);
    
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
        CCCallFuncN::create(this, callfuncN_selector(ChicksGame::bigScoreDone)),
        NULL)
    );
}

void ChicksGame::bigScoreDone (Node* pSender) {
    pSender->setScale(0.2);
    pSender->setVisible(false);
    _scoring = false;
}