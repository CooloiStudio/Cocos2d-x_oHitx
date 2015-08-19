//
//  AndroidLoadScene.h
//  oHitx
//
//  Created by ESoragoto on 8/19/15.
//
//

#ifndef __oHitx__AndroidLoadScene__
#define __oHitx__AndroidLoadScene__

#include "cocos2d.h"

USING_NS_CC;

class AndroidLoad : public Scene
{
public:
    AndroidLoad();
    ~AndroidLoad();
    
    virtual bool init();
    
    CREATE_FUNC(AndroidLoad);
    
    void SetTime(float t);
    
    void ChangeScene(float t);
};

#endif /* defined(__oHitx__AndroidLoadScene__) */
