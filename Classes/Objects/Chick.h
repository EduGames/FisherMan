/* 
 * File:   Chick.h
 * Author: thedreamer
 *
 * Created on September 24, 2014, 9:50 PM
 */

#ifndef CHICK_H
#define	CHICK_H
#include "cocos2d.h"

class Chick : public cocos2d::Sprite{
public:
    Chick();
    static Chick * createChick(const char * name, cocos2d::Vec2 origin);
    virtual ~Chick();
    CC_SYNTHESIZE(cocos2d::Vec2, _originalPosition, OriginalPosition);
    CC_SYNTHESIZE(bool, _isSolved, IsSolved);
    CC_SYNTHESIZE(bool, _isTouched, IsTouched);
private:
};

#endif	/* CHICK_H */

