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
  
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
  setDebuggDraw(false);
  
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
bool newGame;
void MainMenu::onTouchBegan(const std::vector<Touch*>& touch, Event* event)
{
    cocos2d::log("touch Began");
  newGame = true;
}

void MainMenu::onTouchEnded(const std::vector<Touch*>& touches, Event*)
{
  if(!newGame)
    return;
  newGame = false;
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  for (int i = 0;i<touches.size();i++) {
    if ((touches.at(i)->getStartLocation().x) < winSize.width / 2) {
      // LEFT
      setScaleFactor(2);
      setMapUrl("level1.tmx");
    }
    else {
      // RIGHT
      setMapUrl("g2.tmx");
      setScaleFactor(2);
    }
  }

  
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
