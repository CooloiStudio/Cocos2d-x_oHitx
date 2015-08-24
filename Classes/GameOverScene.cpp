//
//  GameOverScene.cpp
//  oHitx
//
//  Created by ESoragoto on 8/18/15.
//
//

#include "GameOverScene.h"
#include "Cooloi_Game.h"

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#include "HelloWorldScene.h"

GameOver::GameOver():
score_(0),
label_score_(nullptr),
label_record_(nullptr)
{
    
}

GameOver::~GameOver()
{
    
}

GameOver* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = GameOver::create();
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
#pragma mark -prepare variate
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
    
    label_score_ = Label::createWithSystemFont("",
                                               "Arial",
                                               64);
    label_score_->setTextColor(Color4B(0,
                                       0,
                                       0,
                                       255));
    
    label_score_->setPosition(Vec2(origin.x + visible_size.width / 2 ,
                                   origin.y + visible_size.height / 2));
    addChild(label_score_);
    
    label_record_ = Label::createWithSystemFont("This Game:",
                                                "Arial",
                                                70);
    label_record_->setTextColor(Color4B(0,
                                        0,
                                        0,
                                        255));
    label_record_->setPosition(Vec2(origin.x + visible_size.width / 2 ,
                                    origin.y
                                    + visible_size.height / 2
                                    + label_record_->getContentSize().height * 2));
    addChild(label_record_);
    
    auto * label_close = Label::createWithSystemFont("Repaly",
                                                     "Arial",
                                                     40);
    label_close->setTextColor(Color4B(0,0,0,255));
    
    auto closeItem = MenuItemLabel::create(label_close,
                                           CC_CALLBACK_1(GameOver::menuCloseCallback,
                                                         this));
    
    closeItem->setPosition(Vec2(origin.x + visible_size.width / 2 ,
                                origin.y
                                + visible_size.height / 2
                                - label_record_->getContentSize().height * 2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    return true;
}


void GameOver::menuCloseCallback(Ref* pSender)
{
    auto scene = HelloWorld::createScene();
    auto ts = TransitionShrinkGrow::create(1, scene);
    Director::getInstance()->replaceScene(ts);
}

void GameOver::DataUpdate()
{
    auto path = FileUtils::getInstance()->getWritablePath() + "score.json";
    auto temp = FileUtils::getInstance()->getStringFromFile(path);
    rapidjson::Document d;
    d.Parse<0>(temp.c_str());
    
    auto score = d["score"].GetInt();
    if (d["new"].GetBool())
    {
        label_record_->setString("New Record:" + std::to_string(score));
    }
    else
    {
        label_record_->setString("Record:" + std::to_string(score));
    }
    
    label_score_->setString("This Game:" + std::to_string(score_));
}
