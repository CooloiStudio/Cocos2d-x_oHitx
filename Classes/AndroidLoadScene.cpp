//
//  AndroidLoadScene.cpp
//  oHitx
//
//  Created by ESoragoto on 8/19/15.
//
//

#include "AndroidLoadScene.h"
#include "HelloWorldScene.h"
#include "Cooloi_Game.h"

AndroidLoad::AndroidLoad()
{
    
}

AndroidLoad::~AndroidLoad()
{
    
}

bool AndroidLoad::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visible_size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
#pragma mark -add a layer to be background
    auto layer = LayerColor::create(Color4B(255,
                                            255,
                                            255,
                                            255));
    layer->setContentSize(visible_size);
    layer->setPosition(origin);
    
    this->addChild(layer,
                   0);
    
    auto ues = Sprite::create("UkiyoESoragoto128.png");
    ues->setPosition(Vec2(origin.x
                          + visible_size.width * .5
                          - ues->getContentSize().width * .5,
                          origin.y
                          + visible_size.height * .5));
    addChild(ues);
    
    auto label_ues = Label::createWithSystemFont("@UkiyoESoragoto",
                                                 "Arial",
                                                 30);
    label_ues->setPosition(origin.x
                           + visible_size.width * .5
                           + label_ues->getContentSize().width * .5,
                           origin.y
                           + visible_size.height * .5);
    label_ues->setTextColor(Color4B(0,0,0,255));
    
    addChild(label_ues);
    
    auto cocos = Sprite::create("cocos2d-x_logo.png");
    cocos->setPosition(Vec2(origin.x
                            + visible_size.width
                            - cocos->getContentSize().width * .6,
                            origin.y
                            + cocos->getContentSize().height * .6));
    addChild(cocos);
    
    auto komori = Sprite::create("taira-komori.jpn.org.png");
    komori->setPosition(Vec2(origin.x
                             + visible_size.width
                             - cocos->getContentSize().width * 1.4,
                             origin.y
                             + komori->getContentSize().height * .6
                             + cocos->getContentSize().height * .1
                             ));
    addChild(komori);
    
    
    return true;
}

void AndroidLoad::SetTime(float t)
{
    scheduleOnce(schedule_selector(AndroidLoad::ChangeScene) , t);
}

void AndroidLoad::ChangeScene(float t)
{
    auto scene = HelloWorld::createScene();
//    TransitionScene *ts = TransitionShrinkGrow::create(1, scene);
    Director::getInstance()->replaceScene(scene);
}