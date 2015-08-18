#include "HelloWorldScene.h"

using namespace cocos2d::ui;

USING_NS_CC;

#pragma mark - Initialization

HelloWorld::HelloWorld():
targets_(NULL),
bullets_(NULL)
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
    
#pragma mark -add close button
//    /////////////////////////////
//    // 2. add a menu item with "X" image, which is clicked to quit the program
//    //    you may modify it.
//    
//    // add a "close" icon to exit the progress. it's an autorelease object
//    auto close_item = MenuItemImage::create("CloseNormal.png",
//                                            "CloseSelected.png",
//                                            CC_CALLBACK_1(HelloWorld::MenuCloseCallback,
//                                                          this));
//    
//    close_item->setPosition(
//                            Vec2(origin.x + visible_size.width - close_item->getContentSize().width / 2,
//                                 origin.y + close_item->getContentSize().height / 2));
//    
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(close_item,
//                             NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu,
//                   1);
    
    //    /////////////////////////////
    //    // 3. add your codes below...
    //
    //    // add a label shows "Hello World"
    //    // create and initialize a label
    //
    //    auto label = LabelTTF::create("Hello World",
    //                                  "Arial",
    //                                  24);
    //
    //    // position the label on the center of the screen
    //    label->setPosition(Vec2(origin.x + visible_size.width/2,
    //                            origin.y + visible_size.height - label->getContentSize().height));
    //
    //
    //    // add the label as a child to this layer
    //    this->addChild(label,
    //                   1);
    //
    
#pragma mark -add player sprite
    // add "HelloWorld" splash screen"
    auto player1 = Sprite::create("xo0002.png");
    
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
    
    return true;
}// HelloWorld::init

#pragma mark - Callbakc function

void HelloWorld::MenuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}// HelloWorld::MenuCloseCallback

#pragma mark - Sprite Management

void HelloWorld::AddTarget()
{
    auto *target = Sprite::create("xo0001.png");
    auto window_size = Director::getInstance()->getVisibleSize();
    
    auto min_y = target->getContentSize().height / 2;
    auto max_y = window_size.height - target->getContentSize().height / 2;
    
    auto range_y = max_y - min_y;
    auto actual_y = (rand() % (int)range_y) + min_y;
    
    target->setPosition(Vec2(window_size.width + (target->getContentSize().width / 2),
                             actual_y));
    this->addChild(target);
    target->setTag(1);
    targets_.pushBack(target);
    
    auto min_duration = (int)2.0;
    auto max_duration = (int)4.0;
    
    auto range_duration = max_duration - min_duration;
    auto actural_duration = (rand() % range_duration) + min_duration;
    
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
        auto bullet_rect = Rect(bullet->getPosition().x - bullet->getContentSize().width / 2,
                                bullet->getPosition().y - bullet->getContentSize().height / 2,
                                bullet->getContentSize().width,
                                bullet->getContentSize().height);
        for (auto target : targets_)
        {
            auto target_rect = Rect(target->getPosition().x - target->getContentSize().width / 2,
                                    target->getPosition().y - target->getContentSize().height / 2,
                                    target->getContentSize().width,
                                    target->getContentSize().height);
            
            if (bullet_rect.intersectsRect(target_rect))
            {
                targets_to_delete.pushBack(target);
                bullets_to_delete.pushBack(bullet);
                log("hit");
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

#pragma mark - Touch

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch,
                              cocos2d::Event *event)
{
    return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch,
                              cocos2d::Event *event)
{
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
    
    bullet->runAction(
                      Sequence::create(MoveTo::create(real_move_duration,
                                                      read_destination),
                                       CallFuncN::create(this,
                                                         callfuncN_selector(HelloWorld::SpriteMoveFinished)),
                                       NULL));
}
