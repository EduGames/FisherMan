#ifndef FALLINGEGGSGAME_H
#define	FALLINGEGGSGAME_H
#include "cocos2d.h"

enum {
    kBackground,
    kMiddleground,
    kForeground
};
class FallingEggsGame : public cocos2d::Layer {
public:
    FallingEggsGame();
    virtual ~FallingEggsGame();
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(FallingEggsGame);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
    virtual void update (float dt);
    
    void bigScoreDone (Node* pSender);
private:
void createGameScreen (void);
    void createPools(void);
    void createActions(void);
    
    void resetEgg();
    cocos2d::Vector<cocos2d::Sprite*> _eggPool;
    int _eggPoolIndex;
    
    cocos2d::SpriteBatchNode * _gameBatchNode;
    cocos2d::Size _screenSize;
    
    float _eggInterval = 1.5;
    float _eggTimer;
    float _eggSpeed = 6;
    
    bool _running;
    bool _hook_pull;
    cocos2d::LabelTTF * _scoreDisplay;
    cocos2d::LabelTTF * _scoreDisplayLarge;
    int _score;
};

#endif	/* FALLINGEGGSGAME_H */

