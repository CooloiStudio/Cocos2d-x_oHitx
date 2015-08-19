#include "HelloWorldScene.h"
#include "Cooloi_Game.h"
#include <math.h>

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#include "GameOverScene.h"
#include "iostream"

using namespace cocos2d::ui;

#pragma mark - Initialization

HelloWorld::HelloWorld():
targets_(NULL),
bullets_(NULL),
rank_(1),
pwoer_(10),
score_(0),
hit_(0),
exp_(0)
{}//HelloWorld::HelloWorld

HelloWorld::~HelloWorld()
{
    if (0 < targets_.size())
    {
        targets_.shrinkToFit();
    }
    
    if (0 < bullets_.size())
    {
        bullets_.shrinkToFit();
    }
}//HelloWorld::~HelloWorld

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    //
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}//HelloWorld::createScene

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
#pragma mark -listener
    listener_touch_ = EventListenerTouchOneByOne::create();
    listener_touch_->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan,
                                                  this);
    listener_touch_->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded,
                                                  this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_touch_,
                                                             this);
    
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
    
#pragma mark -add player sprite
    // add "HelloWorld" splash screen"
    auto player1 = Sprite::create("xo0002.png");
    Cooloi::Game::SetScale(player1);
    
    // position the sprite on the center of the screen
    player1->setPosition(Vec2(origin.x + player1->getContentSize().width / 2,
                              origin.y + visible_size.height / 2));
    player1->setTag(233);
    
    // add the sprite as a child to this layer
    this->addChild(player1,
                   0);
    
#pragma mark -add GameLogic
    this->schedule(schedule_selector(HelloWorld::GameLogic),
                   1.0);
    this->schedule(schedule_selector(HelloWorld::update));
    
    LableInit();
    
    addChild(label_rank_);
    addChild(label_score_);
    addChild(label_pwoer_);
    
    return true;
}// HelloWorld::init

#pragma mark - Callbakc function

#pragma mark - Sprite Management

void HelloWorld::AddTarget()
{
    auto window_size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto *target = Sprite::create("xo0001.png");
    Cooloi::Game::SetScale(target);
    
    auto min_y = origin.y + target->getContentSize().height / 2;
    auto max_y = origin.y + window_size.height - target->getContentSize().height / 2;
    
    auto range_y = max_y - min_y;
    auto actual_y = (rand() % (int)range_y) + min_y;
    
    target->setPosition(Vec2(window_size.width
                             + (target->getContentSize().width / 2)
                             + origin.x,
                             actual_y));
    
    this->addChild(target);
    target->setTag(1);
    targets_.pushBack(target);
    
    auto min_duration = (int)2000 / (pow(1.2,rank_ - 1));
    auto max_duration = (int)8000 / (pow(1.2,rank_ - 1));
    
    auto range_duration = max_duration - min_duration;
    auto actural_duration = (rand() % (int)range_duration) + min_duration;
    
    actural_duration = actural_duration / 1000.0;
    
    auto *action_move = MoveTo::create((float)actural_duration,
                                       Vec2(0 - target->getContentSize().width / 2,
                                            actual_y));
    auto *action_move_done = CallFuncN::create(this,
                                               callfuncN_selector(HelloWorld::SpriteMoveFinished));
    target->runAction(Sequence::create(action_move,
                                       action_move_done,
                                       NULL));
}//HelloWorld::addTarget

void HelloWorld::SpriteMoveFinished(Node *sender)
{
    auto *sprite = (Sprite *)sender;
    this->removeChild(sprite,
                      true);
    if (1 == sprite->getTag())
    {
        targets_.eraseObject(sprite);
        DataUpdateMiss();
    }
    else if (2 == sprite->getTag())
    {
        bullets_.eraseObject(sprite);
    }
    
}//HelloWorld::spreiteMoveFinshed

void HelloWorld::GameLogic(float dt)
{
    AddTarget();
}//HelloWorld::GameLogic

void HelloWorld::update(float dt)
{
    Vector<Sprite *> targets_to_delete;
    Vector<Sprite *> bullets_to_delete;
    
    for (auto bullet : bullets_)
    {
        auto bullet_rect = Rect(bullet->getPosition().x
                                - bullet->getContentSize().width * bullet->getScale() / 2,
                                bullet->getPosition().y
                                - bullet->getContentSize().height * bullet->getScale() / 2,
                                bullet->getContentSize().width * bullet->getScale(),
                                bullet->getContentSize().height * bullet->getScale());
        for (auto target : targets_)
        {
            auto target_rect = Rect(target->getPosition().x
                                    - target->getContentSize().width * target->getScale() / 2,
                                    target->getPosition().y
                                    - target->getContentSize().height * target->getScale() / 2,
                                    target->getContentSize().width * target->getScale(),
                                    target->getContentSize().height * target->getScale());
            
            if (bullet_rect.intersectsRect(target_rect))
            {
                targets_to_delete.pushBack(target);
                bullets_to_delete.pushBack(bullet);
                log("hit");
                DataUpdateHit();
            }
        }
    }
    
    for (auto target : targets_to_delete)
    {
        targets_.eraseObject(target);
        this->removeChild(target);
    }
    
    for (auto bullet : bullets_to_delete)
    {
        bullets_.eraseObject(bullet);
        this->removeChild(bullet);
    }
    
    targets_to_delete.shrinkToFit();
    bullets_to_delete.shrinkToFit();
}

