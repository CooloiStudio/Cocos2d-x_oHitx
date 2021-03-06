#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "Cooloi_Game.h"
#include "AndroidLoadScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("oHitx", Rect(0, 0, 1080, 1920));
        director->setOpenGLView(glview);
    }
    
    director->getOpenGLView()->setDesignResolutionSize(1080,
                                                       1920,
                                                       ResolutionPolicy::NO_BORDER);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    
    auto scene = AndroidLoad::create();
//    TransitionScene *ts;
//    ts = TransitionShrinkGrow::create(1, scene);
//    director->replaceScene(ts);

    // create a scene. it's an autorelease object
//    auto scene = HelloWorld::createScene();
//    TransitionScene *ts = TransitionShrinkGrow::create(1, scene);
//    Director::getInstance()->replaceScene(ts);
    Director::getInstance()->replaceScene(scene);
    
    scene->SetTime(3.0);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
