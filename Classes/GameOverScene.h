//
//  GameOverScene.h
//  oHitx
//
//  Created by ESoragoto on 8/18/15.
//
//

#ifndef __oHitx__GameOverScene__
#define __oHitx__GameOverScene__

#include "cocos2d.h"

USING_NS_CC;

class GameOver : public cocos2d::Scene
{
public:
    GameOver();
    ~GameOver();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static GameOver* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);
    
    void DataUpdate();
    
public:
    
private:
    Label *label_score_;
    
};


#endif /* defined(__oHitx__GameOverScene__) */