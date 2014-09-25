/* 
 * File:   Chick.cpp
 * Author: thedreamer
 * 
 * Created on September 24, 2014, 9:50 PM
 */

#include "Chick.h"

Chick::Chick() {
}

Chick::~Chick() {
}

Chick * Chick::createChick(const char * name, cocos2d::Vec2 origin){
    Chick * chick = new Chick();
    if(chick && chick->initWithSpriteFrameName(name)){
        chick->autorelease();
        chick->setOriginalPosition(origin);
        chick->setPosition(chick->getOriginalPosition());
        return chick;
    }
    CC_SAFE_DELETE(chick);
    return NULL;    
}