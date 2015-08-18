#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
#pragma mark - Initialization
    
public:
    HelloWorld();
    ~HelloWorld();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
#pragma mark - Callbakc function
    
    // a selector callback
    void MenuCloseCallback(cocos2d::Ref* pSender);
    
#pragma mark - Sprite Management
    
    void AddTarget();
    void SpriteMoveFinished(Node *sender);
    void GameLogic(float dt);
    void update(float dt);
    
#pragma mark - Touch
    
    virtual bool onTouchBegan(Touch *touch,
                              Event *event);
    
    void onTouchEnded(Touch *touch,
                      Event *event);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    EventListenerTouchOneByOne *listener_touch_;
    
protected:
    Vector<Sprite *> targets_;
    Vector<Sprite *> bullets_;
};//HelloWorld : public cocos2d::Layer

#endif // __HELLOWORLD_SCENE_H__
