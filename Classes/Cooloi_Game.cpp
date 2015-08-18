//
//  Cooloi_Game.cpp
//  oHitx
//
//  Created by ESoragoto on 8/18/15.
//
//

#include "Cooloi_Game.h"
#include <iostream>
#include <string>
#include <sstream>

namespace std
{
    template < typename T > std::string to_string( const T& n )
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        std::ostringstream os;
        os << n;
        return os.str();
        
#else
        
        return std::to_string(n);
        
#endif
    }
}

namespace Cooloi
{
    void Game::SetScale(cocos2d::Node *node)
    {
        node->setScale(Director::getInstance()->getVisibleSize().height / 1080);
    }
    
    void Game::RandTransitionFn(Scene* scene)
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