#pragma mark - Lable Management

void HelloWorld::LableInit()
{
    label_rank_ = Label::createWithSystemFont("",
                                              "Arial",
                                              40);
    label_rank_->setTextColor(Color4B(0,0,0,255));
    
    label_score_ = Label::createWithSystemFont("",
                                               "Arial",
                                               40);
    label_score_->setTextColor(Color4B(0,0,0,255));
    
    label_pwoer_ = Label::createWithSystemFont("",
                                               "Arial",
                                               32);
    label_pwoer_->setTextColor(Color4B(0,0,0,255));
    
    LabelUpdate();
}

void HelloWorld::LabelUpdate()
{
    auto visible_size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    label_rank_->setString(" x" + std::to_string(rank_) + " ");
    label_rank_->setPosition(Vec2(origin.x + label_rank_->getContentSize().width / 2,
                                  origin.y
                                  + visible_size.height
                                  - label_rank_->getContentSize().height / 2));
    
    label_score_->setString(" " + std::to_string(score_));
    label_score_->setPosition(Vec2(origin.x
                                   + label_score_->getContentSize().width / 2,
                                   origin.y
                                   + visible_size.height
                                   - label_rank_->getContentSize().height
                                   - label_score_->getContentSize().height / 2));
    
    if(0 > pwoer_) pwoer_ = 0;
    label_pwoer_->setString(" " + std::to_string(pwoer_));
    label_pwoer_->setPosition(Vec2(origin.x + label_pwoer_->getContentSize().width / 2,
                                   origin.y + label_pwoer_->getContentSize().height / 2));
}

#pragma mark - Touch

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch,
                              cocos2d::Event *event)
{
    return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch,
                              cocos2d::Event *event)
{
    if (0 >= pwoer_)
    {
        return;
    }
    DataUpdateShoot();
    
    //获取点击位置
    auto location_in_view = touch->getLocationInView();
    auto location = Director::sharedDirector()->convertToGL(location_in_view);
    auto visible_size = Director::getInstance()->getVisibleSize();
    auto player_sprite = this->getChildByTag(233);
    
    auto bullet = Sprite::create("xo0002.png");
    bullet->setPosition(player_sprite->getPosition());
    
    auto off_x = location.x - bullet->getPosition().x;
    auto off_y = location.y - bullet->getPosition().y;
    
    if (0 >= off_x) return;
    Cooloi::Game::SetScale(bullet);
    this->addChild(bullet);
    bullets_.pushBack(bullet);
    
    auto real_x = visible_size.width + (bullet->getContentSize().width / 2);
    auto ratio = off_y / off_x;
    auto real_y = real_x * ratio + bullet->getPosition().y;
    auto read_destination = Point(real_x,
                                  real_y);
    
    auto off_real_x = real_x - bullet->getPosition().x;
    auto off_real_y = real_y - bullet->getPosition().y;
    auto length = sqrtf(off_real_x * off_real_x + off_real_y * off_real_y);
    
    auto velocity = 480 / 1;
    auto real_move_duration = length / velocity;
    
    bullet->runAction(Sequence::create(MoveTo::create(real_move_duration,
                                                      read_destination),
                                       CallFuncN::create(this,
                                                         callfuncN_selector(HelloWorld::SpriteMoveFinished)),
                                       NULL));
}

void HelloWorld::DataUpdateHit()
{
    score_ = score_ + rank_;
    if (233 > rank_)
    {
        if(10 <= exp_)
        {
            exp_ = 0;
            rank_++;
        }
        else
            exp_++;
    }
    else
        rank_ = 233;
    pwoer_ = pwoer_ + (rank_ + 1) / 2;
    LabelUpdate();
}

void HelloWorld::DataUpdateShoot()
{
    pwoer_--;
    LabelUpdate();
}

void HelloWorld::DataUpdateMiss()
{
    if (0 < pwoer_)
    {
        pwoer_ = pwoer_ - (rank_ + 2 / 3);
        LabelUpdate();
    }
    else
    {
        auto path = FileUtils::getInstance()->getWritablePath() + "score.json";
        rapidjson::Document d;
        if (!FileUtils::getInstance()->isFileExist(path))
        {
            d.SetObject();
            d.AddMember("score", score_, d.GetAllocator());
            d.AddMember("new", true, d.GetAllocator());
        }
        else
        {
            auto temp = FileUtils::getInstance()->getStringFromFile(path);
            d.Parse<0>(temp.c_str());
            if(d["score"].GetInt() < score_)
            {
                d["score"] = score_;
                d["new"] = true;
            }
            else
            {
                d["new"] = false;
            }
        }
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
        d.Accept(write);
        log("new score is %s",buffer.GetString());
        FILE* file = fopen(path.c_str(), "wb");
        if (file)
        {
            fputs(buffer.GetString(), file);
            fclose(file);
        }
        
        auto scene = GameOver::createScene();
        scene->set_score_(score_);
        scene->DataUpdate();
        
        Cooloi::Game::RandTransitionFn(scene);
    }
}
