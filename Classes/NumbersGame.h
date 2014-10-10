#ifndef __NUMBERSGAME_SCENE_H__
#define __NUMBERSGAME_SCENE_H__

#include "cocos2d.h"

enum {
    kBackground,
    kMiddleground,
    kForeground
};

class NumbersGame : public cocos2d::Layer
{
private:
    void createGameScreen (void);
    void createPools(void);
    void createActions(void);
    
    void resetFish();
    cocos2d::Vector<cocos2d::Sprite*> _fishPool;
    cocos2d::Sprite * _hook;
    int _fishPoolIndex;
    
    cocos2d::SpriteBatchNode * _gameBatchNode;
    cocos2d::Size _screenSize;
    
    float _fishInterval = 1.5;
    float _fishTimer;
    float _fishSpeed = 6;
    
    bool _running;
    bool _hook_pull;
    bool _hook_has_fish;
    cocos2d::LabelTTF * _scoreDisplay;
    cocos2d::LabelTTF * _scoreDisplayLarge;
    int _score;
    
    void menuCloseCallback(cocos2d::Ref* pSender);
public:
    NumbersGame();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(NumbersGame);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
    virtual void update (float dt);
    
    void fishingDone (Node* pSender);
    void bigScoreDone (Node* pSender);
};

#endif // __NUMBERSGAME_SCENE_H__
