//
//  Cooloi_RandTransition.cpp
//  oHitx
//
//  Created by ESoragoto on 8/18/15.
//
//

#include "Cooloi_RandTransition.h"

namespace Cooloi
{
    void RandTransition::RandTransitionFn(Scene* scene)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        
        auto ts = TransitionShrinkGrow::create(1, scene);
        Director::getInstance()->replaceScene(ts);
        
#else
        
        TransitionScene *ts;
        
        switch (rand() % 5)
        {
            case 0:
                ts = TransitionShrinkGrow::create(1, scene);
                break;
            case 1:
                ts = TransitionJumpZoom::create(1, scene);
                break;
            case 2:
                ts = TransitionProgressInOut::create(1, scene);
                break;
            case 3:
                ts = TransitionZoomFlipAngular::create(1, scene);
                break;
            case 4:
                ts = TransitionFadeDown::create(1, scene);
                break;
            default:
                break;
        }
        
        Director::getInstance()->replaceScene(ts);
        
#endif
    }
}