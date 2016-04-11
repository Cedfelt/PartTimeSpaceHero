#include "MainMenu.hpp"
#include "GlobalPList.hpp"
#include "GameScene.hpp"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;



using namespace cocostudio::timeline;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    
    
    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool MainMenu::init()
{
    /**  you can create scene with following comment code instead of using csb file.
     // 1. super init first
     if ( !Layer::init() )
     {
     return false;
     }
     
     Size visibleSize = Director::getInstance()->getVisibleSize();
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     
     /////////////////////////////
     // 2. add a menu item with "X" image, which is clicked to quit the program
     //    you may modify it.
     
     // add a "close" icon to exit the progress. it's an autorelease object
     auto closeItem = MenuItemImage::create(
     "CloseNormal.png",
     "CloseSelected.png",
     CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
     
     closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
     origin.y + closeItem->getContentSize().height/2));
     
     // create menu, it's an autorelease object
     auto menu = Menu::create(closeItem, NULL);
     menu->setPosition(Vec2::ZERO);
     this->addChild(menu, 1);
     
     /////////////////////////////
     // 3. add your codes below...
     
     // add a label shows "Hello World"
     // create and initialize a label
     
     auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
     
     // position the label on the center of the screen
     label->setPosition(Vec2(origin.x + visibleSize.width/2,
     origin.y + visibleSize.height - label->getContentSize().height));
     
     // add the label as a child to this layer
     this->addChild(label, 1);
     
     // add "MainMenu" splash screen"
     auto sprite = Sprite::create("HelloWorld.png");
     
     // position the sprite on the center of the screen
     sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
     
     // add the sprite as a child to this layer
     this->addChild(sprite, 0);
     **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    
    //addChild(rootNode);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    const size_t scale = getScaleFactor();
    
    
    // Add Touch
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(MainMenu::onTouchBegan, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(MainMenu::onTouchEnded, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(MainMenu::onTouchMoved, this);
    touchListener->onTouchesCancelled = CC_CALLBACK_2(MainMenu::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // Debug Label -
    auto label = Label::createWithTTF("MainMenu", "fonts/Marker Felt.ttf", 25*scale);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));
    addChild(label);
    return true;
}

void MainMenu::onTouchBegan(const std::vector<Touch*>& touch, Event* event)
{
    cocos2d::log("touch Began");
}

void MainMenu::onTouchEnded(const std::vector<Touch*>& touches, Event*)
{
    setMapUrl("alpha.tmx");
    auto scene = GameScene::createScene();
    Director::getInstance()->pushScene(scene);
    
}

void MainMenu::onTouchMoved(const std::vector<Touch*>& touch, Event* event)
{
    cocos2d::log("touch moved");
}

void MainMenu::onTouchCancelled(const std::vector<Touch*>&, Event*)
{
    cocos2d::log("touch cancelled");
}
