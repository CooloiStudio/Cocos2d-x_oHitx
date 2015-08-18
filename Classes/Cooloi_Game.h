//
//  Cooloi_Game.h
//  oHitx
//
//  Created by ESoragoto on 8/18/15.
//
//

#ifndef __oHitx__Cooloi_Game__
#define __oHitx__Cooloi_Game__

#include "cocos2d.h"

USING_NS_CC;

namespace Cooloi
{
    class Game
    {
    public:
        static void SetScale(Node *node);
        static void RandTransitionFn(Scene* scene);
    };
}

#endif /* defined(__oHitx__Cooloi_Game__) */
