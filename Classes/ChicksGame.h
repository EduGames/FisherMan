/* 
 * File:   ChicksGame.h
 * Author: thedreamer
 *
 * Created on September 24, 2014, 9:00 PM
 */

#ifndef CHICKSGAME_H
#define	CHICKSGAME_H

#include "cocos2d.h"
enum {
    kBackground,
    kMiddleground,
    kForeground
};
class ChicksGame : public cocos2d::Layer {
public:
    virtual ~ChicksGame();
    ChicksGame();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ChicksGame);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
    virtual void update (float dt);
    
private:
    void createGameScreen (void);

    cocos2d::LabelTTF * _scoreDisplayLarge;
    int _score;    
    
    cocos2d::SpriteBatchNode * _gameBatchNode;
    cocos2d::Size _screenSize;
};

#endif	/* CHICKSGAME_H */

